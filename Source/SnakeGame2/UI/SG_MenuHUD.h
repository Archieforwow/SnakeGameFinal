// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SG_MenuHUD.generated.h"

class USG_StartGameWidget;

UCLASS()
class SNAKEGAME2_API ASG_MenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USG_StartGameWidget> StartGameWidgetClass;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	USG_StartGameWidget* StartGameWidget;
	
};
