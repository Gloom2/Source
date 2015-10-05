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


	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		AGloom2PlayerController *currentPC = Cast<AGloom2PlayerController>(*Iterator);
		if (currentPC && currentPC != NewPlayer)
		{
			AGloom2PlayerState *currentPS = Cast<AGloom2PlayerState>(currentPC->PlayerState);
			uint8 Team = currentPS->GetTeamNum(NewPlayer);
			if (currentPS)
			{
				if (Team == 1)
				{
					
					currentPC->ClientSetMessage(currentPC, "You have joined the Human team.");
					UpdateTeamCount(currentPC);
				}
					
				else if (Team == 2)
				{
					
					currentPC->ClientSetMessage(currentPC, "You have joined the Alien team.");
					UpdateTeamCount(currentPC);
				}
				else
				{
					currentPC->ClientSetMessage(currentPC, "You have joined the Spectators.");
					UpdateTeamCount(currentPC);
				}
					
				
			}
		}
	}

}

AActor * AGloom2GameMode::ChoosePlayerStart_Implementation(AController * Player) //Choose the spawns for the player
{	
	if (Player) // If player is valid
	{
		AGloom2PlayerState * PS = Cast<AGloom2PlayerState>(Player->PlayerState);
		if (PS)
		{
			TArray<AGloom2HumanStart *> HStarts; //Human Starts (Gloom2HumanStart)
			TArray<AGloom2AlienStart *> AStarts; //Alien Starts (Gloom2AlienStart)
			TArray<AGloom2PlayerStart *> SStarts; //Spectator Starts (Should just be Gloom2PlayerStart)
			uint8 Team = PS->GetTeamNum(Player);

			if (Team == 1)
			{
				for (TActorIterator<AGloom2HumanStart> StartItr(GetWorld()); StartItr; ++StartItr)
				{
					AGloom2HumanStart* TestSpawn = *StartItr;
					if (IsSpawnpointAllowed(TestSpawn, Player))
					{
						HStarts.Add(TestSpawn);
					}
				}
				return HStarts[FMath::RandRange(0, HStarts.Num() - 1)];
			}
			else if (Team == 2)
			{
				for (TActorIterator<AGloom2AlienStart> StartItr(GetWorld()); StartItr; ++StartItr)
				{
					AGloom2AlienStart* TestSpawn = *StartItr;
					if (IsSpawnpointAllowed(TestSpawn, Player))
					{
						AStarts.Add(TestSpawn);
					}
				}
				return AStarts[FMath::RandRange(0, AStarts.Num() - 1)];
			}
			else
			{
				for (TActorIterator<AGloom2PlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
				{
					AGloom2PlayerStart* TestSpawn = *StartItr;
					if (IsSpawnpointAllowed(TestSpawn, Player))
					{
						SStarts.Add(TestSpawn);
					}
				}
				return SStarts[FMath::RandRange(0, SStarts.Num() - 1)];
			}			
		}
	}
	return NULL;
}

bool AGloom2GameMode::IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const
{
	
	if (Player)
	{
		AGloom2PlayerState * PS = Cast<AGloom2PlayerState>(Player->PlayerState);
		uint8 Team = PS->GetTeamNum(Player);
		if (Team == 1)
		{
			AGloom2HumanStart * PlayerStart = Cast<AGloom2HumanStart>(SpawnPoint);
			if (PS && PlayerStart && Team != 1)
			{
				return false;
			}
			else { return true; }
		}
		else if (Team == 2)
		{
			AGloom2AlienStart * PlayerStart = Cast<AGloom2AlienStart>(SpawnPoint);
			if (PS && PlayerStart && Team != 2)
			{
				return false;
			}
			else { return true; }
		}
		else
		{
			AGloom2PlayerStart * PlayerStart = Cast<AGloom2PlayerStart>(SpawnPoint);
			if (PS && PlayerStart && Team != 0)
			{
				return false;
			}
			else { return true; }
		}
	}
	return true;
}

void AGloom2GameMode::UpdateTeamCount(AController* Player) // Update the count of team members
{
	if (Player)
	{
		AGloom2PlayerState * PS = Cast<AGloom2PlayerState>(Player->PlayerState);
		uint8 Team = PS->GetTeamNum(Player);
		if (PS)
		{
			if (Team == 0)
			{
				numTeamS++; //Increment the spectator team by 1
			}
			else if (Team == 1)
			{
				numTeamH++; //Increment the human team by 1
			}
			else
			{
				numTeamA++; //Increment the alien team by 1
			}
		}

	}

}
