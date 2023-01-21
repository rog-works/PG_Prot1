// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PG_InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PG_P1_API UPG_InteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPG_InteractComponent();

	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FUPG_InteractComponentInteractSignature, UPG_InteractComponent, OnInteract, bool, On);

	UPROPERTY(BlueprintAssignable)
	FUPG_InteractComponentInteractSignature OnInteract;
};
