// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game.h"

#include "Snake.h"
#include "Core/Grid.h"
#include "Core/Snake.h"
#include "Core/Food.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All);

using namespace SnakeGame;

Game::Game(const Settings& settings) //
    : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims);
    m_snake = MakeShared<Snake>(settings.snake);
    m_food = MakeShared<Food>();

    updateGrid();
    generateFood();
}

void Game::update(const float deltaSeconds, const Input& input)
{
    if(m_gameOver || !updateTime(deltaSeconds)) return;
    
    m_snake->move(input);

    if(died())
    {
        m_gameOver = true;
        UE_LOG(LogGame, Display, TEXT("--------GAME OVER--------"));
        return;
    }
    //updateGrid();

    if(foodTaken())
    {
        ++m_score;
        m_snake->increase();
        generateFood();
    }

    updateGrid();
}

void Game::updateGrid()
{
    m_grid->update(m_snake->links().GetHead(), CellType::Snake);
    m_grid->printDebug();
}

bool Game::updateTime(float deltaSeconds)
{
    m_moveSeconds += deltaSeconds;
    if(m_moveSeconds < c_settings.gameSpeed) return false;
    m_moveSeconds = 0.0f;
    return true;
}

bool Game::died() const
{
    return m_grid->hitTest(m_snake->head(), CellType::Wall) ||
        m_grid->hitTest(m_snake->head(), CellType::Snake);
}

void Game::generateFood()
{
    Position foodPosition{Position::Zero};
    if(m_grid->randomEmptyPosition(foodPosition))
    {
        m_food->setPosition(foodPosition);
        m_grid->update(m_food->getPosition(), CellType::Food);
    }
    else
    {
        m_gameOver = true;
        UE_LOG(LogGame, Display, TEXT("--------GAME COMPLETED--------"));
    }
    
}

bool Game::foodTaken() const
{
    return m_grid->hitTest(m_snake->head(), CellType::Snake);
}
