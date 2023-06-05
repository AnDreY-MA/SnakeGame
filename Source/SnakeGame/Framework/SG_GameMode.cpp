// SnakeGame. Momontov copyright. All right reserved.


#include "SG_GameMode.h"

#include "SG_Pawn.h"
#include "Core/Grid.h"
#include "Core/Types.h"
#include "World/SG_Grid.h"

void ASG_GameMode::StartPlay()
{
    Super::StartPlay();

    SnakeGame::Settings GS {GridDims.X, GridDims.Y};

    Game = MakeUnique<SnakeGame::Game>(GS);

    const FTransform GridOrigin = FTransform::Identity;
    GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
    GridVisual->SetModel(Game->getGrid(), CellSize);
    GridVisual->FinishSpawning(GridOrigin);

    //set pawn
    const auto* PlayerController = GetWorld()->GetFirstPlayerController();
    check(PlayerController);
    auto* Pawn = Cast<ASG_Pawn>(PlayerController->GetPawn());
    check(Pawn);
    Pawn->UpdateLocation(Game->getGrid()->getDim(), CellSize, GridOrigin);
}
