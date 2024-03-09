// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird2D.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Basket2D.h"
#include "EngineUtils.h"

// Sets default values
ABird2D::ABird2D()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set bird max speed
	MaxSpeed = 500.0f;

	// Set timer
	SeekTimer = 0.0f;

	// Set bird location
	MinX = 50.0f;
	MaxX = 950.0f;
	BirdY = -230.0f;
	BirdZ = 240.0f;

}

// Called when the game starts or when spawned
void ABird2D::BeginPlay()
{
	Super::BeginPlay();

	// Create FVector with random X value
	SeekTarget = FVector(FMath::RandRange(MinX, MaxX), BirdY, BirdZ);

}

// Called every frame
void ABird2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Increment timer
	SeekTimer += DeltaTime;

	// If bird is close to target, create new seek target and spawn egg
	if (GetActorLocation().X - SeekTarget.X <= 10.0f && SeekTimer > 0.7f)
	{
		SeekNewLocation();
		// Reset timer to prevent new seek target being created every frame
		SeekTimer = 0.0f;
	}

	// Seek target location using character movement component
	GetCharacterMovement()->AddInputVector(Seek(SeekTarget));

	// Update bird animation
	UpdateAnimation();

}

// Called to bind functionality to input
void ABird2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Seek function
FVector ABird2D::Seek(FVector Target)
{
	// Calculate desired velocity
	FVector DesiredLocation = Target - GetActorLocation();

	// Normalize desired velocity
	DesiredLocation.Normalize();

	// Scale desired velocity by max speed
	DesiredLocation *= MaxSpeed;

	// Calculate steering force
	FVector SteeringForce = DesiredLocation - GetVelocity();

	// Limit steering force
	SteeringForce.GetClampedToMaxSize(MaxSpeed);

	// Lock Y and Z axis
	SteeringForce.Y = 0;
	SteeringForce.Z = 0;

	// Return direction
	return SteeringForce;

}

// Seek new location
void ABird2D::SeekNewLocation()
{
	// Create new seek vector at least 150 units away from current location
	while (FMath::Abs(GetActorLocation().X - SeekTarget.X) < 150)
	{
		SeekTarget = FVector(FMath::RandRange(MinX, MaxX), BirdY, BirdZ);

	}

	// Spawn egg
	SpawnEgg();
}

// Spawn egg
void ABird2D::SpawnEgg()
{
	// Get bird location
	FVector Location = GetActorLocation();

	// Check object to spawn is not null
	if (ObjectToSpawn)
	{
		AActor* SpawnedEgg = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, Location, FRotator(0, 0, 0));

		// Check if the spawned egg is valid
		if (SpawnedEgg)
		{
			// Get a reference to the basket using its tag
			ABasket2D* Basket = nullptr;
			for (TActorIterator<ABasket2D> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				if (ActorItr->ActorHasTag("BasketTag"))
				{
					Basket = *ActorItr;
					break;
				}
			}

			if (Basket)
			{
				// Increment the number of eggs on screen
				Basket->EggsOnScreen++;

				// Add the egg to the basket's egg list
				Basket->EggList.Add(SpawnedEgg);
			}
		}
	}
}

// Update bird animation
void ABird2D::UpdateAnimation()
{
	// Get the character's velocity
	FVector Velocity = GetVelocity();

	// Calculate the rotation angle based on the character's movement direction
	float RotationAngle = FMath::Atan2(Velocity.Y, Velocity.X) * 180.0f / PI;

	// Set the rotation of the character to match the movement direction
	FRotator NewRotation = FRotator(0.0f, RotationAngle, 0.0f);
	SetActorRotation(NewRotation);

}