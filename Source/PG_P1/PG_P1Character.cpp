// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PG_P1Character.h"

// Sets default values
APG_P1Character::APG_P1Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APG_P1Character::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(Controller);
	if (!playerController) {
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	if (!subsystem) {
		return;
	}

	subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void APG_P1Character::Move(const FInputActionValue& value)
{
	if (!Controller) {
		return;
	}

	FVector2D moveVector = value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), moveVector.Y);
	AddMovementInput(GetActorRightVector(), moveVector.X);
}

void APG_P1Character::Look(const FInputActionValue &value)
{
	if (!Controller) {
		return;
	}

	FVector2D vector = value.Get<FVector2D>();
	AddControllerYawInput(vector.X);
	AddControllerPitchInput(vector.Y * -1.0);
}

// Called to bind functionality to input
void APG_P1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* inputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!inputComponent) {
		return;
	}

	inputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APG_P1Character::Move);
	inputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APG_P1Character::Look);
}
