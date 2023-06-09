#pragma once

#include "CoreMinimal.h"
#include "Containers/List.h"

namespace SnakeGame
{
struct Dim
{
    uint32 width;
    uint32 height;
};

struct Position
{
    Position(uint32 inX, uint32 inY) : x(inX), y(inY) {}
    
    uint32 x;
    uint32 y;

    FORCEINLINE Position& operator+=(const Position& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }
    
};

struct Input
{
    int8 x;
    int8 y;

    FORCEINLINE bool opposite(const Input& rhs) const
    {
        return (x == -rhs.x && x != 0) || (y == -rhs.y && y != 0);
    }
};

enum class CellType
{
    Empty = 0,
    Wall,
    Snake
};

struct Settings
{
    Dim gridDims;
    struct Snake
    {
        uint32 defaultSize{4};
        Position startPosition {0, 0};
    } snake;
    float gameSpeed{1.0f};
};

using TPositionPtr = TDoubleLinkedList<Position>::TDoubleLinkedListNode;

class TSnakeList : TDoubleLinkedList<Position>
{
public:
    void MoveTail(TPositionPtr* tail, TPositionPtr* head, const Position& pos)
    {
        RemoveNode(tail);
        InsertNode(pos, head->GetNextNode());
    }
};

}
