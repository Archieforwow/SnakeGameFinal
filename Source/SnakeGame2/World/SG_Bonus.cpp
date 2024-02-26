// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SG_Bonus.h"
#include "Components/StaticMeshComponent.h"
#include "World/SG_WorldUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/SG_CameraShake.h"

ASG_Bonus::ASG_Bonus()
{
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<USceneComponent>("Bonus");
	check(Origin);
	SetRootComponent(Origin);

	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>("BonusMesh");
	check(BonusMesh);
	BonusMesh->SetupAttachment(Origin);

	BonusAudioComponent = CreateDefaultSubobject<UAudioComponent>("BonusAudioComponent");
	check(BonusAudioComponent);
	BonusAudioComponent->SetupAttachment(Origin);

}

void ASG_Bonus::SetModel(const TSharedPtr<SnakeGame::Bonus>& InBonus, int32 InCellSize, const SnakeGame::Dim& InDims)
{
	Bonus = InBonus;
	CellSize = InCellSize;
	Dims = InDims;

	SnakeGame::WorldUtils::ScaleMesh(BonusMesh, FVector(CellSize));

	SetActorHiddenInGame(false);
}

void ASG_Bonus::UpdateColors(const FLinearColor& Color)
{
	BonusColor = Color;
	if (auto* BonusMaterial = BonusMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		BonusMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ASG_Bonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetBonusWorldLocation());
}

void ASG_Bonus::Explode()
{
	if (UNiagaraComponent* NS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetBonusWorldLocation()))
	{
		NS->SetVariableLinearColor("BonusColor", BonusColor);
	}

	if (BonusAudioComponent)
	{
		BonusAudioComponent->Play();
	}

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(USG_CameraShake::StaticClass());
}

FVector ASG_Bonus::GetBonusWorldLocation() const
{
	if (!Bonus.IsValid()) return FVector::ZeroVector;
	return SnakeGame::WorldUtils::LinkPositionToVector(Bonus.Pin()->position(), CellSize, Dims);
}

void ASG_Bonus::Hide()
{
	SetActorHiddenInGame(true);
}

