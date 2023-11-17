// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.h"
#include "BallActor.generated.h"

UCLASS()
class MATHCOURSE2_API ABallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetRadius();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

private:
	float radius;
	FVector Velocity;
	FVector GravityVelocity;

	TArray<ACube*> StaticColl;
	TArray<ABallActor*> DynColl;

	float bounceStr;

	FVector drag;
};
