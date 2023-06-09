// SnakeGame. Momontov copyright. All right reserved.


#include "Core/Snake.h"
#include "Containers/List.h"

using namespace SnakeGame;

Snake::Snake(const Settings::Snake& settings)
{
    const auto startPosition = settings.startPosition;
    for(uint32 i = 0; i < settings.defaultSize; ++i)
    {
        m_links.AddTail(Position{startPosition.x - i, startPosition.y});
    }
}

void Snake::move(const Input& input)
{
    if(!m_lastInput.opposite(input))
    {
        m_lastInput = input;
    }

    m_links.MoveTail(m_links.GetTail(), m_links.GetHead(), m_links.GetHead()->GetValue());
    m_links.GetHead()->GetValue() += Position(m_lastInput.x, m_lastInput.y);
}
