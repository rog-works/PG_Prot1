// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PG_P1Character.h"

void ABG_LevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: begin play. mode = %d"), this->mode.current());

	this->reticleUI = this->createUI(this->reticleUIClass);
	this->pauseUI = this->createUI(this->pauseUIClass);

	UWidget* continueWidget = this->pauseUI->GetWidgetFromName(TEXT("ButtonContinue"));
	if (continueWidget) {
		UButton* button = Cast<UButton>(continueWidget);
		button->OnClicked.AddDynamic(this, &ABG_LevelScriptActor::onContinue);
	}

	UWidget* resetWidget = this->pauseUI->GetWidgetFromName(TEXT("ButtonReset"));
	if (resetWidget) {
		UButton* button = Cast<UButton>(resetWidget);
		button->OnClicked.AddDynamic(this, &ABG_LevelScriptActor::onReset);
	}

	TArray<AActor*> savePointActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(this->GetWorld(), AActor::StaticClass(), TEXT("SavePoint"), savePointActors);
	for (AActor* actor : savePointActors) {
		auto component = actor->GetComponentByClass(USphereComponent::StaticClass());
		USphereComponent* collision = Cast<USphereComponent>(component);
		if (collision) {
			collision->OnComponentBeginOverlap.AddDynamic(this, &ABG_LevelScriptActor::onOverlappedSavePoint);
		}
	}

	this->InputComponent->BindKey(EKeys::Tab, IE_Released, this, &ABG_LevelScriptActor::onInputPause);

	this->mode.on("on change mode", this, &ABG_LevelScriptActor::onChangeMode);
	this->mode.setNext(PG_Core::PG_Modes::Run);
}

void ABG_LevelScriptActor::onInputPause()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on input pause"));

	if (this->mode.current() == PG_Core::PG_Modes::Run) {
		this->mode.setNext(PG_Core::PG_Modes::Pause);
	}
}

void ABG_LevelScriptActor::onOverlappedSavePoint(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on overlapped save point"));

	auto character = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	APG_P1Character* player = Cast<APG_P1Character>(character);
	if (player) {
		this->isSaveActive = true;
		this->saveData = player->save();
	}
}

void ABG_LevelScriptActor::onContinue()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on continue"));

	this->mode.setNext(PG_Core::PG_Modes::Run);
}

void ABG_LevelScriptActor::onReset()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on reset"));

	this->mode.setNext(PG_Core::PG_Modes::Reset);
}

void ABG_LevelScriptActor::onChangeMode(void* sender, PG_Core::EventData* e)
{
	PG_Core::PG_ModeEventData* data = (PG_Core::PG_ModeEventData*)e;

	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: on change mode. before = %d, after = %d"), data->before, data->after);

	if (data->before == PG_Core::PG_Modes::Init && data->after == PG_Core::PG_Modes::Run) {
		this->initToRun();
	} else if (data->before == PG_Core::PG_Modes::Run && data->after == PG_Core::PG_Modes::Pause) {
		this->runToPause();
	} else if (data->before == PG_Core::PG_Modes::Pause && data->after == PG_Core::PG_Modes::Run) {
		this->pauseToRun();
	} else if (data->before == PG_Core::PG_Modes::Pause && data->after == PG_Core::PG_Modes::Reset) {
		this->pauseToReset();
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

void ABG_LevelScriptActor::pauseToReset()
{
	UE_LOG(LogTemp, Warning, TEXT("ABG_LevelScriptActor: pause to reset"));

	this->reticleUI->SetVisibility(ESlateVisibility::Visible);
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(false);
	controller->SetInputMode(FInputModeGameOnly());

	auto character = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	APG_P1Character* player = Cast<APG_P1Character>(character);
	if (player && this->isSaveActive) {
		player->load(this->saveData);
	}

	this->mode.setNext(PG_Core::PG_Modes::Run);
}

UUserWidget* ABG_LevelScriptActor::createUI(TSubclassOf<UUserWidget> uiClass)
{
	UUserWidget* ui = CreateWidget(this->GetWorld(), uiClass);
	ui->AddToViewport();
	ui->SetVisibility(ESlateVisibility::Hidden);
	return ui;
}
