// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldenCoinPickUp.h"
#include "Net/UnrealNetwork.h"

void AGoldenCoinPickUp::OnGenerate() {

	APickup::OnGenerate();

}

void AGoldenCoinPickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}
