// Fill out your copyright notice in the Description page of Project Settings.


#include "Game.h"
#include "Grid.h"
#include "Core/Snake.h"
#include "Core/Food.h"
#include "Core/Obstacle.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All);

using namespace SnakeGame;

Game::Game(const Settings& settings): c_settings(settings)
{
	m_grid = MakeShared<Grid>(settings.GridSize);
	checkf(m_grid->dim().width / 2 >= settings.snake.defaultSize, TEXT("Snake initial length [%i] doesn't fit grid width [%i]"),
		settings.snake.defaultSize, m_grid->dim().width);
	m_snake = MakeShared<Snake>(settings.snake);
	m_food = MakeShared<Food>();
	m_obstacle = MakeShared<Obstacle>();
	updateGrid();
	generateFood();
	generateObstacle();
}

void Game::update(float deltaSeconds, const Input& input)
{
	if (m_gameOver || !updateTime(deltaSeconds)) return;

	move(input);

	if (died())
	{
		m_gameOver = true;
		dispatchEvent(GameplayEvent::GameOver);
		return;
	}

	if (foodTaken())
	{
		++m_score;
		m_snake->increase();
		dispatchEvent(GameplayEvent::FoodTaken);
		generateFood();
		generateObstacle();
	}

	if (obstacleHit())
	{
		m_gameOver = true;
		dispatchEvent(GameplayEvent::GameOver);
		return;
	}
}

void Game::move(const Input& input)
{
	m_snake->move(input);
	updateGrid();
}

void Game::generateFood()
{
	Position foodPosition;
	if (m_grid->randomEmptyPosition(foodPosition))
	{
		m_food->setPosition(foodPosition);
		m_grid->update(m_food->position(), CellType::Food);
	}

	else
	{
		m_gameOver = true;
		dispatchEvent(GameplayEvent::GameCompleted);

	}

}

void Game::generateObstacle()
{
	Position obstaclePosition;
	if (m_grid->randomEmptyPosition(obstaclePosition))
	{
		m_obstacle->setPosition(obstaclePosition);
		m_grid->update(m_obstacle->position(), CellType::Obstacle);
	}

	else
	{
		m_gameOver = true;
		dispatchEvent(GameplayEvent::GameOver);

	}
}

bool Game::foodTaken() const
{
	return m_grid->hitTest(m_snake->head(), CellType::Food);
}

bool Game::obstacleHit() const
{
	return m_grid->hitTest(m_snake->head(), CellType::Obstacle);
}

void Game::updateGrid()
{
	m_grid->update(m_snake->body(), CellType::Snake);
	//m_grid->printDebug();
}

bool Game::updateTime(float deltaSeconds)
{
	m_gameTime += deltaSeconds;
	m_moveSeconds += deltaSeconds;
	if(m_moveSeconds < c_settings.gameSpeed) return false;
	m_moveSeconds = 0.0f;
	return true;
}

bool Game::died() const
{
	return m_grid->hitTest(m_snake->head(), CellType::Wall) || //
		m_grid->hitTest(m_snake->head(), CellType::Snake) || //
		m_grid->hitTest(m_snake->head(), CellType::Obstacle);
}

void Game::subscribeOnGameplayEvent(GameplayEventCallback callback)
{
	m_gameplayEventCallbacks.Add(callback);
}

void Game::dispatchEvent(GameplayEvent Event)
{
	for (const auto& callback : m_gameplayEventCallbacks)
	{
		if (callback)
		{
			callback(Event);
		}
	}
}

