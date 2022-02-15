// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyGliderController.h"
#include "Engine/World.h"


AFlyGliderController::AFlyGliderController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void AFlyGliderController::BeginPlay()
{
	Super::BeginPlay();
}

void AFlyGliderController::MoveForward(float Value)
{
	if (CharRef && Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		CharRef->AddMovementInput(Direction, Value);
	}
}

void AFlyGliderController::MoveRight(float Value)
{
	if (CharRef && Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		CharRef->AddMovementInput(Direction, Value);
	}
}

void AFlyGliderController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlyGliderController::SetupInputComponent()
{
	Super::SetupInputComponent();

	
	// Set up gameplay key bindings
	check(InputComponent );

	
	InputComponent->BindAxis("MoveForward", this, &AFlyGliderController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFlyGliderController::MoveRight);


}

void AFlyGliderController::AcknowledgePossession(APawn* PossedPawn)
{
	Super::AcknowledgePossession(PossedPawn);

	//Get the possessed and store as reference
	CharRef = Cast<AFlyGlider>(PossedPawn);
	check(CharRef && "Possed a pawn that isn't a normal player type!");
}

