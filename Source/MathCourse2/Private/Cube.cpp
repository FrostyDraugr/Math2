// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "JMath.h"
#include "CurveType.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	t = 0;
	tL = 1;
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	startScale = Mesh->GetRelativeScale3D();
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (t > playTime || t < 0)
		tL *= -1;

	t += DeltaTime * tL;
	
	float normal = JMath::InvLerp(0, playTime, t);


	FVector minScale = startScale * startScaleMult;
	FVector maxScale = startScale * endScaleMult;

	switch (curveType)
	{
		case ECurveTypes::Linear:
			break;

		case ECurveTypes::InverseCurve:
			normal = JMath::InverseCurveNormal(normal);
			break;

		default:
			break;
	}
	
	
	FVector currentScale = JMath::VectorLerp(minScale, maxScale, normal);

	Mesh->SetWorldScale3D(currentScale);
}

