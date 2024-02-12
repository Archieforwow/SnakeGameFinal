// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"

namespace SnakeGame
{
	class Grid;
	class Snake;
	class Food;
	class Obstacle;

	class Game
	{
	public:
		Game(const Settings& settings);

		TSharedPtr<Grid> grid() const { return m_grid; }
		TSharedPtr<Snake> snake() const { return m_snake; }
		TSharedPtr<Food> food() const { return m_food; }
		TSharedPtr<Obstacle> obstacle() const { return m_obstacle; }

		void update(float deltaSeconds, const Input& input);
		uint32 score() const { return m_score; }
		float gameTime() const { return m_gameTime; }
		void subscribeOnGameplayEvent(GameplayEventCallback callback);

	private:
		const Settings c_settings;
		TSharedPtr<Grid> m_grid;
		TSharedPtr<Snake> m_snake;
		TSharedPtr<Food> m_food;
		TSharedPtr<Obstacle> m_obstacle;

		float m_moveSeconds{0.0f};
		bool m_gameOver{false};
		uint32 m_score{0};
		float m_gameTime{0.0f};

		TArray<GameplayEventCallback> m_gameplayEventCallbacks;

		void updateGrid();
		bool updateTime(float deltaSeconds);
		bool died() const;

		void move(const Input& input);
		void generateFood();
		bool foodTaken() const;

		void generateObstacle();
		bool obstacleHit() const;

		FORCEINLINE void dispatchEvent(GameplayEvent Event);
	};


}
