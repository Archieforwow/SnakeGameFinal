#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"
#include "Components/StaticMeshComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedActionKeyMapping.h"

namespace SnakeGame
{
	class WorldUtils
	{
	public:
		static FVector LinkPositionToVector(const SnakeGame::Position& Position, int32 CellSize, const SnakeGame::Dim& Dims)
		{
			return FVector((Dims.height - 1 - Position.y) * CellSize, Position.x * CellSize, 0.0f) + FVector(CellSize * 0.5f);
		}

		static void ScaleMesh(UStaticMeshComponent* Mesh, const FVector& WorldSize)
		{
			if (Mesh && Mesh->GetStaticMesh())
			{
				const FBox Box = Mesh->GetStaticMesh()->GetBoundingBox();
				const auto Size = Box.GetSize();

				check(!Size.IsZero());
				Mesh->SetRelativeScale3D(FVector(WorldSize / Size));
			}
		
		}

		static FText FormatSeconds(float TimeSeconds)
		{
			const int32 TotalSeconds = FMath::RoundToInt(TimeSeconds);
			const int32 Minutes = TotalSeconds / 60;
			const int32 Seconds = TotalSeconds % 60;
			const FString FormattedTime = FString::Printf(TEXT("%02i:%02i"), Minutes, Seconds);
			return FText::FromString(FormattedTime);
		}

		static FText FormatScore(uint32 Score)
		{
			const FString FormattedScore = FString::Printf(TEXT("%02i"), Score);
			return FText::FromString(FormattedScore);
		}

		static FString FindActionKeyName(const UInputMappingContext* InputMapping, const UInputAction* Action)
		{
			auto* FoundAcionKeyMapping = InputMapping->GetMappings().FindByPredicate([&](const FEnhancedActionKeyMapping& Mapping)  //
				{ return Mapping.Action == Action; });

			return FoundAcionKeyMapping ? FoundAcionKeyMapping->Key.GetDisplayName().ToString() : FString{};
		}

		static void SetUIInput(UWorld* World, bool Enabled)
		{
			if (!World) return;
			if (auto* PC = World->GetFirstPlayerController())
			{
				PC->SetShowMouseCursor(Enabled);
				Enabled ? PC->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false)) : PC->SetInputMode(FInputModeGameOnly());
			}
		}
	};
}