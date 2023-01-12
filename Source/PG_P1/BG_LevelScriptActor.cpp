// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ABG_LevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: begin play. mode = %d"), this->mode.current());

	this->reticleUI = this->createUI(this->reticleUIClass);
	this->pauseUI = this->createUI(this->pauseUIClass);
	UW_PG_Pause* pgPauseUI = dynamic_cast<UW_PG_Pause*>(this->pauseUI);
	pgPauseUI->OnShown.AddDynamic(this, &ABG_LevelScriptActor::onShown);

	this->InputComponent->BindKey(EKeys::Tab, IE_Released, this, &ABG_LevelScriptActor::onInputPause);

	this->mode.on("on change mode", this, &ABG_LevelScriptActor::onChangeMode);
	this->mode.setNext(PG_Modes::Run);
}
 
 void ABG_LevelScriptActor::onInputPause()
 {
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on input pause"));

	if (this->mode.current() == PG_Modes::Run) {
 		this->mode.setNext(PG_Modes::Pause);
	}
 }

void ABG_LevelScriptActor::onShown(bool Shown)
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on shown. shown = %d"), Shown);

	if (!Shown) {
		this->mode.setNext(PG_Modes::Run);
	}
}

void ABG_LevelScriptActor::onChangeMode(void* sender, PG_Core::EventData* e)
{
	PG_ModeEventData* data = (PG_ModeEventData*)e;

	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on change mode. before = %d, after = %d"), data->before, data->after);

	if (data->before == PG_Modes::Init && data->after == PG_Modes::Run) {
		this->initToRun();
	} else if (data->before == PG_Modes::Run && data->after == PG_Modes::Pause) {
		this->runToPause();
	} else if (data->before == PG_Modes::Pause && data->after == PG_Modes::Run) {
		this->pauseToRun();
	}
}

void ABG_LevelScriptActor::initToRun()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: init to run"));

	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetInputMode(FInputModeGameOnly());

	this->reticleUI->SetVisibility(ESlateVisibility::Visible);
}

void ABG_LevelScriptActor::runToPause()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: run to pause"));

	this->reticleUI->SetVisibility(ESlateVisibility::Hidden);
	this->pauseUI->SetVisibility(ESlateVisibility::Visible);
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(true);
	controller->SetInputMode(FInputModeUIOnly());
}

void ABG_LevelScriptActor::pauseToRun()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: pause to run"));

	this->reticleUI->SetVisibility(ESlateVisibility::Visible);
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(false);
	controller->SetInputMode(FInputModeGameOnly());
}

UUserWidget* ABG_LevelScriptActor::createUI(TSubclassOf<UUserWidget> uiClass)
{
	UUserWidget* ui = CreateWidget(this->GetWorld(), uiClass);
	ui->AddToViewport();
	ui->SetVisibility(ESlateVisibility::Hidden);
	return ui;
}
