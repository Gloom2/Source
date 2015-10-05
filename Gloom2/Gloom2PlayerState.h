// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "Gloom2PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GLOOM2_API AGloom2PlayerState : public APlayerState
{
	GENERATED_BODY()

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const;

public:

	uint8 GetTeamNum(AController* Player); //Get the team the player is on
	int32 GetFrags() const;
	int32 GetDeaths() const;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Teams")
		uint8 Team = 0; // Start as a spectator, 0 = Spectator, 1 = Human, 2 = Alien


private:
	int32 numFrags = 0; // Number of frags the player has
	int32 numDeaths = 0; // Number of deaths the player has



};
