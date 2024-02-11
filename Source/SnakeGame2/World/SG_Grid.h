// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "World\SG_WorldTypes.h"
#include "SG_Grid.generated.h"

namespace SnakeGame
{
	class Grid;
}

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME2_API ASG_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Grid();
	virtual void Tick(float DeltaTime) override;

	void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, int32 CellSize);

	void UpdateColors(const FSnakeColors& Colors);

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GridMesh;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* GridMaterial;

	SnakeGame::Dim GridDim;
	int32 CellSize;
	int32 WorldWidth;
	int32 WorldHeight;

	void DrawGrid();
};
