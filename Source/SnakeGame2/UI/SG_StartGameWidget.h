// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_StartGameWidget.generated.h"

class UButton;
class UComboBoxString;
class USoundBase;
class UAudioComponent;

UCLASS()
class USG_StartGameWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundBase* SoundBase;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* AudioComponent;

	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseGameButton;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* GameSpeedComboBox;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* GridSizeComboBox;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> GameLevel;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnCloseGame();

	UFUNCTION()
	void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	void SaveSettings();

	void InitComboBox(UComboBoxString*& ComboBox, TFunction<TArray<FString>()> OptionsGetter, TFunction<FString()> CurrentOptionGetter);
};
