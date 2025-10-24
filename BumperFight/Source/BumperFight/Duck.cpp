// Fill out your copyright notice in the Description page of Project Settings.


#include "Duck.h"

// Sets default values
ADuck::ADuck()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	SetRootComponent(Mesh);
	
	CurrentAttack=BaseAttack;
	CurrentHp=BaseHp;
}

// Called when the game starts or when spawned
void ADuck::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADuck::LaunchDuck(FVector Direction, float Force)
{
	Mesh->AddImpulse(Force*Direction);
}

void ADuck::DealDamage(ADuck* OtherDuck)
{
	if(!OtherDuck)
		return;

	//TODO: Add damage multipliers
	OtherDuck->GetDamage(this, CurrentAttack);
}

void ADuck::GetDamage(ADuck* OtherDuck, int Amount)
{
	CurrentHp=FMath::Clamp(CurrentHp-Amount, 0, BaseHp);

	if(CurrentHp==0)
		Die();
}

void ADuck::Die()
{
	Destroy();
}



