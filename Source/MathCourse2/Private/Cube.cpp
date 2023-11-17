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
	Mesh->bAlwaysCreatePhysicsState = false; //Used to be true but for new custom physics I have to turn this off.
	Mesh->SetNotifyRigidBodyCollision(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionProfileName("BlockAllDynamic");
	Mesh->OnComponentHit.AddDynamic(this, &ACube::OnHit);
	RootComponent = Mesh;

	t = 0;
	tL = 1;
	playTime = 1;
	startScaleMult = 0;
	endScaleMult = 1;
	curveType = ECurveTypes::Linear;
	radiusC = 160.f;
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

		case ECurveTypes::PerlinNoise:
			normal = JMath::PerlinNoiseRandCurve(normal);
			break;

		//Add more curves as necessary
		default:
			break;
	}
	
	
	FVector currentScale = JMath::VectorLerp(minScale, maxScale, normal);

	Mesh->SetWorldScale3D(currentScale);
}

float ACube::GetRadius()
{
	//Only works with uniform scale
	return radiusC * Mesh->GetRelativeScale3D().X;
}

void ACube::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Hit");
	
	//Is Above
	if (JMath::IsLarger(OtherActor->GetActorLocation().Z, this->GetActorLocation().Z))
	{
		FVector up = OtherActor->GetActorUpVector();
		OtherComp->AddForce(up * 100000 * OtherComp->GetMass());
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Above");
	}
	
}


