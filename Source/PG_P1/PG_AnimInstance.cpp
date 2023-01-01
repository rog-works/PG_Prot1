// Fill out your copyright notice in the Description page of Project Settings.


#include "PG_AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPG_AnimInstance::NativeInitializeAnimation()
{
	this->Character = Cast<ACharacter>(this->GetOwningActor());
}

void UPG_AnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	if (!this->TryGetPawnOwner()) {
		return;
	}

	this->GroundSpeed = this->GetGroundSpeed();
	this->CanMove = this->GetCanMove();
	this->IsFalling = this->GetIsFalling();
	this->IsFlying = this->GetIsFlying();
	this->IsJumpUpped = this->GetIsJumpUpped();
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
