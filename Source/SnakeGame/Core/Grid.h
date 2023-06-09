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
    void printDebug();
    
    void update(const TPositionPtr* links, CellType cellType);

    bool hitTest(const Position& position, CellType cellType) const;
    
private:
    const Dim c_dim;
    TArray<CellType> m_cells;
    TMap<CellType, TArray<uint32>> m_indByType =
        {
            {CellType::Snake, {}},
            {CellType::Wall, {}}
        };

    void initWalls();
    void updateInternal(const Position& position, CellType cellType);
    void freeCellsByType(CellType cellType);
    FORCEINLINE uint32 posToIndex(const uint32 x, const uint32 y) const;
    FORCEINLINE uint32 posToIndex(const Position& pos) const;
};
}
