// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PG_ActorInteractable.generated.h"

UCLASS()
class PG_P1_API APG_ActorInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APG_ActorInteractable();

	UFUNCTION(BlueprintCallable) // , Category = Weapon)
	virtual void OnInteract(bool On);
};
