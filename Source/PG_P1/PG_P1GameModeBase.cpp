// Copyright Epic Games, Inc. All Rights Reserved.


#include "PG_P1GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/SphereComponent.h"
#include "PG_P1Character.h"

APG_P1GameModeBase::APG_P1GameModeBase()
{
	UESavePersister persister = UESavePersister();
	// this->save = new PG_Core::Save(&persister);
}

APG_P1GameModeBase::~APG_P1GameModeBase()
{
	delete this->save;
}

void APG_P1GameModeBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: begin play"));

	this->initWidget();
	this->initSavePoint();
	this->initInput();
	this->initMode();

	this->mode.setNext(PG_Core::PG_Modes::Run);
}

// initialize

void APG_P1GameModeBase::initWidget()
{
	this->reticleUI = this->createUI(this->reticleUIClass);
	this->pauseMenuUI = this->createUI(this->pauseMenuUIClass);

	UUserWidget* pauseUI = Cast<UUserWidget>(this->pauseMenuUI->GetWidgetFromName(TEXT("W_Pause")));

	UWidget* continueWidget = pauseUI->GetWidgetFromName(TEXT("ButtonContinue"));
	if (continueWidget) {
		UButton* button = Cast<UButton>(continueWidget);
		button->OnClicked.AddDynamic(this, &APG_P1GameModeBase::onContinue);
	}

	UWidget* resetWidget = pauseUI->GetWidgetFromName(TEXT("ButtonReset"));
	if (resetWidget) {
		UButton* button = Cast<UButton>(resetWidget);
		button->OnClicked.AddDynamic(this, &APG_P1GameModeBase::onReset);
	}

	UUserWidget* saveUI = Cast<UUserWidget>(this->pauseMenuUI->GetWidgetFromName(TEXT("W_Save")));

	UWidget* newSaveWidget = pauseUI->GetWidgetFromName(TEXT("ButtonNewSave"));
	if (newSaveWidget) {
		UButton* button = Cast<UButton>(newSaveWidget);
		button->OnClicked.AddDynamic(this, &APG_P1GameModeBase::onNewSave);
	}
}

void APG_P1GameModeBase::initSavePoint()
{
	TArray<AActor*> savePointActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(this->GetWorld(), AActor::StaticClass(), TEXT("SavePoint"), savePointActors);
	for (AActor* actor : savePointActors) {
		auto component = actor->GetComponentByClass(USphereComponent::StaticClass());
		USphereComponent* collision = Cast<USphereComponent>(component);
		if (collision) {
			collision->OnComponentBeginOverlap.AddDynamic(this, &APG_P1GameModeBase::onOverlappedSavePoint);
		}
	}
}

void APG_P1GameModeBase::initInput()
{
	// EnableInputを実行しないとInputComponentが有効にならない
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	EnableInput(controller);
	this->InputComponent->BindKey(EKeys::Tab, IE_Released, this, &APG_P1GameModeBase::onInputPause);
}

void APG_P1GameModeBase::initMode()
{
	this->mode.on("on change mode", this, &APG_P1GameModeBase::onChangeMode);
}

// event handling

void APG_P1GameModeBase::onInputPause()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: on input pause"));

	if (this->mode.current() == PG_Core::PG_Modes::Run) {
		this->mode.setNext(PG_Core::PG_Modes::Pause);
	}
}

void APG_P1GameModeBase::onOverlappedSavePoint(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: on overlapped save point"));

	auto character = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	APG_P1Character* player = Cast<APG_P1Character>(character);
	if (player) {
		// this->saveData.general.enabled = true;
		// this->saveData.game.player = player->save();
	}
}

void APG_P1GameModeBase::onContinue()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: on continue"));

	this->mode.setNext(PG_Core::PG_Modes::Run);
}

void APG_P1GameModeBase::onReset()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: on reset"));

	this->mode.setNext(PG_Core::PG_Modes::Reset);
}

void APG_P1GameModeBase::onNewSave()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: on new save"));

	auto character = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	APG_P1Character* player = Cast<APG_P1Character>(character);
	if (player) {
		auto slot = this->save->newSession("slot1");
		PG_Core::SessionSaveData data;
		// data.game.player = player->save();
		// slot->update(&data);
	}
}

void APG_P1GameModeBase::onChangeMode(void* sender, PG_Core::EventData* e)
{
	PG_Core::PG_ModeEventData* data = (PG_Core::PG_ModeEventData*)e;

	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: on change mode. before = %d, after = %d"), data->before, data->after);

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

// mode operation

void APG_P1GameModeBase::initToRun()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: init to run"));

	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetInputMode(FInputModeGameOnly());

	this->reticleUI->SetVisibility(ESlateVisibility::Visible);
}

void APG_P1GameModeBase::runToPause()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: run to pause"));

	this->reticleUI->SetVisibility(ESlateVisibility::Hidden);
	this->pauseMenuUI->SetVisibility(ESlateVisibility::Visible);
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(true);
	controller->SetInputMode(FInputModeUIOnly());
}

void APG_P1GameModeBase::pauseToRun()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: pause to run"));

	this->reticleUI->SetVisibility(ESlateVisibility::Visible);
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(false);
	controller->SetInputMode(FInputModeGameOnly());
}

void APG_P1GameModeBase::pauseToReset()
{
	UE_LOG(LogTemp, Warning, TEXT("APG_P1GameModeBase: pause to reset"));

	this->reticleUI->SetVisibility(ESlateVisibility::Visible);
	APlayerController* controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	controller->SetShowMouseCursor(false);
	controller->SetInputMode(FInputModeGameOnly());

	auto character = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	APG_P1Character* player = Cast<APG_P1Character>(character);
	// if (player && this->saveData.general.enabled) {
	// 	player->load(this->saveData.game.player);
	// }

	this->mode.setNext(PG_Core::PG_Modes::Run);
}

// utility

UUserWidget* APG_P1GameModeBase::createUI(TSubclassOf<UUserWidget> uiClass)
{
	UUserWidget* ui = CreateWidget(this->GetWorld(), uiClass);
	ui->AddToViewport();
	ui->SetVisibility(ESlateVisibility::Hidden);
	return ui;
}
