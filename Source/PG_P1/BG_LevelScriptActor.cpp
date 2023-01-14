// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_LevelScriptActor.h"

ABG_LevelScriptActor::ABG_LevelScriptActor()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: create"));
}

void ABG_LevelScriptActor::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: begin play"));

	Super::BeginPlay();
}
