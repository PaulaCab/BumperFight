// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PredictionLine.generated.h"
class USplineMeshComponent;

UCLASS()
class BUMPERFIGHT_API APredictionLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APredictionLine();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USplineComponent* Spline = nullptr;


	UPROPERTY(EditDefaultsOnly) class UStaticMesh* LineMesh = nullptr;
	UPROPERTY()	TArray<USplineMeshComponent*> SplineMeshes;
	
	void SetPoints(TArray<FVector> Points);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
