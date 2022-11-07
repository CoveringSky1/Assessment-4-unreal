// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor.h"
#include "Engine/GameEngine.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerHUD.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UArmor::UArmor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	MaxArmor = 100;
}


// Called when the game starts
void UArmor::BeginPlay()
{
	Super::BeginPlay();
	CurrentArmor = 0;
	// ...
	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		if (GetOwner()->GetLocalRole() == ROLE_Authority && OwnerPawn->IsLocallyControlled())
		{
			UpdateArmorBar();
		}
	}
}


// Called every frame
void UArmor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		if (GetOwner()->GetLocalRole() == ROLE_Authority && OwnerPawn->IsLocallyControlled())
		{
			UpdateArmorBar();
		}
	}
}

void UArmor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArmor, CurrentArmor);
}

float UArmor::HealthPercentageRemaining()
{
	return CurrentArmor / MaxArmor * 100.0f;
}

void UArmor::OnTakeDamage(float Damage)
{
	CurrentArmor -= Damage;
}

void UArmor::UpdateArmorBar()
{
	if (GetOwner()->GetLocalRole() == ROLE_AutonomousProxy || (GetOwner()->GetLocalRole() == ROLE_Authority && Cast<APawn>(GetOwner())->IsLocallyControlled()))
	{
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		if (IsValid(PlayerHUD))
		{
			PlayerHUD->SetPlayerArmorBarPercent(CurrentArmor / MaxArmor);
		}
	}
}

