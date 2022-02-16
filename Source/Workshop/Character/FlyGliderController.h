// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

//UE Headers
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

//Custom Headers
#include "FlyGlider.h"

#include "FlyGliderController.generated.h"

/**
 * 
 */
UCLASS()
class WORKSHOP_API AFlyGliderController : public APlayerController
{
	GENERATED_BODY()

public:
	//Functions
	AFlyGliderController();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void AcknowledgePossession(APawn* PossedPawn) override;

	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)	//Base turn rate, in deg/sec. Other scaling may affect final turn rate (For Controllers)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) 	// Base look up/down rate, in deg/sec. Other scaling may affect final rate. (For Controllers)
	float BaseLookUpRate;


	
protected:
	//Functions
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	//Variables
	UPROPERTY()							//Variable to  hold our locally controlled character.
	AFlyGlider* CharRef;  

};
