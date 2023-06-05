#pragma once

#include "CoreMinimal.h"

namespace SnakeGame
{
struct Dim
{
    int32 width;
    int32 height;
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
