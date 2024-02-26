// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core/Game.h"
#include "InputActionValue.h"
#include "Engine/DataTable.h"
#include "SG_GameMode.generated.h"

class ASG_Grid;
class ASG_Snake;
class AExponentialHeightFog;
class UInputAction;
class UInputMappingContext;
class ASG_Food;
class ASG_HUD;
class ASG_Obstacle;
class ASG_Bonus;

UCLASS()
class SNAKEGAME2_API ASG_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASG_GameMode();
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	bool bOverrideUserSettings {false};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100", EditCondition = "bOverrideUserSettings", EditConditionHides), Category = "Settings")
	FIntPoint GridSize {10, 10};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100", EditCondition = "bOverrideUserSettings", EditConditionHides), Category = "Settings")
	int32 CellSize {10};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "4", ClampMax = "10", EditCondition = "bOverrideUserSettings", EditConditionHides), Category = "Settings")
	int32 SnakeDefaultSize {5};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.01", ClampMax = "10", EditCondition = "bOverrideUserSettings", EditConditionHides), Category = "Settings")
	float GameSpeed{1.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<ASG_Grid> GridVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<ASG_Snake> SnakeVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<ASG_Food> FoodVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<ASG_Obstacle> ObstacleVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<ASG_Bonus> BonusVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	UDataTable* ColorsTable;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	UInputAction* MoveForwardInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	UInputAction* MoveRightInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	UInputAction* ResetGameInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	UInputMappingContext* InputMapping;

private:
	UPROPERTY()
	ASG_Grid* GridVisual;

	UPROPERTY()
	ASG_Snake* SnakeVisual;

	UPROPERTY()
	ASG_Food* FoodVisual;

	UPROPERTY()
	ASG_Obstacle* ObstacleVisual;

	UPROPERTY()
	ASG_Bonus* BonusVisual;

	UPROPERTY()
	AExponentialHeightFog* Fog;

	UPROPERTY()
	ASG_HUD* HUD;

	UFUNCTION(Exec, Category = "Console command")
	void NextColor();

	TSharedPtr<SnakeGame::Game> Game;
	int32 ColorTableIndex{0};
	SnakeGame::Input SnakeInput{SnakeGame::Input::Default};

	SnakeGame::Settings MakeSettings() const;

	void FindFog();
	void UpdateColors();

	//enhanced input
	void SetupInput();
	void OnMoveForward(const FInputActionValue& Value);
	void OnMoveRight(const FInputActionValue& Value);
	void OnGameReset(const FInputActionValue& Value);

	void SubscribeOnGameEvents();

};
