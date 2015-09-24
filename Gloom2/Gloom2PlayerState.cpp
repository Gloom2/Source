// Fill out your copyright notice in the Description page of Project Settings.

#include "Gloom2.h"
#include "Gloom2PlayerState.h"
#include "UnrealNetwork.h"

void AGloom2PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AGloom2PlayerState, Team);
	DOREPLIFETIME(AGloom2PlayerState, bHuman);
	

}


