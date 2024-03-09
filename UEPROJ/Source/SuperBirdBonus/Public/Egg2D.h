// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Egg2D.generated.h"

/**
 *
 */
UCLASS()
class SUPERBIRDBONUS_API AEgg2D : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEgg2D();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};