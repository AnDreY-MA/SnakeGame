#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"

namespace SnakeGame
{
class WorldUtils
{
public:
   static FVector LinkPositionToVector(const Position& Position, uint32 CellSize, const Dim& Dim)
   {
         return FVector((Dim.height - 1 - Position.y) * CellSize, Position.x * CellSize, 0.0) + FVector(CellSize * 0.5);
   }
   
   static void ScaleMesh(UStaticMeshComponent* Mesh, const FVector& WorldSize)
   {
       const FBox Box = Mesh->GetStaticMesh()->GetBoundingBox();
       const auto Size = Box.GetSize();

       check(!Size.IsZero())
       Mesh->SetRelativeScale3D(FVector(WorldSize / Size));
   }
   
};
}
