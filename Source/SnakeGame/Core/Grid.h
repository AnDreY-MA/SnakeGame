// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Utils.h"

namespace SnakeGame
{
class Grid
{
public:
    Grid(const Dim& dim, const TSharedPtr<IPositionRandomizer>& randomizer = MakeShared<PositionRandomizer>());

    Dim getDim() const { return c_dim; }
    void printDebug();
    
    void update(const TPositionPtr* links, CellType cellType);
    void update(const Position& position, CellType cellType);

    UE_NODISCARD bool randomEmptyPosition(Position& position)const;

    bool hitTest(const Position& position, CellType cellType) const;
    static Position center(uint32 width, uint32 height) { return Position(width / 2 + 1, height / 2 + 1); }

private:
    const Dim c_dim;
    TArray<CellType> m_cells;
    TMap<CellType, TArray<uint32>> m_indByType =
        {
            {CellType::Snake, {}},
            {CellType::Wall, {}},
            {CellType::Food, {}}
        };

    TSharedPtr<IPositionRandomizer> m_positionRandomizer;

    void initWalls();
    void updateInternal(const Position& position, CellType cellType);
    void freeCellsByType(CellType cellType);
    FORCEINLINE uint32 posToIndex(const uint32 x, const uint32 y) const;
    FORCEINLINE uint32 posToIndex(const Position& pos) const;
};
}
