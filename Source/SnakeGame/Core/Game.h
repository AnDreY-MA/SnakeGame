// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Utils.h"

namespace SnakeGame
{
class Grid;
class Snake;
class Food;

class Game
{
public:
    Game(const Settings& settings, const TSharedPtr<IPositionRandomizer>& randomizer = MakeShared<PositionRandomizer>());

    TSharedPtr<Grid> getGrid() const { return m_grid; }
    TSharedPtr<Snake> getSnake() const { return m_snake; }
    TSharedPtr<Food> getFood() const { return m_food; }
    
    void update(const float deltaSeconds, const Input& input);

    uint32 getScore() const { return m_score; }

    void subscribeOnGameplayEvent(GameplayEventCallback callback);

private:
    const Settings c_settings;
    TSharedPtr<Grid> m_grid;
    TSharedPtr<Snake> m_snake;
    TSharedPtr<Food> m_food;

    float m_moveSeconds{0.0f};
    bool m_gameOver{false};
    uint32 m_score{0};

    GameplayEventCallback m_gameplayEventCallback;

    void updateGrid();
    bool updateTime(float deltaSeconds);
    bool died() const;
    void generateFood();
    bool foodTaken() const;

    void dispatchEvent(GameplayEvent Event);

};
}

