// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Gloom2.h"
#include "Gloom2GameMode.h"
#include "Gloom2HUD.h"
#include "Gloom2Character.h"
#include "Gloom2PlayerController.h"
#include "Gloom2PlayerState.h"
#include "Gloom2PlayerStart.h"
#include "Gloom2HumanStart.h"
#include "Gloom2AlienStart.h"

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
		AGloom2HUD * MsgHUD = Cast<AGloom2HUD>(NewPlayer->GetHUD());
		AGloom2PlayerState * PS = Cast<AGloom2PlayerState>(NewPlayer->PlayerState);
		if (PS && GameState) //If PlayerState and GameState are Valid
		{
			uint8 numHumans = 0; //Number of Humans
			uint8 numAliens = 0; //Number of Aliens
			for (APlayerState * It : GameState->PlayerArray)
			{
				AGloom2PlayerState * OtherPS = Cast<AGloom2PlayerState>(It);
				OtherPS->Team = 1;
				//if (PS->Team == 0)
				//{
				//	/*NewPlayer->PlayerState->bIsSpectator = true;
				//	NewPlayer->ChangeState(NAME_Spectating);
				//	if (MsgHUD)
				//	{
				//		MsgHUD->SetMessage("You have joined the spectators.");
				//	}*/
				//}
				if (OtherPS->Team == 1)
				{
					NewPlayer->PlayerState->bIsSpectator = false;
					NewPlayer->ChangeState(NAME_Playing);
					if (MsgHUD)
					{
						MsgHUD->SetMessage("You have joined the Human team.");
					}
					numHumans++;

				}
				if (OtherPS->Team == 2)
				{
					NewPlayer->PlayerState->bIsSpectator = false;
					NewPlayer->ChangeState(NAME_Playing);
					if (MsgHUD)
					{
						MsgHUD->SetMessage("You have joined the Alien team.");
					}
					numAliens++;
				}
						


			}


		}



	}




}
/*void AGloom2GameMode::PostLogin(APlayerController * NewPlayer) //This Function works (I think)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		AGloom2HUD * MsgHUD = Cast <AGloom2HUD>(NewPlayer->GetHUD());
		AGloom2PlayerState * PS = Cast<AGloom2PlayerState>(NewPlayer->PlayerState);
		if (PS && GameState)
		{
			uint8 NumTeamA = 0; // Number of Alien Players
			uint8 NumTeamH = 0; // Number of Human Players
			
			for (APlayerState * It : GameState->PlayerArray)
			{
				AGloom2PlayerState * OtherPS = Cast<AGloom2PlayerState>(It);
				if (OtherPS)
				{
					if (OtherPS->Team = 1)
					{
						NumTeamH++; // Adds 1 to Human Count
						if (MsgHUD)
						{
							MsgHUD->SetMessage("You have joined the Human team.");
							
						}
						
					}
					else
					{
						NumTeamA++; // Adds 1 to Alien Count
						if (MsgHUD)
						{
							MsgHUD->SetMessage("You have joined the Alien team.");
						}
						
					}
				}
			}
			if (NumTeamA > NumTeamH)
			{
				PS->Team = 1;
			}
		}
	}


}*/


AActor * AGloom2GameMode::ChoosePlayerStart(AController * Player) //Choose the spawns for the player
{
	
	if (Player) // If player is valid
	{
		AGloom2PlayerState * PS = Cast<AGloom2PlayerState>(Player->PlayerState);
		if (PS)
		{
			TArray<AGloom2HumanStart *> HStarts; //Human Starts (Gloom2HumanStart)
			TArray<AGloom2AlienStart *> AStarts; //Alien Starts (Gloom2AlienStart)
			TArray<AGloom2PlayerStart *> SStarts; //Spectator Starts (Should just be Gloom2PlayerStart)
			if (PS->Team == 1)
			{
				for (TActorIterator<AGloom2HumanStart> StartItr(GetWorld()); StartItr; ++StartItr)
				{
					if (StartItr->Team == PS->Team)
					{
						HStarts.Add(*StartItr);
					}
				}
				return HStarts[FMath::RandRange(0, HStarts.Num() - 1)];

			}
			else if (PS->Team == 2)
			{
				for (TActorIterator<AGloom2AlienStart> StartItr(GetWorld()); StartItr; ++StartItr)
				{
					if (StartItr->Team == PS->Team)
					{

						AStarts.Add(*StartItr);
					}
				}
				return AStarts[FMath::RandRange(0, AStarts.Num() - 1)];
			}
			else
			{
				for (TActorIterator<AGloom2PlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
				{
					if (StartItr->Team == PS->Team)
					{
						SStarts.Add(*StartItr);

					}
				}
				return SStarts[FMath::RandRange(0, SStarts.Num() - 1)];


			}
			
		}
	}
	return NULL;
}
