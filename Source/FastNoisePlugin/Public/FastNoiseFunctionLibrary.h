// Copyright(c) 2021 Matthew Laukala
// 
// Copyright 2018 Yaki Studios, Inc. All Rights Reserved.
//
// MIT License
//
// Copyright(c) 2017 Jordan Peck
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FastNoiseFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class EInterpolation : uint8
{
	Linear UMETA(DisplayName = "Linear"),
	Hermite UMETA(DisplayName = "Hermite"),
	Quintic UMETA(DisplayName = "Quintic")
};

UENUM(BlueprintType)
enum class EFractalType : uint8
{
	FBM,
	Billow,
	RigidMulti
};

UENUM(BlueprintType)
enum class ESelectInterpolationType : uint8
{
	None,
	CircularIn,
	CircularOut,
	CircularInOut,
	ExponentialIn,
	ExponentialOut,
	ExponentialInOut,
	SineIn,
	SineOut,
	SineInOut,
	Step,
	Linear
};

UCLASS() 
class FASTNOISEPLUGIN_API UFastNoiseFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//2D
	static float GetValue2D(int32 Seed, float Frequency, EInterpolation Interpolation, float X, float Y);
	static float GetValueFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, float X, float Y);
	static float GetPerlin2D(int32 Seed, float Frequency, EInterpolation Interpolation, float X, float Y);
	static float GetPerlinFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, float X, float Y);
	static float GetSimplex2D(int32 Seed, float Frequency, float X, float Y);
	static float GetSimplexFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y);
	static float GetWhiteNoise2D(int32 Seed, float X, float Y);
	static float GetWhiteNoiseInt2D(int32 Seed, int32 X, int32 Y);
	static float GetCubic2D(int32 Seed, float Frequency, float X, float Y);
	static float GetCubicFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y);
	static void GradientPerturb2D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, float& X, float& Y);
	static void GradientPerturbFractal2D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float& X, float& Y);

	//3D
	static float GetValue3D(int32 Seed, float Frequency, EInterpolation Interpolation, float X, float Y, float Z);
	static float GetValueFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, float X, float Y, float Z);
	static float GetPerlin3D(int32 Seed, float Frequency, EInterpolation Interpolation, float X, float Y, float Z);
	static float GetPerlinFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, float X, float Y, float Z);
	static float GetSimplex3D(int32 Seed, float Frequency, float X, float Y, float Z);
	static float GetSimplexFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y, float Z);
	static float GetWhiteNoise3D(int32 Seed, float X, float Y, float Z);
	static float GetWhiteNoiseInt3D(int32 Seed, int32 X, int32 Y, int32 Z);
	static float GetCubic3D(int32 Seed, float Frequency, float X, float Y, float Z);
	static float GetCubicFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y, float Z);
	static void GradientPerturb3D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, float& X, float& Y, float& Z);
	static void GradientPerturbFractal3D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float& X, float& Y, float& Z);

	//4D
	static float GetSimplex4D(int32 Seed, float Frequency, float X, float Y, float Z, float W);
	static float GetSimplexFractal4D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y, float Z, float W);
	static float GetWhiteNoise4D(int32 Seed, float X, float Y, float Z, float W);
	static float GetWhiteNoiseInt4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W);

	// Simplified wrappers
	//2D
	static float GetValue2D(int32 Seed, float Frequency, EInterpolation Interpolation, const FVector2D& Coordinates);
	static float GetValueFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector2D& Coordinates);
	static float GetPerlin2D(int32 Seed, float Frequency, EInterpolation Interpolation, const FVector2D& Coordinates);
	static float GetPerlinFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector2D& Coordinates);
	static float GetSimplex2D(int32 Seed, float Frequency, const FVector2D& Coordinates);
	static float GetSimplexFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector2D& Coordinates);
	static float GetWhiteNoise2D(int32 Seed, const FVector2D& Coordinates);
	static float GetWhiteNoiseInt2D(int32 Seed, const FIntPoint& Coordinates);
	static float GetCubic2D(int32 Seed, float Frequency, const FVector2D& Coordinates);
	static float GetCubicFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector2D& Coordinates);
	static void GradientPerturb2D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, FVector2D& Coordinates);
	static void GradientPerturbFractal2D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, FVector2D& Coordinates);

	//3D
	static float GetValue3D(int32 Seed, float Frequency, EInterpolation Interpolation, const FVector& Coordinates);
	static float GetValueFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector& Coordinates);
	static float GetPerlin3D(int32 Seed, float Frequency, EInterpolation Interpolation, const FVector& Coordinates);
	static float GetPerlinFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector& Coordinates);
	static float GetSimplex3D(int32 Seed, float Frequency, const FVector& Coordinates);
	static float GetSimplexFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector& Coordinates);
	static float GetWhiteNoise3D(int32 Seed, const FVector& Coordinates);
	static float GetWhiteNoiseInt3D(int32 Seed, const FIntVector& Coordinates);
	static float GetCubic3D(int32 Seed, float Frequency, const FVector& Coordinates);
	static float GetCubicFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector& Coordinates);
	static void GradientPerturb3D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, FVector& Coordinates);
	static void GradientPerturbFractal3D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, FVector& Coordinates);

	//4D
	static float GetSimplex4D(int32 Seed, float Frequency, const FVector4& Coordinates);
	static float GetSimplexFractal4D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector4& Coordinates);
	static float GetWhiteNoise4D(int32 Seed, const FVector4& Coordinates);
	static float GetWhiteNoiseInt4D(int32 Seed, const FIntVector4& Coordinates);

	// Blueprint wrappers
	//2D
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetValue2D"))
	static float Blueprint_GetValue2D(int32 Seed, float Frequency, EInterpolation Interpolation, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetValueFractal2D"))
	static float Blueprint_GetValueFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetPerlin2D"))
	static float Blueprint_GetPerlin2D(int32 Seed, float Frequency, EInterpolation Interpolation, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetPerlinFractal2D"))
	static float Blueprint_GetPerlinFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplex2D"))
	static float Blueprint_GetSimplex2D(int32 Seed, float Frequency, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplexFractal2D"))
	static float Blueprint_GetSimplexFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoise2D"))
	static float Blueprint_GetWhiteNoise2D(int32 Seed, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoiseInt2D"))
	static float Blueprint_GetWhiteNoiseInt2D(int32 Seed, const FIntPoint& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetCubic2D"))
	static float Blueprint_GetCubic2D(int32 Seed, float Frequency, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetCubicFractal2D"))
	static float Blueprint_GetCubicFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GradientPerturb2D"))
	static void Blueprint_GradientPerturb2D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GradientPerturbFractal2D"))
	static void Blueprint_GradientPerturbFractal2D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, FVector2D& Coordinates);

	//3D
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetValue3D"))
	static float Blueprint_GetValue3D(int32 Seed, float Frequency, EInterpolation Interpolation, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetValueFractal3D"))
	static float Blueprint_GetValueFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetPerlin3D"))
	static float Blueprint_GetPerlin3D(int32 Seed, float Frequency, EInterpolation Interpolation, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetPerlinFractal3D"))
	static float Blueprint_GetPerlinFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplex3D"))
	static float Blueprint_GetSimplex3D(int32 Seed, float Frequency, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplexFractal3D"))
	static float Blueprint_GetSimplexFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoise3D"))
	static float Blueprint_GetWhiteNoise3D(int32 Seed, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoiseInt3D"))
	static float Blueprint_GetWhiteNoiseInt3D(int32 Seed, const FIntVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetCubic3D"))
	static float Blueprint_GetCubic3D(int32 Seed, float Frequency, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetCubicFractal3D"))
	static float Blueprint_GetCubicFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GradientPerturb3D"))
	static void Blueprint_GradientPerturb3D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, UPARAM(ref) FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GradientPerturbFractal3D"))
	static void Blueprint_GradientPerturbFractal3D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, UPARAM(ref) FVector& Coordinates);

	//4D
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplex4D"))
	static float Blueprint_GetSimplex4D(int32 Seed, float Frequency, const FVector4& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplexFractal4D"))
	static float Blueprint_GetSimplexFractal4D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, const FVector4& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoise4D"))
	static float Blueprint_GetWhiteNoise4D(int32 Seed, const FVector4& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoiseInt4D"))
	static float Blueprint_GetWhiteNoiseInt4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W);

private:
	//2D
	static float SingleValueFractalFbm2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y);
	static float SingleValueFractalBillow2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y);
	static float SingleValueFractalRigidMulti2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y);
	static float SingleValue2D(int32 Seed, EInterpolation Interpolation, float X, float Y);
	static float SinglePerlinFractalFbm2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y);
	static float SinglePerlinFractalBillow2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y);
	static float SinglePerlinFractalRigidMulti2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y);
	static float SinglePerlin2D(int32 Seed, EInterpolation Interpolation, float X, float Y);
	static float SingleSimplexFractalFbm2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y);
	static float SingleSimplexFractalBillow2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y);
	static float SingleSimplexFractalRigidMulti2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y);
	static float SingleSimplex2D(int32 Seed, float X, float Y);
	static float SingleCubicFractalFbm2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y);
	static float SingleCubicFractalBillow2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y);
	static float SingleCubicFractalRigidMulti2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y);
	static float SingleCubic2D(int32 Seed, float X, float Y);
	static void SingleGradientPerturb2D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, float& X, float& Y);
	static float SeededCoordinateValue2D(int32 Seed, int32 X, int32 Y);
	static float GradientCoordinateValue2D(int32 Seed, int32 X, int32 Y, float Xd, float Yd);
	
	//3D
	static float SingleValueFractalFbm3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z);
	static float SingleValueFractalBillow3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z);
	static float SingleValueFractalRigidMulti3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z);
	static float SingleValue3D(int32 Seed, EInterpolation Interpolation, float X, float Y, float Z);
	static float SinglePerlinFractalFbm3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z);
	static float SinglePerlinFractalBillow3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z);
	static float SinglePerlinFractalRigidMulti3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z);
	static float SinglePerlin3D(int32 Seed, EInterpolation Interpolation, float X, float Y, float Z);
	static float SingleSimplexFractalFbm3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z);
	static float SingleSimplexFractalBillow3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z);
	static float SingleSimplexFractalRigidMulti3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z);
	static float SingleSimplex3D(int32 Seed, float X, float Y, float Z);
	static float SingleCubicFractalFbm3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z);
	static float SingleCubicFractalBillow3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z);
	static float SingleCubicFractalRigidMulti3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z);
	static float SingleCubic3D(int32 Seed, float X, float Y, float Z);
	static void SingleGradientPerturb3D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, float& X, float& Y, float& Z);
	static float SeededCoordinateValue3D(int32 Seed, int32 X, int32 Y, int32 Z);
	static float GradientCoordinateValue3D(int32 Seed, int32 X, int32 Y, int32 Z, float Xd, float Yd, float Zd);

	//4D
	static float SingleSimplexFractalFbm4D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z, float W);
	static float SingleSimplexFractalBillow4D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z, float W);
	static float SingleSimplexFractalRigidMulti4D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z, float W);
	static float SingleSimplex4D(int32 Seed, float X, float Y, float Z, float W);
	static float SeededCoordinateValue4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W);
	static float GradientCoordinateValue4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W, float Xd, float Yd, float Zd, float Wd);
	
	static int32 Hash2D(int32 Seed, const int32& X, const int32& Y);
	static int32 Hash3D(int32 Seed, const int32& X, const int32& Y, const int32& Z);
	static int32 Hash4D(int32 Seed, const int32& X, const int32& Y, const int32& Z, const int32& W);

	static float CalculateFractalBounding(int32 Octaves, float Gain);

	
};
