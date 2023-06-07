// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{
class Grid
{
public:
    Grid(const Dim& dim);

    Dim getDim() const { return c_dim; }
    
private:
    const Dim c_dim;
    TArray<CellType> m_cells;

    void initWalls();
    void printDebug();
    FORCEINLINE uint32 posToIndex(const uint32 x, const uint32 y) const;
};
}
