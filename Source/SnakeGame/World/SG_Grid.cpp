// SnakeGame. Momontov copyright. All right reserved.


#include "World/SG_Grid.h"

#include "Core/Grid.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASG_Grid::ASG_Grid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    SetRootComponent(Origin);

    GridMesh = CreateDefaultSubobject<UStaticMeshComponent>("GridMesh");
    GridMesh->SetupAttachment(Origin);

}

// Called every frame
void ASG_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //DrawGrid();

}

void ASG_Grid::BeginPlay()
{
    Super::BeginPlay();
}

void ASG_Grid::SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize)
{
    GridDim = Grid->getDim();
    CellSize = InCellSize;
    WorldWidth = GridDim.width * CellSize;
    WorldHeight = GridDim.height * CellSize;

    SetupGridMesh();
    SetupMaterial();
}

void ASG_Grid::UpdateColors(const FSnakeColors& ColorSet)
{
    if(!GridMaterial) return;

    GridMaterial->SetVectorParameterValue("BackgroundColor", ColorSet.GridBackgroundColor);
    GridMaterial->SetVectorParameterValue("LineColor", ColorSet.GridLineColor);
    GridMaterial->SetVectorParameterValue("GridColor", ColorSet.GridWallColor);
    
}

void ASG_Grid::DrawGrid()
{
    for(uint32 i = 0; i < GridDim.height; ++i)
    {
        const FVector StartLocation = GetActorLocation() + GetActorForwardVector() * CellSize * i;
        const FVector EndLocation = StartLocation + GetActorRightVector() * WorldWidth;
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.0f, 0, 1.0f);
    }

    for(uint32 i = 0; i < GridDim.height; ++i)
    {
        const FVector StartLocation = GetActorLocation() + GetActorRightVector() * CellSize * i;
        const FVector EndLocation = StartLocation + GetActorForwardVector() * WorldHeight;
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.0f, 0, 1.0f);
    }
}

void ASG_Grid::SetupGridMesh()
{
    check(GridMesh->GetStaticMesh());
    const FBox Box = GridMesh->GetStaticMesh()->GetBoundingBox();
    const auto Size = Box.GetSize();

    GridMesh->SetRelativeScale3D(FVector(WorldHeight / Size.X, WorldWidth / Size.Y, 1.0));
    GridMesh->SetRelativeLocation(0.5 * FVector(WorldHeight, WorldWidth, -Size.Z));
}

void ASG_Grid::SetupMaterial()
{
    GridMaterial = GridMesh->CreateAndSetMaterialInstanceDynamic(0);
    if(GridMaterial)
    {
        GridMaterial->SetVectorParameterValue("Division", FVector(GridDim.height, GridDim.width, 0));
    }
}

