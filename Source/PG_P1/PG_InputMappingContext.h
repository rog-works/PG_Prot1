// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "PG_InputMappingContext.generated.h"

/**
 * 
 */
UCLASS()
class PG_P1_API UPG_InputMappingContext : public UInputMappingContext
{
	GENERATED_BODY()

public:
	UPG_InputMappingContext();

	UInputAction* InputAction;
};
