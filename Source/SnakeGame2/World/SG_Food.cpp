// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SG_Food.h"
#include "Components/StaticMeshComponent.h"
#include "World/SG_WorldUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/SG_CameraShake.h"

ASG_Food::ASG_Food()
{
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	check(Origin);
	SetRootComponent(Origin);

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>("FoodMesh");
	check(FoodMesh);
	FoodMesh->SetupAttachment(Origin);

	FoodAudioComponent = CreateDefaultSubobject<UAudioComponent>("FoodAudioComponent");
	check(FoodAudioComponent);
	FoodAudioComponent->SetupAttachment(Origin);
}

void ASG_Food::SetModel(const TSharedPtr<SnakeGame::Food>& InFood, int32 InCellSize, const SnakeGame::Dim& InDims)
{
	Food = InFood;
	CellSize = InCellSize;
	Dims = InDims;

	SnakeGame::WorldUtils::ScaleMesh(FoodMesh, FVector(CellSize));

	SetActorHiddenInGame(false);
}

void ASG_Food::UpdateColors(const FLinearColor& Color)
{
	FoodColor = Color;
	if (auto* FoodMaterial = FoodMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		FoodMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ASG_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetFoodWorldLocation());

}

void ASG_Food::Explode()
{
	if (UNiagaraComponent* NS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetFoodWorldLocation()))
	{
		NS->SetVariableLinearColor("SnakeColor", FoodColor);
	}

	if (FoodAudioComponent)
	{
		FoodAudioComponent->Play();
	}

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(USG_CameraShake::StaticClass());
}

FVector ASG_Food::GetFoodWorldLocation() const
{
	if (!Food.IsValid()) return FVector::ZeroVector;
	return SnakeGame::WorldUtils::LinkPositionToVector(Food.Pin()->position(), CellSize, Dims);
}

void ASG_Food::Hide()
{
	SetActorHiddenInGame(true);
}