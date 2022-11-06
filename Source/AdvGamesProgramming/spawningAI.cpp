// Fill out your copyright notice in the Description page of Project Settings.


#include "spawningAI.h"

// Sets default values
AspawningAI::AspawningAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AspawningAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AspawningAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AspawningAI::generateAI()
{
	for (int i = 0; i < numberOfAI; i++) {
		FActorSpawnParameters SpawnParams;
		FVector location = FVector(0, 0, 0);
		FRotator rotation = FRotator(0, 0, 0);
		AActor* AI = GetWorld()->SpawnActor<AActor>(AIToSpawn, location, rotation, SpawnParams);
	}
}

