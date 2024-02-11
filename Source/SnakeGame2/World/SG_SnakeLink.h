// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SG_SnakeLink.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class SNAKEGAME2_API ASG_SnakeLink : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_SnakeLink();

	void UpdateColor(const FLinearColor& Color);
	void UpdateScale(int32 CellSize);
	void Explode();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LinkMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ExplosionEffect;

private:
	FLinearColor LinkColor;
};
