// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/BoxComponent.h"

// Sets default values
ABird::ABird()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create BoxComponent and set as RootComponent for the Actor
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	// Create StaticMeshComponent and Attach to BoxComponent
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	// Set default bird speed
	Speed = 500.f;

}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

	// Create a random FVector with X value between 200 and 2800 and other axis to 0
	SeekTarget = FVector(FMath::RandRange(200, 2800), 0, 0);
	// Debug print on screen
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SeekTarget: %s"), *SeekTarget.ToString()));

}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If statement to check if the bird is close to the target
	if (FVector::Dist(GetActorLocation(), SeekTarget) < 100)
	{
		// Debug print on screen
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Close")));

		// Create a random FVector with X value between 200 and 2200 and other axis to 0
		SeekTarget = FVector(FMath::RandRange(200, 2200), 0, 0);
	}

	// Move the bird to the seek target
	StaticMesh->AddForce(Seek(SeekTarget) * Speed * DeltaTime);

}

FVector ABird::Seek(FVector vTarget)
{
	FVector vDesired = vTarget - GetActorLocation();

	vDesired.Normalize();

	vDesired *= 500.0f;

	FVector vSteering = vDesired - StaticMesh->GetPhysicsLinearVelocity();;

	vSteering.GetClampedToMaxSize(500.0f);

	vSteering.Y = 0;
	vSteering.Z = 0;

	return vSteering;

}
