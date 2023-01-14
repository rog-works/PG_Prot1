// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BG_LevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class PG_P1_API ABG_LevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ABG_LevelScriptActor();

protected:
	virtual void BeginPlay() override;
};

