// SnakeGame. Momontov copyright. All right reserved.


#include "SG_GameMode.h"

#include "SG_Pawn.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Core/Grid.h"
#include "Core/Types.h"
#include "Engine/DataTable.h"
#include "Engine/ExponentialHeightFog.h"
#include "Kismet/GameplayStatics.h"
#include "World/SG_Grid.h"
#include "World/SG_WorldTypes.h"

void ASG_GameMode::StartPlay()
{
    Super::StartPlay();

    SetupGame();
    SetupGrid();
    SetupPawn();

    FindFog();
    UpdateColors();
    
}

void ASG_GameMode::NextColor()
{
    if(!ColorsTable) return;
    
    ColorTableIndex = (ColorTableIndex + 1) % ColorsTable->GetRowNames().Num();
    UpdateColors();
}

void ASG_GameMode::SetupGame()
{
    SnakeGame::Settings GS {GridDims.X, GridDims.Y};
    Game = MakeUnique<SnakeGame::Game>(GS);
    
}

void ASG_GameMode::SetupGrid()
{
    const FTransform GridOrigin = FTransform::Identity;
    GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
    GridVisual->SetModel(Game->getGrid(), CellSize);
    GridVisual->FinishSpawning(GridOrigin);
    
}

void ASG_GameMode::SetupPawn() const
{
    const FTransform GridOrigin = FTransform::Identity;
    const auto* PlayerController = GetWorld()->GetFirstPlayerController();
    check(PlayerController);
    auto* Pawn = Cast<ASG_Pawn>(PlayerController->GetPawn());
    check(Pawn);
    Pawn->UpdateLocation(Game->getGrid()->getDim(), CellSize, GridOrigin);
    
}

void ASG_GameMode::FindFog()
{
    TArray<AActor*> Fogs;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExponentialHeightFog::StaticClass(), Fogs);
    if(Fogs.Num() > 0)
    {
        Fog = Cast<AExponentialHeightFog>(Fogs[0]);
    }
}

void ASG_GameMode::UpdateColors()
{
    ColorTableIndex = FMath::RandRange(0, ColorsTable->GetRowNames().Num() - 1);
    const auto RowName = ColorsTable->GetRowNames()[ColorTableIndex];
    const auto* ColorSet = ColorsTable->FindRow<FSnakeColors>(RowName, {});
    if(!ColorSet) return;

    GridVisual->UpdateColors(*ColorSet);

    if(Fog && Fog->GetComponent())
    {
        Fog->GetComponent()->SkyAtmosphereAmbientContributionColorScale =
            ColorSet->SkyAtmosphereColor;
        Fog->MarkComponentsRenderStateDirty();
    }

}