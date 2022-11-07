// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "ArmorPickUp.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EArmorPickupRarity : uint8
{
	LEGENDARY,
	MASTER,
	RARE,
	COMMON
};

UCLASS()
class ADVGAMESPROGRAMMING_API AArmorPickUp : public APickup
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
		EArmorPickupRarity Rarity;
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
		float Buff;

	UFUNCTION(BlueprintImplementableEvent)
		void OnPickup(AActor* ActorThatPickedUp) override;
	UFUNCTION(BlueprintCallable)
		void OnGenerate() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
