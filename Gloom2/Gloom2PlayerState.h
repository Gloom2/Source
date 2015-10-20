// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "Gloom2PlayerController.h"
#include "Gloom2PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GLOOM2_API AGloom2PlayerState : public APlayerState
{
	GENERATED_BODY()

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const;

	virtual void Reset() override;

public:
	AGloom2PlayerState();

	void SetTeamNum(); // Set the team the player is on
	int32 GetTeamNum(); //Get the team the player is on
	
	void SetFrags(); // Set the number of frags the player has (decrement or increment)
	int32 GetFrags(); // Get the number of frags the player has
	
	void SetDeaths(); // Set the number of deaths the player has accrued (increment)
	int32 GetDeaths(); // Get the number of deaths the player has
	
	void SetKills(); // Set the number of kills the player has accrued (increment)
	int32 GetKills(); // Get the number of kills the player has
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Teams")
		int32 Team;// Start as a spectator, 0 = Spectator, 1 = Human, 2 = Alien

	UFUNCTION(Client, Reliable)
		void SetTeamMessage(AGloom2PlayerController *Gloom2Player, const int32 &_team);

	UFUNCTION(Client, Reliable)
		void SetFragsMessage(AGloom2PlayerController *Gloom2Player, const int32 &_frags);


private:
	int32 numFrags; // Number of frags the player has
	int32 numDeaths; // Number of deaths the player has
	int32 numKills; // Number of kills the player has (not necessarily identical to frags)
	int32 numTeamS, numTeamH, numTeamA; // Number of players (going to be linked to gamemode)
	AGloom2PlayerController* Gloom2Player;
	

protected:
	const int32 TeamMax = 3; //Max team num (1 based indexing, make sure to subtract 1 from it!)

	//void UpdateTeamCount();


};
