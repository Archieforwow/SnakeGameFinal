// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Bonus.h"
#include "SG_Bonus.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SNAKEGAME2_API ASG_Bonus : public AActor
{
	GENERATED_BODY()

public:
	ASG_Bonus();
	virtual void Tick(float DeltaTime) override;

	void SetModel(const TSharedPtr<SnakeGame::Bonus>& Bonus, int32 CellSize, const SnakeGame::Dim& Dims);
	void UpdateColors(const FLinearColor& Color);
	void Explode();
	void Hide();

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BonusMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ExplosionEffect;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* BonusAudioComponent;

private:

	TWeakPtr<SnakeGame::Bonus> Bonus;
	int32 CellSize;
	SnakeGame::Dim Dims;
	FLinearColor BonusColor;

	FVector GetBonusWorldLocation() const;
};

