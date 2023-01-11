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
	this->pauseUI->OnVisibilityChanged.AddDynamic(this, &ABG_LevelScriptActor::onVisibilityChanged);

	this->InputComponent->BindKey(EKeys::Tab, IE_Released, this, &ABG_LevelScriptActor::onInputPause);

	this->mode.on("on change mode", this, &ABG_LevelScriptActor::onChangeMode);
}
 
 void ABG_LevelScriptActor::onInputPause()
 {
	if (this->mode.current() == PG_Modes::Run) {
 		this->mode.setNext(PG_Modes::Pause);
	}
 }

void ABG_LevelScriptActor::onChangeMode(void* sender, PG_Core::EventData* e)
{
	PG_ModeEventData* data = (PG_ModeEventData*)e;
	if (data->after == PG_Modes::Pause) {
		this->onPauseBegin();
	} else if (data->before == PG_Modes::Pause) {
		this->onPauseEnd();
	}
}

void ABG_LevelScriptActor::onVisibilityChanged(ESlateVisibility inVisibility)
{
	if (inVisibility == ESlateVisibility::Hidden) {
		this->mode.setNext(PG_Modes::Run);
	}
}

void ABG_LevelScriptActor::onPauseBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on pause begin"));

	this->pauseUI->SetVisibility(ESlateVisibility::Visible);
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(true);
	controller->SetInputMode(FInputModeUIOnly());
}

void ABG_LevelScriptActor::onPauseEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on pause end"));

	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(false);
	controller->SetInputMode(FInputModeGameOnly());
}
