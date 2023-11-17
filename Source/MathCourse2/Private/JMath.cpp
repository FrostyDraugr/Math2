// Fill out your copyright notice in the Description page of Project Settings.


#include "JMath.h"

JMath::JMath()
{
}

JMath::~JMath()
{
}

float JMath::Lerp(float a, float b, float n)
{
	n = JMath::Clamp(0, 1, n);

	return (a + (b - a) * n);
}

float JMath::InverseCurveNormal(float n)
{
	n = JMath::Clamp(0, 1, n);

	return n = 1 - (n * n);
}

float JMath::PerlinNoiseRandCurve(float n)
{
	float pNoise = FMath::PerlinNoise1D(n);
	return pNoise * pNoise;
}

float JMath::InvLerp(float a, float b, float value)
{
	return JMath::Clamp(0, 1, (value - a) / (b - a));
}

FVector JMath::VectorLerp(FVector a, FVector b, float n)
{
	n = JMath::Clamp(0, 1, n);
	
	return FVector(
		a.X + (b.X - a.X) * n,
		a.Y + (b.Y - a.Y) * n,
		a.Z + (b.Z - a.Z) * n
	);
}

float JMath::Clamp(float min, float max, float value)
{
	float v = value;

	if (value < min)
		v = min;
	
	if (value > max)
		v = max;

	return v;
}

bool JMath::IsLarger(float a, float b)
{
	return a > b;
}

FVector JMath::GetBounceNormal(FVector a, FVector b)
{
	return NormalizeVector(a - b);
}

float JMath::GetMagnitude(FVector a)
{
	//Shame, using FMath in JMath
	return FMath::Sqrt((a.X * a.X) + (a.Y * a.Y) + (a.Z * a.Z));
}

FVector JMath::NormalizeVector(FVector a)
{
	return a / GetMagnitude(a);
}
