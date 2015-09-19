// Fill out your copyright notice in the Description page of Project Settings.

#include "Gloom2.h"
#include "Gloom2PlayerController.h"

void AGloom2PlayerController::OnKilled()
{
	UnPossess();
	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &AGloom2PlayerController::Respawn, 5.f);

}

void AGloom2PlayerController::Respawn()
{
	AGameMode * GameMode = GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		APawn * NewPawn = GameMode->SpawnDefaultPawnFor(this, GameMode->ChoosePlayerStart(this));
		Possess(NewPawn);
	}

}