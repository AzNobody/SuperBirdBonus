// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Basket2D.generated.h"

/**
 *
 */
UCLASS()
class SUPERBIRDBONUS_API ABasket2D : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasket2D();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Basket location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basket properties")
		float BasketX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basket properties")
		float BasketY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basket properties")
		float BasketZ;

	// Max speed of the basket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basket properties")
		float MaxSpeed;

	// Egg location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basket properties")
		FVector EggTarget;

	// Bird location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basket properties")
		FVector BirdLocation;

	// Egg list
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basket properties")
		TArray<AActor*> EggList;

	// Egg count
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basket properties")
		int EggCaught;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basket properties")
		int EggTotal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basket properties")
		int EggsOnScreen;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basket properties")
		float EggPercentage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Seek function
	FVector BasketSeek(FVector Target);

	// Overlap function
	UFUNCTION()
		void OnOverlap(AActor* MyActor, AActor* OtherActor);

};
