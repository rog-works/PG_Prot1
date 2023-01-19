// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Sound/SoundWave.h"
#include "PG_AcceptButton.generated.h"

/**
 * 
 */
UCLASS()
class PG_P1_API UPG_AcceptButton : public UButton
{
	GENERATED_BODY()

public:
	UPG_AcceptButton();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* se;

private:
	UFUNCTION()
	void onAccepted();
};
