// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SG_SnakeLink.h"
#include "Components\StaticMeshComponent.h"
#include "SG_WorldUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ASG_SnakeLink::ASG_SnakeLink()
{
	PrimaryActorTick.bCanEverTick = false;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	check(Origin);
	SetRootComponent(Origin);

	LinkMesh = CreateDefaultSubobject<UStaticMeshComponent>("LinkMesh");
	check(LinkMesh);
	LinkMesh->SetupAttachment(Origin);
}

void ASG_SnakeLink::UpdateColor(const FLinearColor& Color)
{
	LinkColor = Color;
	if (auto* LinkMaterial = LinkMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		LinkMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ASG_SnakeLink::UpdateScale(int32 CellSize)
{
	SnakeGame::WorldUtils::ScaleMesh(LinkMesh, FVector(CellSize));
}

void ASG_SnakeLink::Explode()
{
	if (UNiagaraComponent* NS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation()))
	{
		NS->SetVariableLinearColor("LinkColor", LinkColor);
	}

	SetActorHiddenInGame(true);
}


