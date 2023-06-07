// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SG_WorldTypes.h"
#include "Core/Types.h"
#include "GameFramework/Actor.h"
#include "SG_Grid.generated.h"

namespace SnakeGame
{
class Grid;
}

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ASG_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Grid();

	virtual void Tick(float DeltaTime) override;

    void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize);
    void UpdateColors(const FSnakeColors& ColorSet);

protected:

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;
    
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* GridMesh;

    virtual void BeginPlay() override;
    
private:
    UPROPERTY()
    UMaterialInstanceDynamic* GridMaterial;
    
    SnakeGame::Dim GridDim;

    uint32 CellSize;
    uint32 WorldWidth;
    uint32 WorldHeight;

    void DrawGrid();
    void SetupGridMesh();
    void SetupMaterial();

};
