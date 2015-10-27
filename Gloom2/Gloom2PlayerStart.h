// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerStart.h"
#include "Gloom2PlayerStart.generated.h"

/** This is the spectator, or team 0, spawn start, Alien and Human starts inherit directly from this class
 * 
 */
UCLASS(Category = "Spawns")
class GLOOM2_API AGloom2PlayerStart : public APlayerStart
{
	GENERATED_BODY()

};
