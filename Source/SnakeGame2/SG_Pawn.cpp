// Fill out your copyright notice in the Description page of Project Settings.


#include "SG_Pawn.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "Camera/CameraShakeBase.h"

namespace
{
	float FOVTan(float FOVDegrees)
	{
		return FMath::Tan(FMath::DegreesToRadians(FOVDegrees * 0.5f));
	}

	float VerticalFOV(float HorFOVDegrees, float ViewportAspectHW)
	{
		return FMath::RadiansToDegrees(2.0f * FMath::Atan(FMath::Tan(FMath::DegreesToRadians(HorFOVDegrees) * 0.5f) * ViewportAspectHW));
	}

	UPROPERTY(EditDefaultsOnly)
	constexpr float GridMargin = 2.0f;
}

ASG_Pawn::ASG_Pawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	check(Origin);
	SetRootComponent(Origin);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	check(Camera);
	Camera->SetupAttachment(Origin);
}


void ASG_Pawn::UpdateLocation(const SnakeGame::Dim& InDim, int32 InCellSize, const FTransform& InGridOrigin)
{
	Dim = InDim;
	CellSize = InCellSize;
	GridOrigin = InGridOrigin;

	check(GEngine);
	check(GEngine->GameViewport);
	check(GEngine->GameViewport->Viewport);

	auto* Viewport = GEngine->GameViewport->Viewport;
	Viewport->ViewportResizedEvent.Remove(ResizeHandle);
	ResizeHandle = Viewport->ViewportResizedEvent.AddUObject(this, &ASG_Pawn::OnViewportResized);

#if WITH_EDITOR
	OnViewportResized(Viewport, 0);
#endif
}

void ASG_Pawn::OnViewportResized(FViewport* Viewport, uint32 Val)
{
	if (!Viewport || Viewport->GetSizeXY().Y == 0 || Dim.height == 0) return;

	const float WorldWidth = Dim.width * CellSize;
	const float WorldHeight = Dim.height * CellSize;

	float LocationZ = 0.0f;

	const float ViewportAspect = static_cast<float>(Viewport->GetSizeXY().X) / Viewport->GetSizeXY().Y;
	const float GridAspect = static_cast<float>(Dim.width) / Dim.height;

	if (ViewportAspect <= GridAspect)
	{
		const float MarginWidth = (Dim.width + GridMargin) * CellSize;
		LocationZ = MarginWidth / FOVTan(Camera->FieldOfView);
	}
	else
	{
		check(ViewportAspect);
		const float VFOV = VerticalFOV(Camera->FieldOfView, 1.0f / ViewportAspect);
		const float MarginHeight = (Dim.height + GridMargin) * CellSize;
		LocationZ = MarginHeight / FOVTan(VFOV);
	}

	const FVector NewPawnLocation = GridOrigin.GetLocation() + 0.5f * FVector(WorldHeight, WorldWidth, LocationZ);
	SetActorLocation(NewPawnLocation);

}

