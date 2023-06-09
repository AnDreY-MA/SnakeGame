// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Game.h"
#include "GameFramework/GameModeBase.h"
#include "InputActionValue.h"
#include "SG_GameMode.generated.h"

class ASG_Snake;
class AExponentialHeightFog;
class UDataTable;
class ASG_Grid;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASG_GameMode();
    
    virtual void StartPlay() override;
    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(EditDefaultsOnly, meta=(ClampMin="10", ClampMax="100"), Category="Settings")
    FUintPoint GridDims{10, 10};

    UPROPERTY(EditDefaultsOnly, meta=(ClampMin="10", ClampMax="100"), Category="Settings")
    uint32 CellSize{10};
    
    UPROPERTY(EditDefaultsOnly, meta=(ClampMin="4", ClampMax="10"), Category="Settings")
    uint32 SnakeDefaultSize{5};

    UPROPERTY(EditDefaultsOnly, meta=(ClampMin="0.01", ClampMax="10"), Category="Settings")
    float GameSpeed{1.0f};

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_Grid> GridVisualClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_Snake> SnakeVisualClass;

    UPROPERTY(EditDefaultsOnly, Category="Design")
    TObjectPtr<UDataTable> ColorsTable;

    UPROPERTY(EditDefaultsOnly, Category="InputSnake")
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category="InputSnake")
    TObjectPtr<UInputAction> MoveForwardInputAction;
    
    UPROPERTY(EditDefaultsOnly, Category="InputSnake")
    TObjectPtr<UInputAction> MoveRightInputAction;

    UPROPERTY(EditDefaultsOnly, Category="InputSnake")
    TObjectPtr<UInputAction> ResetGameInputAction;
    
private:
    UPROPERTY()
    ASG_Grid* GridVisual;

    UPROPERTY()
    ASG_Snake* SnakeVisual;

    UPROPERTY()
    AExponentialHeightFog* Fog;
    
    TUniquePtr<SnakeGame::Game> Game;
    uint32 ColorTableIndex{0};
    SnakeGame::Input SnakeInput;

    UFUNCTION(Exec, Category="Console command")
    void NextColor();
    
    void SetupGame();
    void SetupGrid();
    void SetupPawn() const;
    void SetupSnake();
    void SetupInput();
    
    void FindFog();
    void UpdateColors();

    void OnMoveForward(const FInputActionValue& Value);
    void OnMoveRight(const FInputActionValue& Value);
    void OnGameReset(const FInputActionValue& Value);

    SnakeGame::Settings MakeSettings() const;
};
