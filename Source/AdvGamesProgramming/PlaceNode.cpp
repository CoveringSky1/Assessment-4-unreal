// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceNode.h"

// Sets default values
APlaceNode::APlaceNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	tileFloorCom = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("tileFloor"));
	tileFloorCom->SetMobility(EComponentMobility::Static);
	tileFloorCom->SetStaticMesh(floor);
	AddInstanceComponent(tileFloorCom);
	bRegenerateMap = false;
}

// Called when the game starts or when spawned
void APlaceNode::BeginPlay()
{
	Super::BeginPlay();
	// background floor
	for (int X = 0; X < 33; X++) {
		for (int Y = 0; Y < 33; Y++) {
			FVector tileVector = FVector(200 * X, 200 * Y, -40);
			transform.SetLocation(tileVector);
			FRotator rotation = FRotator(0, 0, 0);
			transform.SetRotation(rotation.Quaternion());
			tileFloorCom->AddInstance(transform);
		}
	}
	if (AIManager)
	{
		//AIManager->GenerateNodes();
	}
	generateMap();
}

// Called every frame
void APlaceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRegenerateMap)
	{
		generateMap();
		bRegenerateMap = false;
	}

}

void APlaceNode::generateMap()
{
	// generate multiple room in 5 * 5
	for (int X = 0; X < 5; X++) {
		for (int Y = 0; Y < 5; Y++) {
			FActorSpawnParameters SpawnParams;
			FVector location = FVector(X * 1400, Y * 1400, 0);
			FRotator rotation = FRotator(0, 0, 0);
			AActor* Room = GetWorld()->SpawnActor<AActor>(RoomToSpawn, location, rotation, SpawnParams);
		}
	}

	for (int i = 0; i < numberOfAI; i++) {
		FActorSpawnParameters SpawnParams;
		FVector location = FVector(200, i*200, 10);
		FRotator rotation = FRotator(0, 0, 0);
		AActor* AI = GetWorld()->SpawnActor<AActor>(AIToSpawn, location, rotation, SpawnParams);
	}
}

