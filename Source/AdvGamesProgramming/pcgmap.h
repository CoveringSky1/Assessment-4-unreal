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
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector tile;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		int RoomSizeX;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		int RoomSizeY;
	UPROPERTY(EditAnywhere)
		float TileSizeX;
	UPROPERTY(EditAnywhere)
		float TileSizeY;
	UPROPERTY(EditAnywhere)
		int doorNumber;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> DoorToSpawn;
	
	USceneComponent* SceneComponent;

	TArray<AActor*> Doors;

	UPROPERTY(EditAnywhere)
		int DoorEvery;
	UPROPERTY(EditAnywhere)
		int DoorRemainder;

	UPROPERTY(EditAnywhere)
		bool origin;

	void GenerateRoom();

	FTransform transform;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* tileFloorCom;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* tileWallCom;

	UPROPERTY(EditAnywhere)
	UStaticMesh* floor;

	UPROPERTY(EditAnywhere)
	UStaticMesh* wall;

	UPROPERTY(EditAnywhere)
		bool bRegenerateMap;

	void ClearMap();

	void WallOrDoor(FVector loc, FRotator rot, FTransform tra, int index);

	bool RandomSelectDoor();

	UFUNCTION()
	void SpawnDoor(FVector loc, FRotator rot);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
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
};
