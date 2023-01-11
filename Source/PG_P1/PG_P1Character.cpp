// Fill out your copyright notice in the Description page of Project Settings.


#include "PG_P1Character.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APG_P1Character::APG_P1Character(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	this->PrimaryActorTick.bCanEverTick = true;

	this->state = EPG_CharacterStates::Idle;

	this->ActorInteractable = nullptr;

	FString componentName = TEXT("Box");
	UBoxComponent* boxComponent = this->CreateDefaultSubobject<UBoxComponent>(*componentName);
	boxComponent->InitBoxExtent(FVector(5.0, 12.0, 23.0));
	boxComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	boxComponent->CanCharacterStepUpOn = ECB_No;
	boxComponent->SetShouldUpdatePhysicsVolume(true);
	boxComponent->SetCanEverAffectNavigation(false);
	boxComponent->bDynamicObstacle = true;

	boxComponent->SetupAttachment(this->GetCapsuleComponent());
	this->InteractableBoxComponent = boxComponent;
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &APG_P1Character::OnBeginOverlap);
	boxComponent->OnComponentEndOverlap.AddDynamic(this, &APG_P1Character::OnEndOverlap);
}

// Called when the game starts or when spawned
void APG_P1Character::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(this->Controller);
	if (!playerController) {
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	if (!subsystem) {
		return;
	}

	subsystem->AddMappingContext(this->DefaultMappingContext, 0);
}

void APG_P1Character::Move(const FInputActionValue& value)
{
	if (!this->Controller) {
		return;
	}

	FVector2D moveVector = value.Get<FVector2D>();
	FVector forward = FRotator(0, this->GetControlRotation().Yaw, 0).Vector();
	FVector right = FRotator(0, 90.0, 0).RotateVector(forward);
	AddMovementInput(forward, moveVector.Y);
	AddMovementInput(right, moveVector.X);
}

void APG_P1Character::Look(const FInputActionValue &value)
{
	if (!this->Controller) {
		return;
	}

	FVector2D vector = value.Get<FVector2D>();
	this->AddControllerYawInput(vector.X);
	this->AddControllerPitchInput(vector.Y * -1.0);
}

void APG_P1Character::FireEnter(const FInputActionValue &value)
{
	if (!this->Controller) {
		return;
	}

	this->state = EPG_CharacterStates::Fire;
}

void APG_P1Character::FireLeave(const FInputActionValue &value)
{
	if (!this->Controller) {
		return;
	}

	this->state = EPG_CharacterStates::Idle;
}

void APG_P1Character::InteractEnter(const FInputActionValue &value)
{
	if (!this->Controller || !this->ActorInteractable) {
		return;
	}

	this->state = EPG_CharacterStates::Interact;

	this->ActorInteractable->OnInteract.Broadcast(true);
}

void APG_P1Character::InteractLeave(const FInputActionValue &value)
{
	if (this->Controller) {
		this->state = EPG_CharacterStates::Idle;
	}
}

void APG_P1Character::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) {
		return;
	}

	APG_ActorInteractable* interactable = Cast<APG_ActorInteractable>(OtherActor);
	if (!interactable) {
		return;
	}

	this->ActorInteractable = interactable;
}

void APG_P1Character::OnEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) {
		return;
	}

	APG_ActorInteractable* interactable = Cast<APG_ActorInteractable>(OtherActor);
	if (!interactable) {
		return;
	}

	if (interactable == this->ActorInteractable) {
		this->ActorInteractable = nullptr;
	}
}

// Called to bind functionality to input
void APG_P1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* inputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!inputComponent) {
		return;
	}

	inputComponent->BindAction(this->MoveAction, ETriggerEvent::Triggered, this, &APG_P1Character::Move);
	inputComponent->BindAction(this->LookAction, ETriggerEvent::Triggered, this, &APG_P1Character::Look);
	inputComponent->BindAction(this->JumpAction, ETriggerEvent::Triggered, this, &APG_P1Character::Jump);
	inputComponent->BindAction(this->JumpAction, ETriggerEvent::Completed, this, &APG_P1Character::StopJumping);
	inputComponent->BindAction(this->FireAction, ETriggerEvent::Triggered, this, &APG_P1Character::FireEnter);
	inputComponent->BindAction(this->FireAction, ETriggerEvent::Completed, this, &APG_P1Character::FireLeave);
	inputComponent->BindAction(this->InteractAction, ETriggerEvent::Started, this, &APG_P1Character::InteractEnter);
	inputComponent->BindAction(this->InteractAction, ETriggerEvent::Completed, this, &APG_P1Character::InteractLeave);
}
