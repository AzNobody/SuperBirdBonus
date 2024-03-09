// Fill out your copyright notice in the Description page of Project Settings.


#include "Egg2D.h"
#include "Basket2D.h"
#include "EngineUtils.h"

// Sets default values
AEgg2D::AEgg2D()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEgg2D::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEgg2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Destroy egg if it goes off screen
	if (GetActorLocation().Z < -350.0f)
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
			// Remove egg from list
			Basket->EggList.Remove(this);

			// Increase egg total and decrease eggs on screen
			Basket->EggTotal++;
			Basket->EggsOnScreen--;
		}

		// Destroy egg
		Destroy();
	}

}
