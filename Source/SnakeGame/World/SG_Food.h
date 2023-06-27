// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Food.h"
#include "Core/Snake.h"
#include "GameFramework/Actor.h"
#include "SG_Food.generated.h"

UCLASS()
class SNAKEGAME_API ASG_Food : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Food();

    void SetModel(const TSharedPtr<SnakeGame::Food>& InFood, uint32 InCellSize, const SnakeGame::Dim& Dims);
    void UpdateColor(const FLinearColor& Color);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    TWeakPtr<SnakeGame::Food> Food;
    uint32 CellSize;
    SnakeGame::Dim Dim;

};
