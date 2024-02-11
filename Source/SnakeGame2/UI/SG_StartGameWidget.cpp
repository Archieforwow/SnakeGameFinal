// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SG_StartGameWidget.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SG_GameUserSettings.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

void USG_StartGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto* UserSettings = USG_GameUserSettings::Get();
	if (!UserSettings) return;

	check(StartGameButton);
	StartGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGame);

	/*if (SoundBase->IsValidLowLevel())
	{
		AudioComponent->SetSound(SoundBase);
	}

	AudioComponent->Play();*/

	check(CloseGameButton);
	CloseGameButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseGame);

	InitComboBox(
		GameSpeedComboBox,                                   //
		[&]() { return UserSettings->GameSpeedOptions(); },  //
		[&]() { return UserSettings->CurrentGameSpeedOption(); });

	InitComboBox(
		GridSizeComboBox,                                   //
		[&]() { return UserSettings->GridSizeOptions(); },  //
		[&]() { return UserSettings->CurrentGridSizeOption(); });

}

void USG_StartGameWidget::OnStartGame()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), GameLevel);
}

void USG_StartGameWidget::OnCloseGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void USG_StartGameWidget::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		SaveSettings();
	}
}

void USG_StartGameWidget::SaveSettings()
{
	if (auto* UserSettings = USG_GameUserSettings::Get())
	{
		const EGameSpeed GameSpeed = UserSettings->GameSpeedByName(GameSpeedComboBox->GetSelectedOption());
		const EGridSize GridSize = UserSettings->GridSizeByName(GridSizeComboBox->GetSelectedOption());
		UserSettings->SaveSnakeSettings(GameSpeed, GridSize);
	}
}

void USG_StartGameWidget::InitComboBox(UComboBoxString*& ComboBox, TFunction<TArray<FString>()> OptionsGetter, TFunction<FString()> CurrentOptionGetter)
{
	check(ComboBox);
	ComboBox->ClearOptions();
	for (const auto& Option : OptionsGetter())
	{
		ComboBox->AddOption(Option);
	}
	ComboBox->SetSelectedOption(CurrentOptionGetter());
	ComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnSelectionChanged);
}
