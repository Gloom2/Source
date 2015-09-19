// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "Gloom2HUD.generated.h"

UCLASS()
class AGloom2HUD : public AHUD
{
	GENERATED_BODY()

public:
	AGloom2HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

