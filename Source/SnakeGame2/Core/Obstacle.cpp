// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Obstacle.h"

using namespace SnakeGame;

void Obstacle::setPosition(const Position& position)
{
    m_position = position;
}

Position Obstacle::position() const
{
	return m_position;
}
