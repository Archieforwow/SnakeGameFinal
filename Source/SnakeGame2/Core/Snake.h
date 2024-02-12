// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"

namespace SnakeGame
{
	class Snake
	{
	public:
		Snake(const Settings::Snake& settings);

		const TSnakeList& links() const { return m_links; }
		Position head() const { return m_links.GetHead()->GetValue(); }
		const TPositionPtr* body() const { return m_links.GetHead()->GetNextNode(); }

		void move(const Input& input);
		void increase();

	private:
		TSnakeList m_links;
		Input m_lastInput{Input::Default};
	};
}

