// SnakeGame. Momontov copyright. All right reserved.


#include "World/SG_Food.h"
#include "Components/StaticMeshComponent.h"
#include "SG_WorldUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Core/Food.h"

ASG_Food::ASG_Food()
{
	PrimaryActorTick.bCanEverTick = true;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    SetRootComponent(Origin);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("FoodMesh");
    Mesh->SetupAttachment(Origin);

}

void ASG_Food::SetModel(const TSharedPtr<SnakeGame::Food>& InFood, uint32 InCellSize, const SnakeGame::Dim& Dims)
{
    Food = InFood;
    CellSize = InCellSize;
    Dim = Dims;

    SnakeGame::WorldUtils::ScaleMesh(Mesh, FVector(CellSize));
}

void ASG_Food::UpdateColor(const FLinearColor& Color)
{
    FoodColor = Color;
    if(auto* Material = Mesh->CreateAndSetMaterialInstanceDynamic(0))
    {
        Material->SetVectorParameterValue("Color", Color);
    }
}

void ASG_Food::Explode()
{
    if (UNiagaraComponent* NS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetFoodWorldLocation()))
    {
        NS->SetNiagaraVariableLinearColor("SnakeColor", FoodColor);
    }
}

// Called every frame
void ASG_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    SetActorLocation(GetFoodWorldLocation());
    
}

FVector ASG_Food::GetFoodWorldLocation() const
{
    if(!Food.IsValid()) return FVector::ZeroVector;
    
    return SnakeGame::WorldUtils::LinkPositionToVector(Food.Pin()->getPosition(), CellSize, Dim);
}

