// Fill out your copyright notice in the Description page of Project Settings.

#include "Gloom2.h"
#include "Gloom2PlayerController.h"
#include "Gloom2HUD.h"
#include "Gloom2PlayerState.h"
#include "UnrealNetwork.h"


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

void AGloom2PlayerController::ClientSetMessage_Implementation(AGloom2PlayerController *Gloom2Player, const FString &_message)
{
	AGloom2HUD *gloomHUD = Cast<AGloom2HUD>(Gloom2Player->GetHUD());
	if (gloomHUD && Gloom2Player)
	{
		gloomHUD->SetMessage(_message);
	}

}

//void AGloom2PlayerController::SetInfoHUD(AGloom2PlayerController *Gloom2Player)
//{
//	AGloom2PlayerState* PS = Cast<AGloom2PlayerState>(Gloom2Player->PlayerState);
//	AGloom2HUD* gloom2HUD = Cast<AGloom2HUD>(Gloom2Player->GetHUD());
//	int32 frags = PS->GetFrags(Gloom2Player);
//	uint8 teamNum = PS->GetTeamNum(Gloom2Player);
//
//	if (gloom2HUD && PS)
//	{
//		gloom2HUD->SetGloomHUD(Gloom2Player);
//	}
//
//
//}