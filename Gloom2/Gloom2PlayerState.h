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

	
public:
	UPROPERTY(Replicated)
		bool bHuman;
	
	UPROPERTY(Replicated)
		bool bAlien;

	uint8 Team = 0; // Start as a spectator, 0 = Spectator, 1 = Human, 2 = Alien
};
