// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MATHCOURSE2_API JMath
{
public:
	JMath();
	~JMath();

	static float Lerp(float a, float b, float n);

	static float InverseCurveNormal(float n);

	static float InvLerp(float a, float b, float value);

	static FVector VectorLerp(FVector a, FVector b, float n);

	static float Clamp(float min, float max, float value);
};
