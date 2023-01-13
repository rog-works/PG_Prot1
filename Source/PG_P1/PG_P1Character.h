// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "PG_Core/PG_Save.h"
#include "PG_ActorInteractable.h"
#include "PG_P1Character.generated.h"

UENUM(BlueprintType)
enum class EPG_CharacterStates : uint8
{
	Idle,
	Interact,
	Fire,
};

UCLASS()
class PG_P1_API APG_P1Character : public ACharacter, public PG_Core::ISaver<PG_Core::PlayerSaveData>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APG_P1Character(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character, meta=(AllowPrivateAccess = "true"))
	EPG_CharacterStates state;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess = "true"))
	APG_ActorInteractable* ActorInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> InteractableBoxComponent;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual PG_Core::PlayerSaveData save() override;
	virtual void load(PG_Core::PlayerSaveData saveData) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void FireEnter(const FInputActionValue& value);
	void FireLeave(const FInputActionValue& value);
	void InteractEnter(const FInputActionValue& value);
	void InteractLeave(const FInputActionValue& value);

private:
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
