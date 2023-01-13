// Fill out your copyright notice in the Description page of Project Settings.


#include "PG_AcceptButton.h"
#include "Kismet/GameplayStatics.h"

UPG_AcceptButton::UPG_AcceptButton()
{
	this->OnClicked.AddDynamic(this, &UPG_AcceptButton::onAccepted);
}

void UPG_AcceptButton::onAccepted()
{
	if (this->se) {
		UGameplayStatics::PlaySound2D(this->GetWorld(), this->se);
	}
}
