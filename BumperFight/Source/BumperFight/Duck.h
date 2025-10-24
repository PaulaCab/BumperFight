// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Duck.generated.h"

UCLASS()
class BUMPERFIGHT_API ADuck : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh = nullptr;

	
	// Sets default values for this actor's properties
	ADuck();
	
	UPROPERTY(EditDefaultsOnly)	int BaseAttack = 5;
	int CurrentAttack;

	UPROPERTY(EditDefaultsOnly) int BaseHp = 50;
	int CurrentHp;


	void LaunchDuck(FVector Direction, float Force);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DealDamage(ADuck* OtherDuck);
	virtual void GetDamage(ADuck* OtherDuck, int Amount);
	virtual void Die();

};
