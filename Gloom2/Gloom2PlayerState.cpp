// Fill out your copyright notice in the Description page of Project Settings.

#include "Gloom2.h"
#include "Gloom2PlayerState.h"
#include "Gloom2HUD.h"
#include "UnrealNetwork.h"

AGloom2PlayerState::AGloom2PlayerState()
{
	
	Gloom2Player = Cast<AGloom2PlayerController>(Gloom2Player);
	numFrags = 5; // Number of frags the player has
	numDeaths = 0; // Number of deaths the player has
	numKills = 0; // Number of kills
	Team = 2; // Team number
	numTeamA = 0; // Number of Alien Team Members
	numTeamH = 0; // Number of Human Team Members
	numTeamS = 0; // Number of Observer Team Members
}

void AGloom2PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGloom2PlayerState, Team); // Team is replicated to the clients

}

void AGloom2PlayerState::Reset()
{
	Super::Reset();

	numFrags = 0; // Number of frags the player has
	numDeaths = 0; // Number of deaths the player has
	numKills = 0; // Number of kills
	Team = 0; // Default set to spectator (Observer)

}

void AGloom2PlayerState::SetTeamNum() // Randomly assigns team
{
	if (Gloom2Player)
	{
		Team = FMath::RandRange(0, (TeamMax - 1));
	}

}


int32 AGloom2PlayerState::GetTeamNum() // Returns the team number
{
	
	if (Gloom2Player)
	{
		return Team;
	}
	return Team;
}

// Set the team name message to be displayed at the HUD (top left)
void AGloom2PlayerState::SetTeamMessage_Implementation(AGloom2PlayerController *Gloom2Player, const int32 &_team)
{
	AGloom2HUD *gloomHUD = Cast<AGloom2HUD>(Gloom2Player->GetHUD());
	if (gloomHUD && Gloom2Player)
	{
		gloomHUD->SetTeamMessage(_team);
	}

}

// Set the frags message (top right) of HUD
void AGloom2PlayerState::SetFragsMessage_Implementation(AGloom2PlayerController *Gloom2Player, const int32 &_frags)
{
	if (Gloom2Player)
	{
		AGloom2HUD *gloomHUD = Cast<AGloom2HUD>(Gloom2Player->GetHUD());
		if (gloomHUD)
		{
			gloomHUD->SetFragsMessage(_frags);
		}

	}



}

// Set the number of frags to be tested
void AGloom2PlayerState::SetFrags()
{
	if (Gloom2Player)
	{

		numFrags = 5;
	}
}

// Return the amount of frags
int32 AGloom2PlayerState::GetFrags()
{
	if (Gloom2Player)
	{
		return numFrags;
	}
	return numFrags;
}

// Set the number of deaths for testing
void AGloom2PlayerState::SetDeaths()
{
	if (Gloom2Player)
	{
		numDeaths = 0;
	}
}

// Return the amount of deaths
int32 AGloom2PlayerState::GetDeaths()
{
	if (Gloom2Player)
	{
		return numDeaths;
	}
	return numDeaths;
}

// Set the amount of kills for testing
void AGloom2PlayerState::SetKills()
{
	if (Gloom2Player)
	{
		numKills = 0;
	}
}

// Return the amount of kills
int32 AGloom2PlayerState::GetKills()
{
	if (Gloom2Player)
	{
		return numKills;
	}
	return numKills;
}




