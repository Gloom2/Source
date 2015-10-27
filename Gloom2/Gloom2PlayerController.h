// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Gloom2PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GLOOM2_API AGloom2PlayerController : public APlayerController
{
	GENERATED_BODY()

	FTimerHandle TimerHandle_Respawn; // Respawn timer

	
public:

	void OnKilled(); // When player dies

	void Respawn(); // How player respawns (for now it auto-respawns)

	UFUNCTION(Client, Reliable) // Set the message for the clients message display
		virtual void ClientSetMessage(AGloom2PlayerController *Gloom2Player, const FString &_message); 
	
};
