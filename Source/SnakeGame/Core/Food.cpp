#include "Food.h"

using namespace SnakeGame;

void SnakeGame::Food::setPosition(const Position& position)
{
    m_position = position;
}

SnakeGame::Position SnakeGame::Food::getPosition() const
{
    return m_position;
}
