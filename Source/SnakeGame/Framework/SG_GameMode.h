// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Game.h"
#include "GameFramework/GameModeBase.h"
#include "SG_GameMode.generated.h"

class AExponentialHeightFog;
class UDataTable;
class ASG_Grid;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void StartPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, meta=(ClampMin="10", ClampMax="100"))
    FUintPoint GridDims{10, 10};

    UPROPERTY(EditDefaultsOnly, meta=(ClampMin="10", ClampMax="100"))
    uint32 CellSize{10};

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_Grid> GridVisualClass;

    UPROPERTY(EditDefaultsOnly, Category="Design")
    UDataTable* ColorsTable;
    
private:
    UPROPERTY()
    ASG_Grid* GridVisual;

    UPROPERTY()
    AExponentialHeightFog* Fog;
    
    TUniquePtr<SnakeGame::Game> Game;
    uint32 ColorTableIndex{0};

    UFUNCTION(Exec, Category="Console command")
    void NextColor();
    
    void SetupGame();
    void SetupGrid();
    void SetupPawn() const;
    void FindFog();
    void UpdateColors();
};
