// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FlyGlider.generated.h"

UCLASS()
class WORKSHOP_API AFlyGlider : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFlyGlider();

	//Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Keep track how much we are rotating
	FRotator FlyCurrentRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flying Parameters")
	FRotator FlyRotationAcceleration;

	//Define values for the max rotation we can do
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flying Parameters")
	float FlyRotationMaxRoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flying Parameters")
	float FlyRotationMaxPitch;

	//Define a speed, as well as an accelleration value
	float FlyCurrentSpeed;
	
	UPROPERTY(EditAnywhere, Category = "Flying Parameters")
	float FlySpeedAcceleration;

	//Define the Gravity that should be effected on our flying object
	UPROPERTY(EditAnywhere, Category = "Flying Parameters")
	float FlyGravityAcceleration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flying Parameters")
	float FlyGravityMax;

	//The velocity of our flying object
	FVector FlyingVelocity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
