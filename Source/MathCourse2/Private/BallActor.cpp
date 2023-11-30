// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "Kismet/GameplayStatics.h"
#include "JMath.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABallActor::ABallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	radius = 160.f;
	Velocity = (FVector(0, 0, 0));
	GravityVelocity = FVector(0, 0, -980);
	bounceStr = 1000.f;
	drag = FVector(0.1f, 0.1f, 1);
	spawnDisMax = 500.f;
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();

	DynMaterial = UMaterialInstanceDynamic::Create(Material, this);

	spawnPos = GetActorLocation();

	Mesh->SetMaterial(0, DynMaterial);

	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACube::StaticClass(), FoundActors);

	//Collidable object cache
	for (AActor* actor : FoundActors)
	{
		ACube* staticCollider = Cast<ACube>(actor);
		StaticColl.Add(staticCollider);
	}
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Pos = GetActorLocation();
	//Assignment 4: Collission Check
		//Check if Distance between ThisActor and OtherActor is less than
		//This radius + Other Radius, if so add velocity away from other actor
	for (ACube* staticColl : StaticColl)
	{
		FVector posB = staticColl->GetActorLocation();
		float distance = FVector::Dist(Pos, posB);
		
			//Assignment 3: Intersection, if ball collider is within collider of obstacle
		if (distance < (GetRadius() + staticColl->GetRadius()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, "collission");
			//GetBounceDir then add Force
			FVector dir = JMath::GetBounceNormal(Pos, posB);
			Velocity = dir * JMath::GetMagnitude(Velocity);
			//Velocity += dir * bounceStr;

			//Assignment 1, if ball hits the obstacles on top, add an upward force
			if (JMath::IsLarger(posB.Y, Pos.Y))
			{
				Velocity.Y += bounceStr;
			}
		}
	}
	
	Velocity.Z += GravityVelocity.Z * DeltaTime;

	SetActorLocation(Pos + (Velocity) * DeltaTime);

	//Generate Normalise PerlinNoise Value depending on Actor Location
	//Right now it's just flickering a bunch, which I mean makes sense...
	//I should probably offload this to a timeline that Lerps the color to a target color every cycle
	float pNoise = FMath::PerlinNoise3D(GetActorLocation());
	DynMaterial->SetScalarParameterValue("Normal", pNoise);
	
	if (Pos.Z < -2000)
		ResetPos();
}

float ABallActor::GetRadius()
{
	//This is really stupid and only works with Uniform scaling and spheres
	FVector scale = Mesh->GetRelativeScale3D();
	return radius * scale.X;
}

void ABallActor::ResetPos()
{
	//Assignment 5: Reset ball at a random distance away
	//from original spawn position depending on the location
	//the ball "died" at.
	float pNoise = FMath::PerlinNoise3D(GetActorLocation());
	FRandomStream random;
	random.GenerateNewSeed();
	FVector randomVector = random.GetUnitVector();

	FVector SpawnOffset = spawnPos + (randomVector * (pNoise * spawnDisMax));

	Velocity = FVector(0, 0, 0);
	
	SetActorLocation(SpawnOffset);
}



