// My game copyright


#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Grid.h"

DEFINE_SPEC(FSnakeGrid, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)


void FSnakeGrid::Define()
{
    using namespace SnakeGame;
    
Describe("CoreGrid", [this]()
{
    It("DimsMightIncludeWalls", [this]()
    {
        const Grid grid(Dim{10, 10});
        TestTrueExpr(grid.getDim().height == 12);
        TestTrueExpr(grid.getDim().width == 12);
    });
});
}

#endif
