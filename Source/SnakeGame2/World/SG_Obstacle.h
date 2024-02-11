// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Obstacle.h"
#include "SG_Obstacle.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SNAKEGAME2_API ASG_Obstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Obstacle();
	virtual void Tick(float DeltaTime) override;

	void SetModel(const TSharedPtr<SnakeGame::Obstacle>& Obstacle, int32 CellSize, const SnakeGame::Dim& Dims);
	void UpdateColors(const FLinearColor& Color);
	void Explode();
	void Hide();

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ExplosionEffect;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* ObstacleAudioComponent;

private:

	TWeakPtr<SnakeGame::Obstacle> Obstacle;
	int32 CellSize;
	SnakeGame::Dim Dims;
	FLinearColor ObstacleColor;

	FVector GetObstacleWorldLocation() const;
};
