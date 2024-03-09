// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Bird2D.generated.h"

/**
 *
 */
UCLASS()
class SUPERBIRDBONUS_API ABird2D : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird2D();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Timer
	float SeekTimer;

	// Bird location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird properties")
		float MinX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird properties")
		float MaxX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird properties")
		float BirdY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird properties")
		float BirdZ;

	// Max speed of the bird
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird properties")
		float MaxSpeed;

	// Seek target location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird properties")
		FVector SeekTarget;

	// Seek function
	FVector Seek(FVector Target);

	// Seek new location function
	void SeekNewLocation();

	// Spawn egg function
	void SpawnEgg();

	// Update bird animation function
	void UpdateAnimation();

	// Dynamic actor variable you can acces in UE editor, used to spawn eggs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird properties")
		TSubclassOf<AActor> ObjectToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
