// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game.h"
#include "Core/Grid.h"

using namespace SnakeGame;

Game::Game(const Settings& settings) //
    : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims);
}
