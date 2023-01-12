// Fill out your copyright notice in the Description page of Project Settings.


#include "PG_AnimInstance.h"
#include "PG_P1Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UPG_AnimInstance::UPG_AnimInstance()
{
	this->GroundSpeed = 0.0;
	this->CanMove = false;
	this->IsFalling = false;
	this->IsFlying = false;
	this->IsJumpUpped = false;
	this->Fired = false;
	this->Interacted = false;
}

void UPG_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	this->Character = Cast<ACharacter>(this->GetOwningActor());
}

void UPG_AnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!this->TryGetPawnOwner()) {
		return;
	}

	this->GroundSpeed = this->GetGroundSpeed();
	this->CanMove = this->GetCanMove();
	this->IsFalling = this->GetIsFalling();
	this->IsFlying = this->GetIsFlying();
	this->IsJumpUpped = this->GetIsJumpUpped();
	this->Fired = this->GetFired();
	this->Interacted = this->GetInteracted();
}

float UPG_AnimInstance::GetGroundSpeed()
{
	return UKismetMathLibrary::VSizeXY(this->Character->GetVelocity());
}

bool UPG_AnimInstance::GetCanMove()
{
	return !this->GetIsFlying();
}

bool UPG_AnimInstance::GetIsFalling()
{
	return this->GetIsFlying() && this->Character->GetVelocity().Z <= 0.0;
}

bool UPG_AnimInstance::GetIsFlying()
{
	return this->Character->GetCharacterMovement()->IsFalling();
}

bool UPG_AnimInstance::GetIsJumpUpped()
{
	return this->GetIsFlying() && this->Character->GetVelocity().Z > 0.0;
}

bool UPG_AnimInstance::GetFired()
{
	return Cast<APG_P1Character>(this->Character)->state == EPG_CharacterStates::Fire;
}

bool UPG_AnimInstance::GetInteracted()
{
	return Cast<APG_P1Character>(this->Character)->state == EPG_CharacterStates::Interact;
}
