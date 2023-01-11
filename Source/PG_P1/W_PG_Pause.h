// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PG_Pause.generated.h"

/**
 * 
 */
UCLASS()
class PG_P1_API UW_PG_Pause : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void onVisibilityChanged(ESlateVisibility inVisibility);

	void onOpen();
	void onClose();
};
