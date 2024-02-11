// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SG_HUD.generated.h"

class USG_GameplayWidget;
class USG_GameOverWidget;

UENUM()
enum class EUIGameState : uint8
{
	GameInProgress = 0,
	GameOver,
	GameCompleted
};

namespace SnakeGame
{
	class Game;
}

UCLASS()
class ASG_HUD : public AHUD
{
	GENERATED_BODY()

public:
	ASG_HUD();

	void SetModel(const TSharedPtr <SnakeGame::Game>& Game);
	void SetInputKeyNames(const FString& ResetGameKeyName);
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USG_GameplayWidget> GameplayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USG_GameOverWidget> GameOverWidgetClass;
	
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USG_GameplayWidget* GameplayWidget;

	UPROPERTY()
	USG_GameOverWidget* GameOverWidget;

	UPROPERTY()
	TMap <EUIGameState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	TWeakPtr<SnakeGame::Game> Game;

	EUIGameState GameState;

	void SetUIGameState(EUIGameState GameState);
};
