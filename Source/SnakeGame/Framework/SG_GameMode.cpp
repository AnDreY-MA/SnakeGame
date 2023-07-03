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
#include "World/SG_Snake.h"
#include "World/SG_WorldTypes.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "World/SG_Food.h"

DEFINE_LOG_CATEGORY_STATIC(LogSnakeGameMode, All, All);

ASG_GameMode::ASG_GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASG_GameMode::StartPlay()
{
    Super::StartPlay();

    SubscribeOnGameEvents();

    SetupGame();
    SetupGrid();
    SetupPawn();
    SetupSnake();
    SetupFood();

    FindFog();
    UpdateColors();

    SetupInput();
    
}

void ASG_GameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if(Game)
    {
        Game->update(DeltaSeconds, SnakeInput);
    }
}

void ASG_GameMode::NextColor()
{
    if(!ColorsTable) return;
    
    ColorTableIndex = (ColorTableIndex + 1) % ColorsTable->GetRowNames().Num();
    UpdateColors();
}

void ASG_GameMode::SetupGame()
{
    Game = MakeUnique<SnakeGame::Game>(MakeSettings());
    
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

void ASG_GameMode::SetupSnake()
{
    SnakeVisual = GetWorld()->SpawnActorDeferred<ASG_Snake>(SnakeVisualClass, FTransform::Identity);
    SnakeVisual->SetModel(Game->getSnake(), CellSize, Game->getGrid()->getDim());
    SnakeVisual->FinishSpawning(FTransform::Identity);
}

void ASG_GameMode::SetupInput()
{
    if(const auto* PC = GetWorld()->GetFirstPlayerController())
    {
        if(auto* InputSystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            InputSystem->AddMappingContext(InputMappingContext, 0);
        }

        auto* Input = Cast<UEnhancedInputComponent>(PC->InputComponent);
        check(Input);
        Input->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveForward);
        Input->BindAction(MoveRightInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveRight);
        Input->BindAction(ResetGameInputAction, ETriggerEvent::Started, this, &ThisClass::OnGameReset);
    }
}

void ASG_GameMode::SetupFood()
{
    FoodVisual = GetWorld()->SpawnActorDeferred<ASG_Food>(FoodVisualClass, FTransform::Identity);
    FoodVisual->SetModel(Game->getFood(), CellSize, Game->getGrid()->getDim());
    FoodVisual->FinishSpawning(FTransform::Identity);
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

    SnakeVisual->UpdateColors(*ColorSet);
    FoodVisual->UpdateColor(ColorSet->FoodColor);

    if(Fog && Fog->GetComponent())
    {
        Fog->GetComponent()->SkyAtmosphereAmbientContributionColorScale =
            ColorSet->SkyAtmosphereColor;
        Fog->MarkComponentsRenderStateDirty();
    }

}

void ASG_GameMode::OnMoveForward(const FInputActionValue& Value)
{
    const float InputValue = Value.Get<float>();
    if(InputValue == 0.0f) return;
    SnakeInput = SnakeGame::Input{0,static_cast<int8>(InputValue)};
}

void ASG_GameMode::OnMoveRight(const FInputActionValue& Value)
{
    const float InputValue = Value.Get<float>();
    if(InputValue == 0.0f) return;
    SnakeInput = SnakeGame::Input{static_cast<int8>(InputValue), 0};
}

void ASG_GameMode::OnGameReset(const FInputActionValue& Value)
{
    if(const bool InputValue = Value.Get<bool>())
    {
        Game.Reset(new SnakeGame::Game(MakeSettings()));
        SubscribeOnGameEvents();
        GridVisual->SetModel(Game->getGrid(), CellSize);
        SnakeVisual->SetModel(Game->getSnake(), CellSize, Game->getGrid()->getDim());
        FoodVisual->SetModel(Game->getFood(), CellSize, Game->getGrid()->getDim());
        SnakeInput = SnakeGame::Input::Default;
    }
    
}

SnakeGame::Settings ASG_GameMode::MakeSettings() const
{
    SnakeGame::Settings GS;
    GS.gridDims = SnakeGame::Dim {GridDims.X, GridDims.Y};
    GS.gameSpeed = GameSpeed;
    GS.snake.defaultSize = SnakeDefaultSize;
    GS.snake.startPosition = SnakeGame::Grid::center(GridDims.X, GridDims.Y);
        //SnakeGame::Position(GridDims.X / 2, GridDims.Y / 2);

    return GS;
}

void ASG_GameMode::SubscribeOnGameEvents()
{
    using namespace SnakeGame;

    Game->subscribeOnGameplayEvent(
        [&](GameplayEvent Event)
    {
        switch (Event)
        {
            case GameplayEvent::GameOver:
                UE_LOG(LogSnakeGameMode, Display, TEXT("--------GAME OVER--------"));
                UE_LOG(LogSnakeGameMode, Display, TEXT("--------SCORE: %i--------"), Game->getScore());
                SnakeVisual->Explode();
                break;
            case GameplayEvent::GameCompleted:
                UE_LOG(LogSnakeGameMode, Display, TEXT("--------GAME COMPLETED--------"));
                UE_LOG(LogSnakeGameMode, Display, TEXT("--------SCORE: %i--------"), Game->getScore());
                break;
            case GameplayEvent::FoodTaken:
                FoodVisual->Explode();
                break;
        }
    });
}
