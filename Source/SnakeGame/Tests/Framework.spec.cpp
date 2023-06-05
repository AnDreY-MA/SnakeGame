// My game copyright

#include "Framework/SG_GameMode.h"
#include "Utils/TestUtils.h"
#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(FSnakeFramework, "Category", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
END_DEFINE_SPEC(FSnakeFramework)

void FSnakeFramework::Define()
{
    using namespace LifeExe::Test;
    
Describe("Framework", [this]()
    {
    BeforeEach([this]()
    {
       AutomationOpenMap("GameLevel");
        World = GetTestGameWorld();
    });
    It("GameMapMightExist", [this]()
    {
        TestNotNull("World Exists", World);
    });
    It("ClassesMightBeSetupCorrectly", [this]()
    {
        TestNotNull("Snake game mode set up", Cast<ASG_GameMode>(World->GetAuthGameMode()));
    });

    });
}

#endif
