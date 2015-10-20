// Fill out your copyright notice in the Description page of Project Settings.

#include "Gloom2.h"
#include "Gloom2PlayerState.h"
#include "Gloom2HUD.h"
#include "UnrealNetwork.h"

AGloom2PlayerState::AGloom2PlayerState()
{
	
	Gloom2Player = Cast<AGloom2PlayerController>(Gloom2Player);
	numFrags = 0; // Number of frags the player has
	numDeaths = 0; // Number of deaths the player has
	numKills = 0; // Number of kills
	Team = 0;
	numTeamA = 0;
	numTeamH = 0;
	numTeamS = 0;
}

void AGloom2PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGloom2PlayerState, Team);
	/*DOREPLIFETIME(AGloom2PlayerState, numFrags);
	DOREPLIFETIME(AGloom2PlayerState, numKills);
	DOREPLIFETIME(AGloom2PlayerState, numDeaths);*/

}

void AGloom2PlayerState::Reset()
{
	Super::Reset();

	numFrags = 0; // Number of frags the player has
	numDeaths = 0; // Number of deaths the player has
	numKills = 0; // Number of kills
	Team = 0;

}

void AGloom2PlayerState::SetTeamNum()
{
	if (Gloom2Player)
	{
		AGloom2PlayerState *Gloom2PS = Cast<AGloom2PlayerState>(Gloom2Player->PlayerState);
		if (Gloom2PS)
		{
			Gloom2PS->Team = FMath::RandRange(0, (TeamMax - 1));
		}
	}
	Team = 0;

}


int32 AGloom2PlayerState::GetTeamNum()
{
	
	if (Gloom2Player)
	{
		AGloom2PlayerState *Gloom2PS = Cast<AGloom2PlayerState>(Gloom2Player->PlayerState);
		if (Gloom2PS)
		{
			return Gloom2PS->Team;
		}
	}
	return 0;
}

void AGloom2PlayerState::SetTeamMessage_Implementation(AGloom2PlayerController *Gloom2Player, const int32 &_team)
{
	AGloom2HUD *gloomHUD = Cast<AGloom2HUD>(Gloom2Player->GetHUD());
	if (gloomHUD && Gloom2Player)
	{
		gloomHUD->SetTeamMessage(_team);
	}

}

void AGloom2PlayerState::SetFragsMessage_Implementation(AGloom2PlayerController *Gloom2Player, const int32 &_frags)
{
	if (Gloom2Player)
	{
		AGloom2HUD *gloomHUD = Cast<AGloom2HUD>(Gloom2Player->GetHUD());
		if (gloomHUD && Gloom2Player)
		{
			gloomHUD->SetFragsMessage(_frags);
		}

	}



}

void AGloom2PlayerState::SetFrags()
{
	if (Gloom2Player)
	{
		AGloom2PlayerState *Gloom2PS = Cast<AGloom2PlayerState>(Gloom2Player->PlayerState);
		if (Gloom2PS)
		{
			Gloom2PS->numFrags = 5;
		}
	}
}

int32 AGloom2PlayerState::GetFrags()
{
	if (Gloom2Player)
	{
		AGloom2PlayerState *Gloom2PS = Cast<AGloom2PlayerState>(Gloom2Player->PlayerState);
		if (Gloom2PS)
		{
			return Gloom2PS->numFrags;
		}
	}
	return 0;
}

void AGloom2PlayerState::SetDeaths()
{
	if (Gloom2Player)
	{
		numDeaths = 0;
	}
}

int32 AGloom2PlayerState::GetDeaths()
{
	if (Gloom2Player)
	{
		return numDeaths;
	}
	return 0;
}

void AGloom2PlayerState::SetKills()
{
	if (Gloom2Player)
	{
		numKills = 0;
	}
}

int32 AGloom2PlayerState::GetKills()
{
	if (Gloom2Player)
	{
		return numKills;
	}
	return 0;
}




