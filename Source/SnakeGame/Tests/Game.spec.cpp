// My game copyright


#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"
#include "Core/Grid.h"
#include "Core/Utils.h"

using namespace SnakeGame;

BEGIN_DEFINE_SPEC(FSnakeGame, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
TUniquePtr<Game> CoreGame;
Settings GS;
END_DEFINE_SPEC(FSnakeGame)

class MockPositionRandomizer : public IPositionRandomizer
{
public:
    virtual bool generatePosition(const Dim& dim, const TArray<CellType>& cells, Position& position) const override
    {
        position = m_positions[m_index++];
        return true;
    }

    void setPosition(const TArray<Position>& positions)
    {
        m_positions = positions;
    }

private:
    TArray<Position> m_positions;
    mutable int32 m_index{0};

};

void FSnakeGame::Define()
{
    
    
Describe("Core.Game", [this]()
{
    BeforeEach([this]()
    {
        GS.gridDims = Dim{10, 10};
        GS.snake.startPosition = Grid::center(GS.gridDims.width, GS.gridDims.height);
        GS.gameSpeed = 1.0f;
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

    It("GameCanBeOver", [this]()
    {
        bool bGameOver{false};
        CoreGame->subscribeOnGameplayEvent(
            [&bGameOver](GameplayEvent Event)
            {
                if(Event == GameplayEvent::GameOver)
                {
                    bGameOver = true;
                }
            });

        const int32 Moves = FMath::RoundToInt(GS.gridDims.width / 2.0f) - 1;

        for(int32 i = 0; i < Moves; ++i)
        {
            CoreGame->update(1.0f, Input::Default);
            TestTrueExpr(!bGameOver);
        }
        CoreGame->update(1.0f, Input::Default);
        TestTrueExpr(bGameOver);
    });

    
});

    Describe("Core.Game", [this]()
    {
        It("FoodCanBeTaken", [this]()
    {
        
        auto Randomizer = MakeShared<MockPositionRandomizer>();
            Randomizer->setPosition({Position{7, 6}, Position{9, 6}, Position::Zero});    
            
        GS.gridDims = Dim{10, 10};
        GS.snake.startPosition = Grid::center(GS.gridDims.width, GS.gridDims.height);
        GS.gameSpeed = 1.0f;
        CoreGame = MakeUnique<Game>(GS, MakeShared<MockPositionRandomizer>());
            
        uint32 Score = 0;

        CoreGame->subscribeOnGameplayEvent(
            [&Score](GameplayEvent Event)
            {
                if(Event == GameplayEvent::FoodTaken)
                {
                    ++Score;
                }
            });

            TestTrueExpr(CoreGame->getScore() == 0);
            TestTrueExpr(Score == 0);

            CoreGame->update(1.0f, Input::Default);
            TestTrueExpr(CoreGame->getScore() == 1);
            TestTrueExpr(Score == 1);

            CoreGame->update(1.0f, Input::Default);
            TestTrueExpr(CoreGame->getScore() == 1);
            TestTrueExpr(Score == 1);

            CoreGame->update(1.0f, Input::Default);
            TestTrueExpr(CoreGame->getScore() == 1);
            TestTrueExpr(Score == 1);

            CoreGame->update(1.0f, Input::Default);
            TestTrueExpr(CoreGame->getScore() == 2);
            TestTrueExpr(Score == 2);
    });
    });
}

#endif
