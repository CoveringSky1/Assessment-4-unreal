// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"
#include "Engine/Blueprint.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIManager.h"
#include "Math/RandomStream.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "PlaceNode.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API APlaceNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UInstancedStaticMeshComponent* tileFloorCom;
	UPROPERTY(EditAnywhere)
		UStaticMesh* floor;


	FTransform transform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> RoomToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bRegenerateMap;

	UPROPERTY(EditAnywhere)
		AAIManager* AIManager;

	void generateMap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> AIToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int numberOfAI;


};
