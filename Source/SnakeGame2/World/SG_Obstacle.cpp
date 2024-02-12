// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SG_Obstacle.h"
#include "Components/StaticMeshComponent.h"
#include "World/SG_WorldUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"


ASG_Obstacle::ASG_Obstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	check(Origin);
	SetRootComponent(Origin);

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObstacleMesh");
	check(ObstacleMesh);
	ObstacleMesh->SetupAttachment(Origin);

	ObstacleAudioComponent = CreateDefaultSubobject<UAudioComponent>("ObstacleAudioComponent");
	check(ObstacleAudioComponent);
	ObstacleAudioComponent->SetupAttachment(Origin);
}

void ASG_Obstacle::SetModel(const TSharedPtr<SnakeGame::Obstacle>& InObstacle, int32 InCellSize, const SnakeGame::Dim& InDims)
{
	Obstacle = InObstacle;
	CellSize = InCellSize;
	Dims = InDims;

	SnakeGame::WorldUtils::ScaleMesh(ObstacleMesh, FVector(CellSize));

	SetActorHiddenInGame(false);
}

void ASG_Obstacle::UpdateColors(const FLinearColor& Color)
{
	ObstacleColor = Color;
	if (auto* ObstacleMaterial = ObstacleMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		ObstacleMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ASG_Obstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetObstacleWorldLocation());

}

void ASG_Obstacle::Explode()
{
	if (UNiagaraComponent* NS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetObstacleWorldLocation()))
	{
		NS->SetVariableLinearColor("SnakeColor", ObstacleColor);
	}

	if (ObstacleAudioComponent)
	{
		ObstacleAudioComponent->Play();
	}
}

FVector ASG_Obstacle::GetObstacleWorldLocation() const
{
	if (!Obstacle.IsValid()) return FVector::ZeroVector;
	return SnakeGame::WorldUtils::LinkPositionToVector(Obstacle.Pin()->position(), CellSize, Dims);
}

void ASG_Obstacle::Hide()
{
	SetActorHiddenInGame(true);
}

