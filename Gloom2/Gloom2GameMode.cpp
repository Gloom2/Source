// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Gloom2.h"
#include "Gloom2GameMode.h"
#include "Gloom2HUD.h"
#include "Gloom2Character.h"
#include "Gloom2PlayerController.h"
#include "Gloom2PlayerState.h"
#include "Gloom2PlayerStart.h"

AGloom2GameMode::AGloom2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGloom2HUD::StaticClass();

	PlayerControllerClass = AGloom2PlayerController::StaticClass(); //Using the Gloom 2 Player Controller vs the Default Player Controller
	PlayerStateClass = AGloom2PlayerState::StaticClass(); // Using the Gloom 2 Player State vs the Default Player State

}

void AGloom2GameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		AGloom2PlayerState * PS = Cast<AGloom2PlayerState>(NewPlayer->PlayerState);
		if (PS && GameState)
		{
			uint8 NumTeamA = 0;
			uint8 NumTeamB = 0;
			
			for (APlayerState * It : GameState->PlayerArray)
			{
				AGloom2PlayerState * OtherPS = Cast<AGloom2PlayerState>(It);
				if (OtherPS)
				{
					if (OtherPS->bTeamB)
					{
						NumTeamB++;

					}
					else
					{
						NumTeamA++;
					}
				}
			}
			if (NumTeamA > NumTeamB)
			{
				PS->bTeamB = true;
			}
		}
	}


}

AActor * AGloom2GameMode::ChoosePlayerStart(AController * Player)
{
	
	if (Player)
	{
		AGloom2PlayerState * PS = Cast<AGloom2PlayerState>(Player->PlayerState);
		if (PS)
		{
			TArray<AGloom2PlayerStart *> Starts;
			for (TActorIterator<AGloom2PlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
			{
				if (StartItr->bTeamB == PS->bTeamB)
				{
					Starts.Add(*StartItr);
				}
			}
			return Starts[FMath::RandRange(0, Starts.Num() - 1)];
		}
	}
	return NULL;
}
