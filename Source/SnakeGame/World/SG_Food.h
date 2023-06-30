// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"
#include "GameFramework/Actor.h"
#include "SG_Food.generated.h"

namespace SnakeGame
{
class Food;
}
class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class SNAKEGAME_API ASG_Food : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Food();

    void SetModel(const TSharedPtr<SnakeGame::Food>& InFood, uint32 InCellSize, const SnakeGame::Dim& Dims);
    void UpdateColor(const FLinearColor& Color);

    void Explode();

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    TObjectPtr<UNiagaraSystem> ExplosionEffect;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    TWeakPtr<SnakeGame::Food> Food;
    uint32 CellSize;
    SnakeGame::Dim Dim;

    FLinearColor FoodColor;

    FVector GetFoodWorldLocation() const;

};
