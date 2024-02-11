// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Food.h"
#include "SG_Food.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SNAKEGAME2_API ASG_Food : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Food();

	void SetModel(const TSharedPtr<SnakeGame::Food>& Food, int32 CellSize, const SnakeGame::Dim& Dims);
	void UpdateColors(const FLinearColor& Color);
	void Explode();
	void Hide();

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FoodMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ExplosionEffect;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* FoodAudioComponent;

public:	
	virtual void Tick(float DeltaTime) override;

private:

	TWeakPtr<SnakeGame::Food> Food;
	int32 CellSize;
	SnakeGame::Dim Dims;
	FLinearColor FoodColor;

	FVector GetFoodWorldLocation() const;
};
