// Fill out your copyright notice in the Description page of Project Settings.


#include "Basket2D.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Egg2D.h"
#include "Bird2D.h"
#include "EngineUtils.h"

// Sets default values
ABasket2D::ABasket2D()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set bird max speed
	MaxSpeed = 500.0f;

	// Set basket location
	BasketX = 500.0f;
	BasketY = -220.0f;
	BasketZ = -260.0f;

	// Set egg count
	EggCaught = 0;
	EggTotal = 0;
	EggsOnScreen = 0;
	EggPercentage = 0.0f;

}

// Called when the game starts or when spawned
void ABasket2D::BeginPlay()
{
	Super::BeginPlay();

	// Bind function OnActorBeginOverlap with your class function OnOverlap
	this->OnActorBeginOverlap.AddDynamic(this, &ABasket2D::OnOverlap);

	// Get a reference to the bird using its tag
	ABird2D* Bird = nullptr;
	for (TActorIterator<ABird2D> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->ActorHasTag("BirdTag"))
		{
			Bird = *ActorItr;
			break;
		}
	}

	if (Bird)
	{
		BirdLocation = Bird->GetActorLocation();
		BirdLocation.Y = BasketY;
		BirdLocation.Z = BasketZ;
	}

}

// Called every frame
void ABasket2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If there are no eggs on screen, seek bird
	if (EggsOnScreen == 0)
	{
		// Seek bird
		GetCharacterMovement()->AddInputVector(BasketSeek(BirdLocation));
	}
	else
	{
		// Update egg target from the list of eggs
		if (EggList.Num() > 0)
		{
			EggTarget = EggList[0]->GetActorLocation();
			// Edit EggTarget Y and Z value so the basket isn't decelerating
			EggTarget.Y = BasketY;
			EggTarget.Z = BasketZ;
		}

		// Seek egg
		GetCharacterMovement()->AddInputVector(BasketSeek(EggTarget));
	}

	// Get a reference to the bird using its tag
	ABird2D* Bird = nullptr;
	for (TActorIterator<ABird2D> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->ActorHasTag("BirdTag"))
		{
			Bird = *ActorItr;
			break;
		}
	}

	if (Bird)
	{
		BirdLocation.X = Bird->GetActorLocation().X;
	}

	// Update egg percentage for UI
	if (EggTotal > 0)
	{
		EggPercentage = (EggCaught * 100.0f) / EggTotal;
	}

}

// Called to bind functionality to input
void ABasket2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Seek function
FVector ABasket2D::BasketSeek(FVector Target)
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

// Overlap function
void ABasket2D::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	// Check if the overlapping actor is an egg
	if (auto Egg = Cast<AEgg2D>(OtherActor)) {

		// Remove egg from list
		EggList.Remove(Egg);

		// Increase egg count and decrease egg on screen count
		EggCaught++;
		EggTotal++;
		EggsOnScreen--;

		// Destroy egg
		Egg->Destroy();
	}

}