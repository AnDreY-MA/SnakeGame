#pragma once

#include "CoreMinimal.h"

namespace SnakeGame
{
struct Dim
{
    uint32 width;
    uint32 height;
};

enum class CellType
{
    Empty = 0,
    Wall
};

struct Settings
{
    Dim gridDims;
};
}
