﻿// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "SG_WorldTypes.h"
#include "GameFramework/Actor.h"
#include "Core/Snake.h"
#include "SG_Snake.generated.h"

class ASG_SnakeLink;

UCLASS()
class SNAKEGAME_API ASG_Snake : public AActor
{
    GENERATED_BODY()

public:
    ASG_Snake();

    void SetModel(const TSharedPtr<SnakeGame::Snake>& InSnake, uint32 InCellSize, const SnakeGame::Dim& InDims);
    void UpdateColors(const FSnakeColors& Colors);

    void Explode();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ASG_SnakeLink> SnakeHeadClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ASG_SnakeLink> SnakeLinkClass;
    
public:
    virtual void Tick(float DeltaTime) override;

private:
    TWeakPtr<SnakeGame::Snake> Snake;
    uint32 CellSize;
    SnakeGame::Dim Dims;

    UPROPERTY()
    TArray<ASG_SnakeLink*> SnakeLinks;

    void SpawnLink();


};
