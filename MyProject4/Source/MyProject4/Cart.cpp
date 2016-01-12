// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject4.h"
#include "Cart.h"


// Sets default values
ACart::ACart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FrontRight = CreateDefaultSubobject<UArrowComponent>(TEXT("FrontRight"));
	FrontLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("FrontLeft"));
	BackRight = CreateDefaultSubobject<UArrowComponent>(TEXT("BackRight"));
	BackLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("BackLeft"));
	
	Arrows.Add(FrontRight);
	Arrows.Add(FrontLeft);
	Arrows.Add(BackRight);
	Arrows.Add(BackLeft);

	for (auto Arrow : Arrows)
	{
		Arrow->AttachTo(BodyMesh);
	}

	FrontRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontRightWheel"));
	FrontLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLeftWheel"));
	BackRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackRightWheel"));
	BackLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackLeftWheel"));

	Wheels.Add(FrontRightWheel);
	Wheels.Add(FrontLeftWheel);
	Wheels.Add(BackRightWheel);
	Wheels.Add(BackLeftWheel);

	for (auto Wheel : Wheels)
	{
		Wheel->AttachTo(RootComponent);
	}
}

// Called when the game starts or when spawned
void ACart::BeginPlay()
{
	Super::BeginPlay();
	BodyMesh->SetSimulatePhysics(true);
}

// Called every frame
void ACart::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	auto World = GetWorld();
	for (int32 i = 0; i < 4; i++)
	{
		FHitResult HitResult(ForceInit);
		FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
		Params.bTraceComplex = true;
		//Params.bTraceAsyncScene = true;
		Params.bReturnPhysicalMaterial = true;

		const FName TraceTag("MyTraceTag");
		World->DebugDrawTraceTag = TraceTag;
		Params.TraceTag = TraceTag;

		

		bool Hit = World->LineTraceSingleByChannel(HitResult, Arrows[i]->GetComponentLocation(), Arrows[i]->GetComponentLocation() + Arrows[i]->GetForwardVector() * (SpringLength + WheelRadius), ECC_PhysicsBody, Params);
		if (Hit)
		{
			FVector Force = HitResult.ImpactNormal * SpringStrength * BodyMesh->GetMass() * (1 - HitResult.Distance / (SpringLength + WheelRadius));
			BodyMesh->AddForceAtLocation(Force, Arrows[i]->GetComponentLocation());
			Wheels[i]->SetWorldLocation(HitResult.Location - (Arrows[i]->GetForwardVector() * WheelRadius));
		}
		else
		{
			Wheels[i]->SetWorldLocation(Arrows[i]->GetComponentLocation() + Arrows[i]->GetForwardVector() * SpringLength);
		}
		
	}
}

// Called to bind functionality to input
void ACart::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

