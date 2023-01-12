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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundWave* se;

protected:
	// XXX PostLoadは適当ではないかもしれない
	virtual void PostLoad() override;

private:
	UFUNCTION()
	void onAccepted();
};
