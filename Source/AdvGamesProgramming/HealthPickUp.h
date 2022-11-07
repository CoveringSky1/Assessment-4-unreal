// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AHealthPickUp : public APickup
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated,BlueprintReadOnly, EditAnywhere)
		float FullHealth;

	UFUNCTION(BlueprintImplementableEvent)
		void OnPickup(AActor* ActorThatPickedUp) override;
	UFUNCTION(BlueprintCallable)
		void OnGenerate() override;

		void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
