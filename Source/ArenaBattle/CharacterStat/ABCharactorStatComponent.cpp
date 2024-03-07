// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABCharactorStatComponent.h"
#include "GameData/ABGameSingleton.h"

// Sets default values for this component's properties
UABCharactorStatComponent::UABCharactorStatComponent()
{
	CurrentLevel = 0;
}


// Called when the game starts
void UABCharactorStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetLevelStat(CurrentLevel);
	SetHP(BaseStat.MaxHp);
	
}

void UABCharactorStatComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp(NewHP,0.0f,BaseStat.MaxHp);

	OnHpChanged.Broadcast(CurrentHP);
}


// Called every frame
void UABCharactorStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UABCharactorStatComponent::ApplyDamage(float InDamage)
{
	float ActualDamage = FMath::Clamp(InDamage, 0.0f, InDamage);

	SetHP(CurrentHP - ActualDamage);
	if (CurrentHP <= 0.0f)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}

void UABCharactorStatComponent::SetLevelStat(uint8 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UABGameSingleton::Get().GetMaxLevel());
	BaseStat = UABGameSingleton::Get().GetCharacterStat(CurrentLevel);
}

