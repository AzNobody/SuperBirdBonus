// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bird.generated.h"

UCLASS()
class SUPERBIRDBONUS_API ABird : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMesh;

public:
	// Sets default values for this actor's properties
	ABird();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Bird speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird")
		float Speed;

	// Target Vector to seek
	FVector SeekTarget;

	// Seek function
	FVector Seek(const FVector vTarget);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
