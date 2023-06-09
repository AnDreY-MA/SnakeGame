// SnakeGame. Momontov copyright. All right reserved.


#include "SG_SnakeLink.h"

ASG_SnakeLink::ASG_SnakeLink()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    SetRootComponent(Origin);

    LinkMesh = CreateDefaultSubobject<UStaticMeshComponent>("LinkMesh");
    LinkMesh->SetupAttachment(Origin);

}

void ASG_SnakeLink::UpdateColors(const FLinearColor& Color)
{
    if(auto* LinkMaterial = LinkMesh->CreateAndSetMaterialInstanceDynamic(0))
    {
        LinkMaterial->SetVectorParameterValue("Color", Color);
    }
}

void ASG_SnakeLink::UpdateScale(uint32 CellSize)
{
    const FBox Box = LinkMesh->GetStaticMesh()->GetBoundingBox();
    const auto Size = Box.GetSize();

    LinkMesh->SetRelativeScale3D(FVector(CellSize / Size.X, CellSize / Size.Y, CellSize / Size.Z));
}


