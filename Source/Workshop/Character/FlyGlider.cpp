// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyGlider.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFlyGlider::AFlyGlider()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void AFlyGlider::BeginPlay()
{
	Super::BeginPlay();

	//Set it to flying to handle flying without built in physics
	GetCharacterMovement()->MovementMode = MOVE_Flying;
}

// Called every frame
void AFlyGlider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Only do this calculation per frame if we are flying
	if (GetCharacterMovement()->MovementMode == MOVE_Flying || GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		//Update rotation Section based on input//

		//Deals with Roll
		FlyCurrentRotation.Roll = FMath::FInterpTo(FlyCurrentRotation.Roll, GetLastMovementInputVector().X * FlyRotationMaxRoll, DeltaTime, 10);

		//Deals with Pitch
		float ClampedPitch = FMath::Clamp(((GetLastMovementInputVector().Y * FlyRotationAcceleration.Pitch) * DeltaTime) + FlyCurrentRotation.Pitch, FlyRotationMaxPitch * -1, FlyRotationMaxPitch);
		FlyCurrentRotation.Pitch = FMath::FInterpTo(FlyCurrentRotation.Pitch, ClampedPitch, DeltaTime, 100);

		//Deals with Yaw
		FlyCurrentRotation.Yaw = FMath::FInterpTo(FlyCurrentRotation.Yaw, ((GetLastMovementInputVector().X * FlyRotationAcceleration.Yaw) * DeltaTime) + FlyCurrentRotation.Yaw, DeltaTime, 100);

		//Apply the new Rotation we got from our input
		SetActorRotation(FRotator(0, -90, 0) + FlyCurrentRotation);


		//Update Speed//
		
		float ClampedSpeed= FMath::Clamp(((FlySpeedAcceleration * DeltaTime) * ((FlyCurrentRotation.Pitch * -1.0f) / 90.0f)) + FlyCurrentSpeed, 0.0f, FlyGravityMax);
		FlyCurrentSpeed = ClampedSpeed;


		//Move Character through space//

		//What Does Gravity want the character to do?
		FVector GravityVec(FlyingVelocity.X, FlyingVelocity.Y,FMath::Max((FlyGravityAcceleration * DeltaTime) - FlyingVelocity.Z, FlyGravityMax * - 1));

		//What the Flight Path Wants
		FVector FlightVec = UKismetMathLibrary::GetForwardVector(FlyCurrentRotation) * FlyCurrentSpeed;

		//Closer to gravity speed the player is, more control is had.
		FlyingVelocity = FMath::Lerp(GravityVec, FlightVec, FlyCurrentSpeed / FlyGravityMax);
		AddActorWorldOffset(FlyingVelocity * DeltaTime, true);
	}


}

// Called to bind functionality to input
void AFlyGlider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

