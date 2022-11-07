// Fill out your copyright notice in the Description page of Project Settings.


#include "pcgmap.h"
#include "EngineUtils.h"
#include "Net/UnrealNetwork.h"

// Sets default values
Apcgmap::Apcgmap()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;
	//setting of the tile mesh floor
	tileFloorCom = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("tileFloor"));
	tileFloorCom->SetMobility(EComponentMobility::Static);
	tileFloorCom->SetStaticMesh(floor);
	//setting of the tile mesh wall
	tileWallCom = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("tileWall"));
	tileWallCom->SetMobility(EComponentMobility::Static);
	tileWallCom->SetStaticMesh(wall);

	tileWallCom->AttachTo(RootComponent);
	tileFloorCom->AttachTo(RootComponent);
	AddInstanceComponent(tileWallCom);
	AddInstanceComponent(tileFloorCom);

	bRegenerateMap = false;
	DoorEvery = 2;
	DoorRemainder = 1;
	origin = true;
	Doors.Empty();
}

// Called when the game starts or when spawned
void Apcgmap::BeginPlay()
{
	Super::BeginPlay();
	Doors.Empty();
	RoomSizeX = 5;
	RoomSizeY = 5;
	GenerateRoom();
}

// Called every frame
void Apcgmap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRegenerateMap)
	{
		for (auto It = Doors.CreateIterator(); It; ++It)
		{
			(*It)->Destroy();
		}
		Doors.Empty();
		ClearMap();
		GenerateRoom();
		bRegenerateMap = false;
	}
}

void Apcgmap::GenerateRoom() {
	//Floor generate
	for (int X = 0; X < RoomSizeX; X++) {
		for (int Y = 0; Y < RoomSizeY; Y++) {
			FVector tileVector = FVector(TileSizeX * X, TileSizeY * Y, -40);
			FVector final = tileVector + this->GetActorLocation();
			transform.SetLocation(final);
			FRotator rotation = FRotator(0, 0, 0);
			transform.SetRotation(rotation.Quaternion());
			tileFloorCom->AddInstance(transform);
			
			if (X == int(RoomSizeX / 2) && Y == int(RoomSizeY/2)) {
				FVector item = FVector(int(RoomSizeX / 2)*TileSizeX,int(RoomSizeY/2)*TileSizeY, 0);
				FVector itemloc = item + this->GetActorLocation();
				ItemPlace(itemloc);
			}
		}
	}
	for (int Y = 0; Y < RoomSizeY; Y++) {
		//bottom wall generate
		FVector tileVector = FVector(-200, TileSizeY * Y, -40);
		FVector final = tileVector + this->GetActorLocation();
		FRotator rotation = FRotator(0,0,0);
		transform.SetLocation(final);
		transform.SetRotation(rotation.Quaternion());
		WallOrDoor(final, rotation, transform, Y);
		//top wall generate
		tileVector = FVector((RoomSizeX) * TileSizeX, Y*TileSizeY, -40);
		final = tileVector + this->GetActorLocation();
		transform.SetLocation(final);
		rotation = FRotator(0, 180, 0);
		transform.SetRotation(rotation.Quaternion());
		WallOrDoor(final, rotation, transform, Y);
	}
	for (int X = 0; X < RoomSizeX; X++) {
		//left wall generate
		FVector tileVector = FVector(X * TileSizeX, (RoomSizeY) * TileSizeY, -40);
		FVector final = tileVector + this->GetActorLocation();
		FRotator rotation = FRotator(0, -90, 0);
		transform.SetLocation(final);
		transform.SetRotation(rotation.Quaternion());
		WallOrDoor(final, rotation, transform, X);
		//right wall generate
		tileVector = FVector(TileSizeX*X , -200, -40);
		final = tileVector + this->GetActorLocation();
		transform.SetLocation(final);
		rotation = FRotator(0, 90, 0);
		transform.SetRotation(rotation.Quaternion());
		WallOrDoor(final, rotation, transform, X);
	}
}

void Apcgmap::ClearMap(){
	//delete all the mesh
	//tileWallCom->ClearInstances();
	//tileFloorCom->ClearInstances();
}

void Apcgmap::WallOrDoor(FVector loc, FRotator rot, FTransform tra, int index)
{
	//get it need to generate a wall or door
	if (index % DoorEvery == DoorRemainder && RandomSelectDoor()) {
		SpawnDoor(loc, rot);
	}
	else {
		tileWallCom->AddInstance(tra);
	}
}

bool Apcgmap::RandomSelectDoor()
{
	//Random select door
	float weight = float(doorNumber-Doors.Num())/float(doorNumber);
	bool isdoor = UKismetMathLibrary::RandomBoolWithWeightFromStream(weight, FRandomStream());
	return isdoor;
}

void Apcgmap::SpawnDoor(FVector loc, FRotator rot)
{
	FActorSpawnParameters SpawnParams;
	AActor* Door = GetWorld()->SpawnActor<AActor>(DoorToSpawn,loc, rot, SpawnParams);
	Doors.Add(Door);
}

void Apcgmap::SpawnArmor(FVector loc, FRotator rot)
{
	FActorSpawnParameters SpawnParams;
	AActor* Armor = GetWorld()->SpawnActor<AActor>(ArmorToSpawn, loc, rot, SpawnParams);
}

void Apcgmap::SpawnGun(FVector loc, FRotator rot)
{
	FActorSpawnParameters SpawnParams;
	AActor* Gun = GetWorld()->SpawnActor<AActor>(GunToSpawn, loc, rot, SpawnParams);
}

void Apcgmap::SpawnHealth(FVector loc, FRotator rot)
{
	FActorSpawnParameters SpawnParams;
	AActor* Health = GetWorld()->SpawnActor<AActor>(HealthToSpawn, loc, rot, SpawnParams);
}

void Apcgmap::SpawnGoldenCoin(FVector loc, FRotator rot)
{
	FActorSpawnParameters SpawnParams;
	AActor* GoldenCoin = GetWorld()->SpawnActor<AActor>(GoldenCoinToSpawn, loc, rot, SpawnParams);
}

TypeOfItem Apcgmap::WhichItemPlace()
{
	//random with percentage select the item
	RarityValue = FMath::RandRange(0.0f, 1.0f);

	if (RarityValue <= 0.15f)
	{
		ItemType = TypeOfItem::ARMOR;
	}
	else if (RarityValue <= 0.3f)
	{
		ItemType = TypeOfItem::GUN;
	}
	else if (RarityValue <= 0.45f)
	{
		ItemType = TypeOfItem::HEALTH;
	}
	else if(RarityValue <= 1.0)
	{
		ItemType = TypeOfItem::GOLDENCOIN;
	}
	return ItemType;
}

void Apcgmap::ItemPlace(FVector location)
{
	//generate the item
	if (WhichItemPlace() == TypeOfItem::ARMOR) {
		SpawnArmor(location, FRotator(0, 0, 0));
	}
	else if (WhichItemPlace() == TypeOfItem::GUN) {
		SpawnGun(location, FRotator(0, 0, 0));
	}
	else if (WhichItemPlace() == TypeOfItem::HEALTH) {
		SpawnHealth(location, FRotator(0, 0, 0));
	}
	else if (WhichItemPlace() == TypeOfItem::GOLDENCOIN) {
		SpawnGoldenCoin(location, FRotator(0, 0, 0));
	}
}

void Apcgmap::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(Apcgmap, RarityValue);
	DOREPLIFETIME(Apcgmap, RoomSizeX);
	DOREPLIFETIME(Apcgmap, RoomSizeY);
	DOREPLIFETIME(Apcgmap, TileSizeX);
	DOREPLIFETIME(Apcgmap, TileSizeY);
	DOREPLIFETIME(Apcgmap, doorNumber);
	DOREPLIFETIME(Apcgmap, DoorEvery);
	DOREPLIFETIME(Apcgmap, DoorRemainder);
	DOREPLIFETIME(Apcgmap, origin);
	DOREPLIFETIME(Apcgmap, Doors);
	DOREPLIFETIME(Apcgmap, transform);
	DOREPLIFETIME(Apcgmap, bRegenerateMap);
	DOREPLIFETIME(Apcgmap, ItemType);
}

