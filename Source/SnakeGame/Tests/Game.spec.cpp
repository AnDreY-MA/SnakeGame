// My game copyright


#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"
#include "Core/Grid.h"

using namespace SnakeGame;

BEGIN_DEFINE_SPEC(FSnakeGame, "SnakeGame", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
TUniquePtr<Game> CoreGame;
END_DEFINE_SPEC(FSnakeGame)

void FSnakeGame::Define()
{
    
    
Describe("CoreGame", [this]()
{
    BeforeEach([this]()
    {
        Settings GS;
        GS.gridDims = Dim{10, 10};
        GS.snake.startPosition = Grid::center(GS.gridDims.width, GS.gridDims.height);
        CoreGame = MakeUnique<Game>(GS);
    });
    
    It("GridMightExists", [this]()
    {
        TestTrueExpr(CoreGame->getGrid().IsValid());
    });
    It("SnakeMightExists", [this]()
    {
        TestTrueExpr(CoreGame->getSnake().IsValid());
    });
    It("FoodMightExists", [this]()
    {
        TestTrueExpr(CoreGame->getFood().IsValid());
    });
});
}

#endif
