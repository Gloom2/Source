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

	FString GetUIMessage();

	UFUNCTION()
		void SetMessage(FString Message);

	UFUNCTION()
		void SetTeamMessage(int32 TeamNum);

	UFUNCTION()
		void SetFragsMessage(int32 Frags);

	/*UFUNCTION()
		AGloom2HUD* SetGloomHUD(AGloom2PlayerController* Player);*/

	int32 GetFrags(AGloom2PlayerController *Player);
	//FString GetTeam(AGloom2PlayerController *Player);


private:
	/** Crosshair asset pointer */
	class UTexture2D *CrosshairTex;

	class UFont *DisplayFont;
	class UFont *HUDFont;

	//void Tick(float DeltaTime) override;

	FTimerHandle FTimerMessageRefresh;

	FString DisplayText;

	FString UIMessage;
	int32 playerFrags;
	int32 teamNum;
	FString teamName;
	AGloom2PlayerController *Gloom2Player;
	//AGloom2PlayerState* Gloom2PS;
	//AGloom2HUD* Gloom2HUD;

	void DisplayMessage(FString DisplayText, UFont *DisplayFont, FVector2D DisplayMessagePosition);
	void DisplayGloomHUD(FString Team, int32 Frags, UFont *HUDFont, FVector2D TeamDisplayPosition, FVector2D FragDisplayPosition);
	void DisplayPlayerInfo(UFont *HUDFont, FVector2D HealthDisplayPosition, FVector2D AmmoDisplayPosition);
	/*AGloom2PlayerController* GetPlayer();*/

};

