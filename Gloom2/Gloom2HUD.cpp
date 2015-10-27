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

	// Set the HUD font
	ConstructorHelpers::FObjectFinder<UFont> HUDFontObject(TEXT("/Game/Fonts/GHUD"));
	HUDFont = HUDFontObject.Object;
	Gloom2Player = Cast<AGloom2PlayerController>(Gloom2Player);
	
}


void AGloom2HUD::DrawHUD()
{
	Super::DrawHUD();


	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f)),
										   (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)) );

	// 2D Locations of the HUD messages
	const FVector2D DisplayMessagePosition((Center.X * 0.5f), (Center.Y * 0.5f)); // Message position (Above Crosshair in center)
	const FVector2D TeamDisplayPosition((Center.X * 0.025f), (Center.Y * 0.025f)); // Team label on top left of screen
	const FVector2D FragDisplayPosition((Canvas->ClipX * 0.95f), (Canvas->ClipY * 0.025f)); // Frag amount displayed on top right of screen
	const FVector2D HealthDisplayPosition((Canvas->ClipX * 0.025f), (Canvas->ClipY * 0.95f)); // Display the amount of health the player has on bottom left of screen
	const FVector2D AmmoDisplayPosition((Canvas->ClipX * 0.95f), (Canvas->ClipY * 0.95f)); // Display the ammo/clip count for the player as well as the type on bottom right of screen

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );

	playerFrags = GetFragsMessage(); // Get the frags from Gloom2PlayerState
	teamName = GetTeamMessage(); // Get the team name from Gloom2PlayerState

	// Display a message to the screen above the crosshair
	DisplayMessage(DisplayText, DisplayFont, DisplayMessagePosition);

	// Display the pertinent Gloom HUD information
	DisplayGloomHUD(teamName, playerFrags, HUDFont, TeamDisplayPosition, FragDisplayPosition);
	DisplayPlayerInfo(HUDFont, HealthDisplayPosition, AmmoDisplayPosition);
	

}

// Set the Client message to the DisplayText FString for DisplayMessage()
void AGloom2HUD::SetMessage(FString UIMessage)
{

	DisplayText = UIMessage;
}

// Get the UIMessage for the DisplayMessage()
FString AGloom2HUD::GetUIMessage()
{
	return UIMessage;
}

// Set the teamName for the HUD to display what team player is on
void AGloom2HUD::SetTeamMessage(int32 TeamNumber)
{
	teamNum = TeamNumber;
	if (teamNum == 0) { teamName = "Observer"; }
	else if (teamNum == 1) { teamName = "Human"; }
	else if (teamNum == 2) { teamName = "Alien"; }

}

// Get the teamname for the HUD
FString AGloom2HUD::GetTeamMessage()
{
	return teamName;
}

// Set the amount of frags for the player HUD (read from playerstate)
void AGloom2HUD::SetFragsMessage(int32 Frags)
{
	playerFrags = Frags;
}

// Get the player frags for the HUD
int32 AGloom2HUD::GetFragsMessage()
{
	return playerFrags;
}

// Display a message to the player (just above the crosshair in center of screen)
void AGloom2HUD::DisplayMessage(FString DisplayText, UFont *DisplayFont, FVector2D DisplayMessagePosition)
{
	Canvas->DrawText(DisplayFont, (DisplayText), DisplayMessagePosition.X, DisplayMessagePosition.Y, 2.0f, 2.0f, FFontRenderInfo());
}

// Display the topmost information for the Gloom HUD for the player
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

// Display the information tags for the player on the bottom of the screen
void AGloom2HUD::DisplayPlayerInfo(UFont *HUDFont, FVector2D HealthDisplayPosition, FVector2D AmmoDisplayPosition)
{
	// Display Information Types
	Canvas->DrawText(HUDFont, "Health", HealthDisplayPosition.X, HealthDisplayPosition.Y, 0.4f, 0.4f, FFontRenderInfo());
	Canvas->DrawText(HUDFont, "Ammo", AmmoDisplayPosition.X, AmmoDisplayPosition.Y, 0.4f, 0.4f, FFontRenderInfo());

}

