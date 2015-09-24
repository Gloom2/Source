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

	// Set the font
	ConstructorHelpers::FObjectFinder<UFont> FontObject(TEXT("Font'/Game/StarterContent/Fonts/DisplayMessage'"));
	DisplayFont = FontObject.Object;
	DisplayText = " ";
	UIMessage = " ";

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

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );

	// Display a message to the screen above the crosshair
	DisplayMessage(DisplayText, DisplayFont, DisplayMessagePosition);

	// Display Frags

	// Display Health and Armor

	// Display Ammo
}

void AGloom2HUD::SetMessage(FString UIMessage)
{

	DisplayText = UIMessage;
}

FString AGloom2HUD::GetUIMessage()
{
	return UIMessage;
}

void AGloom2HUD::DisplayMessage(FString DisplayText, UFont* DisplayFont, FVector2D DisplayMessagePosition)
{
	Canvas->DrawText(DisplayFont, (DisplayText), DisplayMessagePosition.X, DisplayMessagePosition.Y, 2.0f, 2.0f, FFontRenderInfo());

}
