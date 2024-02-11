// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Types.h"
#include "SG_Pawn.generated.h"

class UCameraComponent;
class UCameraShakeBase;
class UCameraShakeSourceComponent;

UCLASS()
class SNAKEGAME2_API ASG_Pawn : public APawn
{
	GENERATED_BODY()

public:
	ASG_Pawn();

	void UpdateLocation(const SnakeGame::Dim& Dim, int32 CellSize, const FTransform& GridOrigin);

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

private:
	SnakeGame::Dim Dim;
	int32 CellSize;
	FTransform GridOrigin;
	FDelegateHandle ResizeHandle;

	void OnViewportResized(FViewport* Viewport, uint32 Val);
};
