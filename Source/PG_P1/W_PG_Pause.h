// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Blueprint/UserWidget.h"
#include "W_PG_Pause.generated.h"

/**
 * 
 */
UCLASS()
class PG_P1_API UW_PG_Pause : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FUW_PG_PauseOnShowSignature, UW_PG_Pause, OnShown, bool, Shown);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FUW_PG_PauseOnShowSignature OnShown;

protected:
	virtual void NativeOnInitialized() override;
};
