// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorPickUp.h"
#include "Net/UnrealNetwork.h"

void AArmorPickUp::OnGenerate() {

	APickup::OnGenerate();

	float percentage = FMath::RandRange(0.0f, 1.0f);

	if (percentage <= 0.5) {
		Rarity = EArmorPickupRarity::COMMON;
	}
	else if (percentage >= 0.5 && percentage <= 0.8) {
		Rarity = EArmorPickupRarity::RARE;
	}
	else if (percentage >= 0.8 && percentage <= 0.95) {
		Rarity = EArmorPickupRarity::MASTER;
	}
	else if (percentage >= 0.95) {
		Rarity = EArmorPickupRarity::LEGENDARY;
	}

	if (Rarity == EArmorPickupRarity::COMMON) {
		Buff = 25.0f;
	}
	else if (Rarity == EArmorPickupRarity::RARE) {
		Buff = 50.0f;
	}
	else if (Rarity == EArmorPickupRarity::MASTER) {
		Buff = 75.0f;
	}
	else if (Rarity == EArmorPickupRarity::LEGENDARY) {
		Buff = 100.0f;
	}
}

void AArmorPickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AArmorPickUp, Rarity);
	DOREPLIFETIME(AArmorPickUp, Buff);
}
