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
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACube::StaticClass(), FoundActors);

	for (AActor* actor : FoundActors)
	{
		ACube* staticCollider = Cast<ACube>(actor);
		StaticColl.Add(staticCollider);
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Test");
	}

	//FString printStr = FString::SanitizeFloat(JMath::NormalizeVector(GravityVelocity).X);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, printStr);

}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Pos = GetActorLocation();
	//Physics
		//Check if grounded, only have spheres so this check is basicaly useless	
			//If Other Actor is bellow && Distance is less than 0
			//Between the two actors radius

	//Collission Check
		//Check if Distance between ThisActor and OtherActor is less than
		//This radius + Other Radius, if so add velocity away from other actor
	for (ACube* staticColl : StaticColl)
	{
		FVector posB = staticColl->GetActorLocation();
		float distance = FVector::Dist(Pos, posB);
		if (distance < (GetRadius() + staticColl->GetRadius()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, "collission");
			//GetBounceDir then add Force
			FVector dir = JMath::GetBounceNormal(Pos, posB);
			Velocity += dir * bounceStr;

			if (JMath::IsLarger(Pos.Y, posB.Y))
			{
				Velocity.Y += bounceStr * 0.5f;
			}
		}
	}
	
	//This drag is weird and simplistic, should probably use a curve here instead
	//Velocity -= drag * DeltaTime;
	
	//Just capping Gravity Down force, would depend on the atosmphere
	//Velocity.Z = GravityVelocity.Z;
	//if (Velocity.Z < GravityVelocity.Z)

	Velocity.Z += GravityVelocity.Z * DeltaTime;

	SetActorLocation(Pos + (Velocity) * DeltaTime);
}

float ABallActor::GetRadius()
{
	//This is really stupid and only works with Uniform scaling and spheres
	FVector scale = Mesh->GetRelativeScale3D();
	return radius * scale.X;
}

