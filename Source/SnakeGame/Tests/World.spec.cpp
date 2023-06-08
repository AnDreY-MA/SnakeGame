// My game copyright


#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"
#include "Core/Grid.h"
#include "Tests/AutomationCommon.h"
#include "Utils/TestUtils.h"
#include "World/SG_Grid.h"
#include "World/SG_WorldTypes.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

BEGIN_DEFINE_SPEC(FSnakeWorld, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
SnakeGame::Dim Dims;
uint32 CellSize;
TSharedPtr<SnakeGame::Grid> ModelGrid;
UStaticMeshComponent* GridStatiMesh;
ASG_Grid* GridVisual;
END_DEFINE_SPEC(FSnakeWorld)

// /Script/Engine.Blueprint'/Game/World/BP_SnakeGrid.BP_SnakeGrid'

void FSnakeWorld::Define()
{
    using namespace LifeExe::Test;
Describe("WorldGrid", [this]()
    {
    BeforeEach([this]()
    {
        AutomationOpenMap("TestEmptyLevel");
        World = GetTestGameWorld();

        constexpr char* GridBP = "Blueprint'/Game/World/BP_SnakeGrid.BP_SnakeGrid'";

        Dims = SnakeGame::Dim{10, 10};
        CellSize = 20;
        ModelGrid = MakeShared<SnakeGame::Grid>(Dims);

        const FTransform Origin = FTransform::Identity;
        GridVisual = CreateBlueprintDeferred<ASG_Grid>(World, GridBP, Origin);
        GridVisual->SetModel(ModelGrid, CellSize);
        GridVisual->FinishSpawning(Origin);

        auto* Comp = GridVisual->GetComponentByClass(UStaticMeshComponent::StaticClass());
        GridStatiMesh = Cast<UStaticMeshComponent>(Comp);
    });
    It("StaticGridMightHaveCorrectTransform", [this]()
    {
        const FBox Box = GridStatiMesh->GetStaticMesh()->GetBoundingBox();
        const auto Size = Box.GetSize();

        const auto WorldWidth = ModelGrid->getDim().width * CellSize;
        const auto WorldHeight = ModelGrid->getDim().height * CellSize;

        TestTrueExpr(GridStatiMesh->GetRelativeLocation().Equals(0.5 * FVector(WorldHeight, WorldWidth, -Size.Z)));
        TestTrueExpr(GridStatiMesh->GetRelativeScale3D().Equals(FVector(WorldHeight / Size.X, WorldWidth / Size.Y, 1.0)));
    });
    It("ColorsMightBeSetupCorrectly", [this]()
    {
        FSnakeColors Colors;
        Colors.GridBackgroundColor = FLinearColor::Green;
        Colors.GridWallColor = FLinearColor::Red;
        Colors.GridLineColor = FLinearColor::Yellow;
        GridVisual->UpdateColors(Colors);

        auto* Material = GridStatiMesh->GetMaterial(0);
        FLinearColor ColorToCheck;

        Material->GetVectorParameterValue(FName("BackgroundColor"), ColorToCheck);
        TestTrueExpr(ColorToCheck.Equals(Colors.GridBackgroundColor));
        
        Material->GetVectorParameterValue(FName("WallColor"), ColorToCheck);
        TestTrueExpr(ColorToCheck.Equals(Colors.GridWallColor));

        Material->GetVectorParameterValue(FName("LineColor"), ColorToCheck);
        TestTrueExpr(ColorToCheck.Equals(Colors.GridLineColor));
    });
    });
}

#endif
