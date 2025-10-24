// Fill out your copyright notice in the Description page of Project Settings.


#include "PredictionLine.h"

#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
APredictionLine::APredictionLine()
{
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;
}

void APredictionLine::SetPoints(TArray<FVector> Points)
{
	if (Points.Num() < 2) return;

	UWorld* World = GetWorld();
	if (!World) return;
	
	for (int32 i = 0; i < Points.Num() - 1; ++i)
	{
		DrawDebugLine(World, Points[i], Points[i + 1], FColor::Blue, false, 0.1, 0, 5);
	}
}

// Called when the game starts or when spawned
void APredictionLine::BeginPlay()
{
	Super::BeginPlay();
	
}



