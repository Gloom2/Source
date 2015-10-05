// Fill out your copyright notice in the Description page of Project Settings.

#include "Gloom2.h"
#include "Gloom2PlayerState.h"
#include "UnrealNetwork.h"

void AGloom2PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGloom2PlayerState, Team);
	

}
uint8 AGloom2PlayerState::GetTeamNum(AController* Player)
{
	AGloom2PlayerState* PS = Cast<AGloom2PlayerState>(Player->PlayerState);
	if (PS)
	{
		PS->Team = 0;
		return PS->Team;
	}
	return 0;
}

int32 AGloom2PlayerState::GetFrags() const
{
	return numFrags;
}

int32 AGloom2PlayerState::GetDeaths() const
{
	return numDeaths;
}


