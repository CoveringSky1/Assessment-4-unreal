// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/TransformNonVectorized.h"
#include "Engine/Blueprint.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/RandomStream.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "pcgmap.generated.h"


UENUM(BlueprintType)
enum class TypeOfItem : uint8
{
	ARMOR,
	GUN,
	HEALTH,
	GOLDENCOIN
};


UCLASS()
class ADVGAMESPROGRAMMING_API Apcgmap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Apcgmap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	FVector tile;
	UPROPERTY(Replicated, EditAnywhere,BlueprintReadWrite)
		int RoomSizeX;
	UPROPERTY(Replicated, EditAnywhere,BlueprintReadWrite)
		int RoomSizeY;
	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
		float TileSizeX;
	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
		float TileSizeY;
	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
		int doorNumber;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<AActor> DoorToSpawn;
	UPROPERTY(Replicated, BlueprintReadOnly,EditAnywhere)
	    float RarityValue;
	
	USceneComponent* SceneComponent;

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
	TArray<AActor*> Doors;

	UPROPERTY(Replicated, EditAnywhere)
		int DoorEvery;
	UPROPERTY(Replicated, EditAnywhere)
		int DoorRemainder;

	UPROPERTY(Replicated, EditAnywhere)
		bool origin;

	UFUNCTION(BlueprintCallable)
	void GenerateRoom();
	
	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
	FTransform transform;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* tileFloorCom;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* tileWallCom;

	UPROPERTY(EditAnywhere)
	UStaticMesh* floor;

	UPROPERTY(EditAnywhere)
	UStaticMesh* wall;

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
		bool bRegenerateMap;

	void ClearMap();

	void WallOrDoor(FVector loc, FRotator rot, FTransform tra, int index);

	bool RandomSelectDoor();

	UFUNCTION()
	void SpawnDoor(FVector loc, FRotator rot);

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere)
		TypeOfItem ItemType;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ArmorToSpawn;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> GunToSpawn;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> HealthToSpawn;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> GoldenCoinToSpawn;

	UFUNCTION()
		void SpawnArmor(FVector loc, FRotator rot);

	UFUNCTION()
		void SpawnGun(FVector loc, FRotator rot);

	UFUNCTION()
		void SpawnHealth(FVector loc, FRotator rot);

	UFUNCTION()
		void SpawnGoldenCoin(FVector loc, FRotator rot);
	
	TypeOfItem WhichItemPlace();

	void ItemPlace(FVector location);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
