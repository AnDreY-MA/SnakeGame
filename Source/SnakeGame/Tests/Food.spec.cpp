// My game copyright

#include "Core/Food.h"
#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Types.h"

DEFINE_SPEC(FSnakeFood, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

// BEGIN_DEFINE_SPEC(FTestClassName, "Category", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

// END_DEFINE_SPEC(FTestClassName)

void FSnakeFood::Define()
{
    using namespace SnakeGame;
Describe("Core.Food", [this]()
{
    It("PositionCabBeUpdated", [this]()
    {
        const Position Pos = Position(45, 67);
        Food CoreFood;
        CoreFood.setPosition(Pos);
        TestTrueExpr(CoreFood.getPosition() == Pos);
    });
});
}

#endif
