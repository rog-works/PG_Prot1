// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedActionKeyMapping.h"
#include "PG_InputMappingContext.h"
#include "PG_IA_Move.h"

UPG_InputMappingContext::UPG_InputMappingContext()
{
	UInputAction* moveIA = NewObject<UPG_IA_Move>();

	// up
	FEnhancedActionKeyMapping up = FEnhancedActionKeyMapping(moveIA, EKeys::W);
	UInputModifierSwizzleAxis* upAxis = NewObject<UInputModifierSwizzleAxis>();
	upAxis->Order = EInputAxisSwizzle::YXZ;
	up.Modifiers.Add(upAxis);

	// down
	FEnhancedActionKeyMapping down = FEnhancedActionKeyMapping(moveIA, EKeys::S);
	UInputModifierSwizzleAxis* downAxis = NewObject<UInputModifierSwizzleAxis>();
	downAxis->Order = EInputAxisSwizzle::YXZ;
	UInputModifierNegate* downNegate = NewObject<UInputModifierNegate>();
	down.Modifiers.Add(downAxis);
	down.Modifiers.Add(downNegate);

	// left
	FEnhancedActionKeyMapping left = FEnhancedActionKeyMapping(moveIA, EKeys::A);
	UInputModifierNegate* leftNegate = NewObject<UInputModifierNegate>();
	left.Modifiers.Add(leftNegate);

	// right
	FEnhancedActionKeyMapping right = FEnhancedActionKeyMapping(moveIA, EKeys::D);

	// add bindings
	this->InputAction = moveIA;
	this->Mappings.Add(up);
	this->Mappings.Add(down);
	this->Mappings.Add(left);
	this->Mappings.Add(right);
}
