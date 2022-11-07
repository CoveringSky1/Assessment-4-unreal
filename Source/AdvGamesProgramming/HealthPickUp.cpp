// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "Net/UnrealNetwork.h"

void AHealthPickUp::OnGenerate() {

	APickup::OnGenerate();

}

void AHealthPickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHealthPickUp, FullHealth);
}

