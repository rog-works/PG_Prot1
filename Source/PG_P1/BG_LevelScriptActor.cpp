// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ABG_LevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	this->pauseUI = CreateWidget(this->GetWorld(), this->pauseUIClass);
	this->pauseUI->AddToViewport();
	this->pauseUI->SetVisibility(ESlateVisibility::Hidden);

	UW_PG_Pause* pgPauseUI = dynamic_cast<UW_PG_Pause*>(this->pauseUI);
	pgPauseUI->OnShown.AddDynamic(this, &ABG_LevelScriptActor::onShown);

	this->InputComponent->BindKey(EKeys::Tab, IE_Released, this, &ABG_LevelScriptActor::onInputPause);

	this->mode.on("on change mode", this, &ABG_LevelScriptActor::onChangeMode);
}
 
 void ABG_LevelScriptActor::onInputPause()
 {
	if (this->mode.current() == PG_Modes::Run) {
 		this->mode.setNext(PG_Modes::Pause);
	}
 }

void ABG_LevelScriptActor::onShown(bool Shown)
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on shown"));

	if (!Shown) {
		this->mode.setNext(PG_Modes::Run);
	}
}

void ABG_LevelScriptActor::onChangeMode(void* sender, PG_Core::EventData* e)
{
	PG_ModeEventData* data = (PG_ModeEventData*)e;
	if (data->after == PG_Modes::Pause) {
		this->toPause();
	} else if (data->before == PG_Modes::Pause) {
		this->toRun();
	}
}

void ABG_LevelScriptActor::toPause()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on pause begin"));

	this->pauseUI->SetVisibility(ESlateVisibility::Visible);
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(true);
	controller->SetInputMode(FInputModeUIOnly());
}

void ABG_LevelScriptActor::toRun()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on pause end"));

	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(false);
	controller->SetInputMode(FInputModeGameOnly());
}
