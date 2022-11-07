#include "PlayerHUD.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDObject(TEXT("/Game/Widgets/PlayerHUDWidget"));
	

	PlayerHUDClass = PlayerHUDObject.Class;
	

	if (PlayerHUDClass)
	{
		CurrentPlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (CurrentPlayerHUDWidget)
		{
			CurrentPlayerHUDWidget->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unable to find CurrentPlayerHUDWidget"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find the PlayerHUDClass"))
	}

	if (CurrentPlayerHUDWidget)
	{
		HealthProgressBar = Cast<UProgressBar>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("ProgHealthBar")));
		ArmorProgressBar = Cast<UProgressBar>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("ProgArmorBar")));
		RoundsRemainingText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("RoundsRemaining")));
		RoundsInMagazineText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("RoundsInMagazine")));
		CurrentCollectionText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("CurrentCollection")));
		TotalCollectionText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("TotalCollection")));
		BossHealthText = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("BossHealth")));
	}
	
}

void APlayerHUD::SetPlayerHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find the progress bar to update the health"))
	}
}

void APlayerHUD::SetPlayerArmorBarPercent(float Percent)
{
	if (ArmorProgressBar)
	{
		ArmorProgressBar->SetPercent(Percent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find the progress bar to update the Armor"))
	}
}

void APlayerHUD::HideHUD()
{
	if (CurrentPlayerHUDWidget)
	{
		CurrentPlayerHUDWidget->RemoveFromViewport();
	}
}

void APlayerHUD::ShowHUD()
{
	if (CurrentPlayerHUDWidget)
	{
		CurrentPlayerHUDWidget->AddToViewport();
	}
}

void APlayerHUD::SetAmmoText(int32 RoundsRemaining, int32 RoundsInMagazine)
{
	if (RoundsRemainingText && RoundsInMagazineText)
	{
		RoundsRemainingText->SetText(FText::FromString(FString::Printf(TEXT("%i"), RoundsRemaining)));
		RoundsInMagazineText->SetText(FText::FromString(FString::Printf(TEXT("%i"), RoundsInMagazine)));
	}
}

void APlayerHUD::SetGoldCoinText(int32 currentCollection, int32 totalCollection, int32 BossHealth)
{
	if (CurrentCollectionText && TotalCollectionText && BossHealthText)
	{
		CurrentCollectionText->SetText(FText::FromString(FString::Printf(TEXT("%i"), currentCollection)));
		TotalCollectionText->SetText(FText::FromString(FString::Printf(TEXT("%i"), totalCollection)));
		BossHealthText->SetText(FText::FromString(FString::Printf(TEXT("%i"), BossHealth)));
	}
}
