// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Snake.h"
#include "World/SG_WorldTypes.h"
#include "Types.h"
#include "SG_Snake.generated.h"

class ASG_SnakeLink;

UCLASS()
class SNAKEGAME2_API ASG_Snake : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Snake();

	void SetModel(const TSharedPtr<SnakeGame::Snake>& Snake, int32 CellSize, const SnakeGame::Dim& Dims);
	void UpdateColors(const FSnakeColors& Colors);
	void Explode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ASG_SnakeLink> SnakeHeadClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ASG_SnakeLink> SnakeLinkClass;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	TWeakPtr<SnakeGame::Snake> Snake;
	int32 CellSize;
	SnakeGame::Dim Dims;

	FLinearColor SnakeLinkColor;

	UPROPERTY()
	TArray<ASG_SnakeLink*> SnakeLinks;

};
