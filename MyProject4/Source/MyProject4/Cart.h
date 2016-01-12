// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Cart.generated.h"

UCLASS()
class MYPROJECT4_API ACart : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	
public:
	// Sets default values for this pawn's properties
	ACart();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cart", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BodyMesh;

	/** Arrows from which the suspension will be calculated */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* FrontRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* FrontLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* BackRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* BackLeft;

	/** Wheels which sit at the end of the suspension raycast*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wheel", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FrontRightWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wheel", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FrontLeftWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wheel", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BackRightWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wheel", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BackLeftWheel;

	UPROPERTY(EditANywhere, Category = "Physics")
	float SpringStrength;

	UPROPERTY(EditANywhere, Category = "Physics")
	float SpringLength;

	UPROPERTY(EditANywhere, Category = "Physics")
	float WheelRadius;

	/** Array of arrows so they can be looped through easily */
	TArray<class UArrowComponent*> Arrows;

	/** Array of Wheels so they can be looped through easily */
	TArray<class UStaticMeshComponent*> Wheels;

};
