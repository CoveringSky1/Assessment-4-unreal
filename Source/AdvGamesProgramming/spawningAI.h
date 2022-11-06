// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "spawningAI.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API AspawningAI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AspawningAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTransform transform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> AIToSpawn;

	UPROPERTY(EditAnywhere)
	int numberOfAI;

	void generateAI();

};
