// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "Gloom2GameMode.generated.h"


UCLASS(minimalapi)
class AGloom2GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AGloom2GameMode();

	void PostLogin(APlayerController * NewPlayer) override;

	AActor * ChoosePlayerStart(AController * Player);

	bool ShouldSpawnAtStartSpot(AController * Player) override { return false; };

};



