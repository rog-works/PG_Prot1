// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Components/SphereComponent.h"
#include "PG_Core/PG_Mode.h"
#include "PG_Core/PG_Save.h"
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
	PG_Core::PG_Mode mode;

	bool isSaveActive;
	PG_Core::PlayerSaveData saveData;

	UUserWidget* reticleUI;
	UUserWidget* pauseUI;

	void onInputPause();

	UFUNCTION()
	void onOverlappedSavePoint(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void onContinue();

	UFUNCTION()
	void onReset();

	void onChangeMode(void* sender, PG_Core::EventData* e);

	void initToRun();
	void runToPause();
	void pauseToRun();
	void pauseToReset();

	UUserWidget* createUI(TSubclassOf<UUserWidget> uiClass);
};

