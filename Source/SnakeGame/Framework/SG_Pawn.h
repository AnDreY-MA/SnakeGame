// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"
#include "GameFramework/Pawn.h"
#include "SG_Pawn.generated.h"

class UCameraComponent;

UCLASS()
class SNAKEGAME_API ASG_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASG_Pawn();

    void UpdateLocation(const SnakeGame::Dim& InDim, int32 InCellSize, const FTransform& InGridOrigin);
    
protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

private:
    SnakeGame::Dim Dim;
    int32 CellSize;
    FTransform GridOrigin;
    FDelegateHandle ResizeHandle;

    void OnViewportResized(FViewport* Viewport, uint32 Val);

};
