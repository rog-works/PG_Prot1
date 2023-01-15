// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PG_Core/PG_Mode.h"
#include "PG_Core/PG_Save.h"
#include "PG_Core/Extention/UESavePersister.h"
#include "PG_P1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PG_P1_API APG_P1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APG_P1GameModeBase();
	~APG_P1GameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UMG")
	TSubclassOf<UUserWidget> reticleUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UMG")
	TSubclassOf<UUserWidget> pauseMenuUIClass;

protected:
	virtual void BeginPlay() override;

private:
	PG_Core::PG_Mode mode;

	std::unique_ptr<PG_Core::Save> save;

	UUserWidget* reticleUI;
	UUserWidget* pauseMenuUI;

	void initWidget();
	void initSavePoint();
	void initInput();
	void initMode();

	void onInputPause();

	UFUNCTION()
	void onOverlappedSavePoint(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void onContinue();

	UFUNCTION()
	void onReset();

	UFUNCTION()
	void onNewSave();

	void onChangeMode(void* sender, PG_Core::EventData* e);

	void initToRun();
	void runToPause();
	void pauseToRun();
	void pauseToReset();

	UUserWidget* createUI(TSubclassOf<UUserWidget> uiClass);
};
