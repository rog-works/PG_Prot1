// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PG_Pause.h"

void UW_PG_Pause::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	this->OnVisibilityChanged.AddDynamic(this, &UW_PG_Pause::onVisibilityChanged);
}

void UW_PG_Pause::onVisibilityChanged(ESlateVisibility inVisibility)
{
	if (inVisibility == ESlateVisibility::Visible) {
		this->onOpen();
	} else {
		this->onClose();
	}
}

void UW_PG_Pause::onOpen()
{
	UE_LOG(LogTemp, Warning, TEXT("UW_PG_Pause: on open"));
}

void UW_PG_Pause::onClose()
{
	UE_LOG(LogTemp, Warning, TEXT("UW_PG_Pause: on close"));
}
