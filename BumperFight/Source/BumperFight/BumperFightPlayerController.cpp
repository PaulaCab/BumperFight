// Copyright Epic Games, Inc. All Rights Reserved.

#include "BumperFightPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "BumperFightCharacter.h"
#include "Duck.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ABumperFightPlayerController::ABumperFightPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ABumperFightPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ABumperFightPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &ABumperFightPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, &ABumperFightPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Canceled, this, &ABumperFightPlayerController::OnSetDestinationReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


// Triggered every frame when the input is held down
void ABumperFightPlayerController::OnSetDestinationTriggered()
{
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		SelectedDuck = Cast<ADuck>(Hit.GetActor());
		if(!SelectedDuck)
			return;

		float x, y;
		GetMousePosition(x,y);
		CachedMousePosition=FVector(x,y,0);
	}
	//TODO: Give some type of feedback i guess
}

void ABumperFightPlayerController::OnSetDestinationReleased()
{
	if(!SelectedDuck)
		return;

	float x, y;
	GetMousePosition(x,y);
	FVector MousePosition = FVector(x,y,0);

	auto dist = FVector::Dist(CachedMousePosition, MousePosition);
	if(dist<5)
		return;
	auto dir = (CachedMousePosition-MousePosition).GetSafeNormal();
	SelectedDuck->LaunchDuck(dir, dist*LaunchForceFactor);
}

