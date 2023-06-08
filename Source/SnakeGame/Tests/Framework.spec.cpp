// My game copyright

#include "Framework/SG_GameMode.h"
#include "Misc/PathViews.h"
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
    It("GameMapMightExist", [this]()
    {
        const TArray<FString> SnakeGameMaps = { "GameLevel" };
        TArray<FString> AllProjectMaps;
        IFileManager::Get().FindFilesRecursive(AllProjectMaps, *FPaths::ProjectConfigDir(), TEXT("*.umap"), true, false);

        for(const auto& SnakeGameMap : SnakeGameMaps)
        {
            const bool bSnakeMapExists = AllProjectMaps.ContainsByPredicate([&](const FString& ProjectMap)
            {
                FStringView OutPath, OutName, OutExit;
                FPathViews::Split(FStringView(ProjectMap), OutPath, OutName, OutExit);
                return SnakeGameMap.Equals(FString(OutName));
            });

            TestTrueExpr(bSnakeMapExists);
        }

    });

    });
    
Describe("Framework", [this]()
    {
    BeforeEach([this]()
    {
       AutomationOpenMap("GameLevel");
        World = GetTestGameWorld();
    });

    It("ClassesMightBeSetupCorrectly", [this]()
    {
        TestNotNull("Snake game mode set up", Cast<ASG_GameMode>(World->GetAuthGameMode()));
    });

    });
}

#endif
