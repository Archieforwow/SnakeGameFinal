// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/SG_MenuGameMode.h"
#include "World/SG_WorldUtils.h"

void ASG_MenuGameMode::StartPlay()
{
    Super::StartPlay();

    SnakeGame::WorldUtils::SetUIInput(GetWorld(), true);
}