// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "BumperFightPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class ADuck;
class APredictionLine;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ABumperFightPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABumperFightPlayerController();

	UPROPERTY(EditAnywhere) float LaunchForceFactor = 100.f;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ClickAction;


protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationOngoing();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	TArray<FVector> PredictImpulseTrayectory(ADuck* Duck, const FVector& Impulse);

	UPROPERTY(EditDefaultsOnly)	TSubclassOf<APredictionLine> PredictionLineClass = nullptr;
	UPROPERTY()	APredictionLine* PredictionLine = nullptr;

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

	class ADuck* SelectedDuck = nullptr;
	FVector CachedMousePosition;
};


