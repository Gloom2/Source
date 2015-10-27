// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "Gloom2PlayerController.h"
#include "Gloom2PlayerState.h"
#include "Gloom2HUD.generated.h"


UCLASS()
class AGloom2HUD : public AHUD
{
	GENERATED_BODY()

public:
	AGloom2HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	UFUNCTION()
		FString GetUIMessage();

	UFUNCTION()
		void SetMessage(FString Message);

	UFUNCTION()
		void SetTeamMessage(int32 TeamNum);

	UFUNCTION()
		void SetFragsMessage(int32 Frags);

	UFUNCTION()
		int32 GetFragsMessage();

	UFUNCTION()
		FString GetTeamMessage();


private:
	/** Crosshair asset pointer */
	UPROPERTY()
	class UTexture2D *CrosshairTex;

	// HUD Fonts
	class UFont *DisplayFont;
	class UFont *HUDFont;

	FTimerHandle FTimerMessageRefresh;

	// The message to be displayed to the HUD
	FString DisplayText;

	UPROPERTY()
		FString UIMessage;

	UPROPERTY()
		int32 playerFrags;

	UPROPERTY()
		int32 teamNum;

	UPROPERTY()
		FString teamName;

	UPROPERTY()
		AGloom2PlayerController *Gloom2Player;

	UFUNCTION()
		void DisplayMessage(FString DisplayText, UFont *DisplayFont, FVector2D DisplayMessagePosition);
	UFUNCTION()
		void DisplayGloomHUD(FString Team, int32 Frags, UFont *HUDFont, FVector2D TeamDisplayPosition, FVector2D FragDisplayPosition);
	UFUNCTION()
		void DisplayPlayerInfo(UFont *HUDFont, FVector2D HealthDisplayPosition, FVector2D AmmoDisplayPosition);

};

