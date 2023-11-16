// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class ECurveTypes : uint8
{
	Linear UMETA(DisplayName = "Linear"),
	InverseCurve UMETA(DisplayName = "Inverse"),
};