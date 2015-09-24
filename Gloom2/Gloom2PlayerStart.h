// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerStart.h"
#include "Gloom2PlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class GLOOM2_API AGloom2PlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Spawns")
		bool bHuman;

	uint8 Team = 0;

	
	
};
