// Fill out your copyright notice in the Description page of Project Settings.

#include "FortniteCloneHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Engine.h"

AFortniteCloneHUD::AFortniteCloneHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairObj(TEXT("/Game/UI/Textures/T_Crosshair"));
	CrosshairTexture = CrosshairObj.Object;
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarObj(TEXT("/Game/UI/Widgets/UI_Health"));
	HealthWidgetClass = HealthBarObj.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> MaterialBarObj(TEXT("/Game/UI/Widgets/UI_Materials"));
	MaterialsWidgetClass = MaterialBarObj.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemBarObj(TEXT("/Game/UI/Widgets/UI_Items"));
	ItemsWidgetClass = ItemBarObj.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> KillBarObj(TEXT("/Game/UI/Widgets/UI_KillCount"));
	KillsWidgetClass = KillBarObj.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> HitMarkerObj(TEXT("/Game/UI/Widgets/UI_HitMarker"));
	HitMarkerWidgetClass = HitMarkerObj.Class;
}

void AFortniteCloneHUD::DrawHUD()
{
	Super::DrawHUD();

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X - CrosshairTexture->GetSizeX()/2),
		(Center.Y - CrosshairTexture->GetSizeY() / 2));

	// draw the crosshair
	FCanvasTileItem CrosshairTileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
	CrosshairTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(CrosshairTileItem);
}

void AFortniteCloneHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HealthWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HealthWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	if (MaterialsWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MaterialsWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	if (ItemsWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), ItemsWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	if (KillsWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), KillsWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AFortniteCloneHUD::DrawHitMarker() {
	if (HitMarkerWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HitMarkerWidgetClass);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "hitmarkerclass is not null");
		if (CurrentWidget)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "current widget is not null");
			CurrentWidget->AddToViewport();
			// TODO for later: Implement your own UUserWidget class to retrieve animation from a blueprint and play the animation here
		}
	}
}
