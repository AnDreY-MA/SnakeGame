// SnakeGame. Momontov copyright. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{

class Snake
{
public:
    Snake(const Settings::Snake& settings);

    const TSnakeList& links() const { return m_links; }
    Position head() const { return m_links.GetHead()->GetValue(); }
    TPositionPtr* body() const { return m_links.GetHead()->GetNextNode(); }
    void move(const Input& Input);

private:
    TSnakeList m_links;
    Input m_lastInput{1, 0};
};

}
