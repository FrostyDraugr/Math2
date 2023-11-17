// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurveType.h"
#include "Cube.generated.h"

UCLASS()
class MATHCOURSE2_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float startScaleMult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float endScaleMult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECurveTypes curveType;


private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float t;
	int tL;
	FVector startScale;
};
