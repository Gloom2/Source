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

	FTimerHandle TimerHandle_Respawn;

public:

	void OnKilled();

	void Respawn();

	
	
};
