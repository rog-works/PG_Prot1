// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "PG_Mode.h"
#include "W_PG_Pause.h"
#include "BG_LevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class PG_P1_API ABG_LevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UMG")
	TSubclassOf<UUserWidget> reticleUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UMG")
	TSubclassOf<UUserWidget> pauseUIClass;

protected:
	virtual void BeginPlay() override;

private:
	PG_Mode mode;

	UUserWidget* reticleUI;
	UUserWidget* pauseUI;

	void onInputPause();

	UFUNCTION()
	void onShown(bool Show);

	void onChangeMode(void* sender, PG_Core::EventData* e);

	void initToRun();
	void runToPause();
	void pauseToRun();

	UUserWidget* createUI(TSubclassOf<UUserWidget> uiClass);
};

