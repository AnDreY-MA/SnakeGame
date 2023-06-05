// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"
#include "GameFramework/Actor.h"
#include "SG_Grid.generated.h"

namespace SnakeGame
{
class Grid;
}

UCLASS()
class SNAKEGAME_API ASG_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Grid();

	virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, int32 InCellSize);

private:
    SnakeGame::Dim GridDim;

    int32 CellSize;
    int32 WorldWidth;
    int32 WorldHeight;

    void DrawGrid();

};
