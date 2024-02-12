// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"

namespace SnakeGame
{
	class Grid
	{
	public:
		Grid(const Dim& dim);

		static Position center(uint32 width, uint32 height) { return Position(width / 2 + 1, height / 2 + 1); }

		Dim dim() const { return c_dim; }
		void update(const TPositionPtr* links, CellType cellType);
		void update(const Position& position, CellType cellType);
		bool hitTest(const Position& position, CellType cellType) const;

		UE_NODISCARD bool randomEmptyPosition(Position& position) const;


		void printDebug();

	private:
		const Dim c_dim;
		TArray<CellType> m_cells;
		TMap <CellType, TArray<int32>> m_indByType = 
		{
			{CellType::Snake, {}},
			{CellType::Wall, {}},
			{CellType::Food, {}},
			{CellType::Obstacle, {}},
		};

		void initWalls();
		void freeCellsByType(CellType cellType);
		void updateInternal(const Position& position, CellType cellType);
	
		FORCEINLINE uint32 posToIndex(uint32 x, uint32 y) const;
		FORCEINLINE uint32 posToIndex(const Position& position) const;
		FORCEINLINE Position indexToPos(uint32 index) const;

	};

}

