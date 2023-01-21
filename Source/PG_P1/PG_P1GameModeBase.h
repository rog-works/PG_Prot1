// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
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

	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FAPG_P1GameModeBaseOnLoadSignature, APG_P1GameModeBase, OnLoad);

	UPROPERTY(BlueprintAssignable)
	FAPG_P1GameModeBaseOnLoadSignature OnLoad;

	UFUNCTION(BlueprintCallable)
	bool StringEqual(FString a, FString b);

	UFUNCTION(BlueprintCallable)
	FTimespan DateTimeDiff(FDateTime a, FDateTime b);

protected:
	virtual void BeginPlay() override;

private:
	PG_Core::PG_Mode mode;

	std::unique_ptr<PG_Core::Save> save;

	UUserWidget* reticleUI;
	UUserWidget* pauseMenuUI;

	void initWidget();
	void initInput();
	void initMode();

	void onInputPause();

	UFUNCTION()
	void onContinue();

	UFUNCTION()
	void onReset();

	UFUNCTION()
	void onNewSave();

	void onChangeMode(void* sender, PG_Core::EventData* e);

	void initToLoad();
	void initToRun();
	void loadToRun();
	void runToPause();
	void pauseToRun();
	void pauseToReset();

	UUserWidget* createUI(TSubclassOf<UUserWidget> uiClass, int32 zOrder);
};
