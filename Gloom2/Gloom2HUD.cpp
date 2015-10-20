// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Gloom2.h"
#include "Gloom2HUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

AGloom2HUD::AGloom2HUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	// Set the message font
	ConstructorHelpers::FObjectFinder<UFont> DisplayObject(TEXT("/Game/Fonts/DisplayMessage"));
	DisplayFont = DisplayObject.Object;
	DisplayText = " ";
	UIMessage = " ";

	// Set the HUD font
	ConstructorHelpers::FObjectFinder<UFont> HUDFontObject(TEXT("/Game/Fonts/GHUD"));
	HUDFont = HUDFontObject.Object;
	Gloom2Player = Cast<AGloom2PlayerController>(Gloom2Player);
	//Gloom2PS = Cast<AGloom2PlayerState>(Gloom2Player->PlayerState);
	//AGloom2PlayerState *PS = Cast<AGloom2PlayerState>(Gloom2Player->PlayerState);
	teamName = "Team Name";
	playerFrags = 0;
	teamNum = 0;
}


void AGloom2HUD::DrawHUD()
{
	Super::DrawHUD();


	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f)),
										   (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)) );

	const FVector2D DisplayMessagePosition((Center.X * 0.5f), (Center.Y * 0.5f));

	const FVector2D TeamDisplayPosition((Center.X * 0.025f), (Center.Y * 0.025f));
	const FVector2D FragDisplayPosition((Canvas->ClipX * 0.95f), (Canvas->ClipY * 0.025f));
	const FVector2D HealthDisplayPosition((Canvas->ClipX * 0.025f), (Canvas->ClipY * 0.95f));
	const FVector2D AmmoDisplayPosition((Canvas->ClipX * 0.95f), (Canvas->ClipY * 0.95f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );


	// Display a message to the screen above the crosshair
	//Gloom2Player = GetPlayer();
	//teamName = GetTeam(Gloom2Player);
	playerFrags = GetFrags(Gloom2Player);
	DisplayMessage(DisplayText, DisplayFont, DisplayMessagePosition);
	DisplayGloomHUD(teamName, playerFrags, HUDFont, TeamDisplayPosition, FragDisplayPosition);
	DisplayPlayerInfo(HUDFont, HealthDisplayPosition, AmmoDisplayPosition);
	

}

//AGloom2PlayerController* AGloom2HUD::GetPlayer()
//{
//	AGloom2PlayerController* Gloom2Player = Cast<AGloom2PlayerController>(Gloom2Player);
//	return Gloom2Player;
//
//}

void AGloom2HUD::SetMessage(FString UIMessage)
{

	DisplayText = UIMessage;
}

FString AGloom2HUD::GetUIMessage()
{
	return UIMessage;
}

void AGloom2HUD::SetTeamMessage(int32 TeamNumber)
{
	teamNum = TeamNumber;
	if (teamNum == 0) { teamName = "Spectators"; }
	else if (teamNum == 1) { teamName = "Human"; }
	else if (teamNum == 2) { teamName = "Alien"; }

}

void AGloom2HUD::SetFragsMessage(int32 Frags)
{
	playerFrags = Frags;
}
//FString AGloom2HUD::GetTeam(AGloom2PlayerController *Player)
//{
//	if (Player)
//	{
//		AGloom2PlayerState *Gloom2PS = Cast<AGloom2PlayerState>(Player->PlayerState);
//		if (Gloom2PS)
//		{
//
//			teamNum = Gloom2PS->GetTeamNum();
//			if (teamNum == 0) { teamName = "Spectators"; }
//			else if (teamNum == 1) { teamName = "Human"; }
//			else if (teamNum == 2) { teamName = "Alien"; }
//			return teamName;
//		}
//		return teamName;
//	}
//	return teamName;
//
//}

int32 AGloom2HUD::GetFrags(AGloom2PlayerController *Player)
{
	if (Player)
	{
		AGloom2PlayerState *Gloom2PS = Cast<AGloom2PlayerState>(Player->PlayerState);
		if (Gloom2PS)
		{
			playerFrags = Gloom2PS->GetFrags();
			return playerFrags;
		}
		return 0;
	}
	return 0;
}

void AGloom2HUD::DisplayMessage(FString DisplayText, UFont *DisplayFont, FVector2D DisplayMessagePosition)
{
	Canvas->DrawText(DisplayFont, (DisplayText), DisplayMessagePosition.X, DisplayMessagePosition.Y, 2.0f, 2.0f, FFontRenderInfo());
}

void AGloom2HUD::DisplayGloomHUD(FString Team, int32 Frags, UFont *HUDFont, FVector2D TeamDisplayPosition, FVector2D FragDisplayPosition)
{

	// Display Team Name
	Canvas->DrawText(HUDFont, (Team), TeamDisplayPosition.X, TeamDisplayPosition.Y, 0.5f, 0.5f, FFontRenderInfo());
	// Display Amount of Frags
	FString S_Frags = FString::FromInt(Frags);
	Canvas->DrawText(HUDFont, (S_Frags), FragDisplayPosition.X, FragDisplayPosition.Y, 1.f, 1.f, FFontRenderInfo());

	// Display Information Types
	Canvas->DrawText(HUDFont, "Frags", FragDisplayPosition.X, FragDisplayPosition.Y * 0.25f, 0.4f, 0.4f, FFontRenderInfo());

}

void AGloom2HUD::DisplayPlayerInfo(UFont *HUDFont, FVector2D HealthDisplayPosition, FVector2D AmmoDisplayPosition)
{
	// Display Information Types
	Canvas->DrawText(HUDFont, "Health", HealthDisplayPosition.X, HealthDisplayPosition.Y, 0.4f, 0.4f, FFontRenderInfo());
	Canvas->DrawText(HUDFont, "Ammo", AmmoDisplayPosition.X, AmmoDisplayPosition.Y, 0.4f, 0.4f, FFontRenderInfo());

}

//AGloom2HUD* SetGloomHUD(AGloom2PlayerController* Player)
//{
//	AGloom2HUD* Gloom2HUD = Cast<AGloom2HUD>(Gloom2HUD);
//	return Gloom2HUD;
//}
