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

UCLASS() 
class FASTNOISEPLUGIN_API UFastNoiseFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//2D
	static double GetValue2D(int32 Seed, double Frequency, EInterpolation Interpolation, double X, double Y);
	static double GetValueFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, double X, double Y);
	static double GetPerlin2D(int32 Seed, double Frequency, EInterpolation Interpolation, double X, double Y);
	static double GetPerlinFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, double X, double Y);
	static double GetSimplex2D(int32 Seed, double Frequency, double X, double Y);
	static double GetSimplexFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, double X, double Y);
	static double GetWhiteNoise2D(int32 Seed, double X, double Y);
	static double GetWhiteNoiseInt2D(int32 Seed, int32 X, int32 Y);
	static double GetCubic2D(int32 Seed, double Frequency, double X, double Y);
	static double GetCubicFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, double X, double Y);
	static void GradientPerturb2D(int32 Seed, double Perturb, double Frequency, EInterpolation Interpolation, double& X, double& Y);
	static void GradientPerturbFractal2D(int32 Seed, double Perturb, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double& X, double& Y);

	//3D
	static double GetValue3D(int32 Seed, double Frequency, EInterpolation Interpolation, double X, double Y, double Z);
	static double GetValueFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, double X, double Y, double Z);
	static double GetPerlin3D(int32 Seed, double Frequency, EInterpolation Interpolation, double X, double Y, double Z);
	static double GetPerlinFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, double X, double Y, double Z);
	static double GetSimplex3D(int32 Seed, double Frequency, double X, double Y, double Z);
	static double GetSimplexFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, double X, double Y, double Z);
	static double GetWhiteNoise3D(int32 Seed, double X, double Y, double Z);
	static double GetWhiteNoiseInt3D(int32 Seed, int32 X, int32 Y, int32 Z);
	static double GetCubic3D(int32 Seed, double Frequency, double X, double Y, double Z);
	static double GetCubicFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, double X, double Y, double Z);
	static void GradientPerturb3D(int32 Seed, double Perturb, double Frequency, EInterpolation Interpolation, double& X, double& Y, double& Z);
	static void GradientPerturbFractal3D(int32 Seed, double Perturb, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double& X, double& Y, double& Z);

	//4D
	static double GetSimplex4D(int32 Seed, double Frequency, double X, double Y, double Z, double W);
	static double GetSimplexFractal4D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, double X, double Y, double Z, double W);
	static double GetWhiteNoise4D(int32 Seed, double X, double Y, double Z, double W);
	static double GetWhiteNoiseInt4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W);

	// Simplified wrappers
	//2D
	static double GetValue2D(int32 Seed, double Frequency, EInterpolation Interpolation, const FVector2D& Coordinates);
	static double GetValueFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector2D& Coordinates);
	static double GetPerlin2D(int32 Seed, double Frequency, EInterpolation Interpolation, const FVector2D& Coordinates);
	static double GetPerlinFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector2D& Coordinates);
	static double GetSimplex2D(int32 Seed, double Frequency, const FVector2D& Coordinates);
	static double GetSimplexFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector2D& Coordinates);
	static double GetWhiteNoise2D(int32 Seed, const FVector2D& Coordinates);
	static double GetWhiteNoiseInt2D(int32 Seed, const FIntPoint& Coordinates);
	static double GetCubic2D(int32 Seed, double Frequency, const FVector2D& Coordinates);
	static double GetCubicFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector2D& Coordinates);
	static void GradientPerturb2D(int32 Seed, double Perturb, double Frequency, EInterpolation Interpolation, FVector2D& Coordinates);
	static void GradientPerturbFractal2D(int32 Seed, double Perturb, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, FVector2D& Coordinates);

	//3D
	static double GetValue3D(int32 Seed, double Frequency, EInterpolation Interpolation, const FVector& Coordinates);
	static double GetValueFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector& Coordinates);
	static double GetPerlin3D(int32 Seed, double Frequency, EInterpolation Interpolation, const FVector& Coordinates);
	static double GetPerlinFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector& Coordinates);
	static double GetSimplex3D(int32 Seed, double Frequency, const FVector& Coordinates);
	static double GetSimplexFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector& Coordinates);
	static double GetWhiteNoise3D(int32 Seed, const FVector& Coordinates);
	static double GetWhiteNoiseInt3D(int32 Seed, const FIntVector& Coordinates);
	static double GetCubic3D(int32 Seed, double Frequency, const FVector& Coordinates);
	static double GetCubicFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector& Coordinates);
	static void GradientPerturb3D(int32 Seed, double Perturb, double Frequency, EInterpolation Interpolation, FVector& Coordinates);
	static void GradientPerturbFractal3D(int32 Seed, double Perturb, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, FVector& Coordinates);

	//4D
	static double GetSimplex4D(int32 Seed, double Frequency, const FVector4& Coordinates);
	static double GetSimplexFractal4D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector4& Coordinates);
	static double GetWhiteNoise4D(int32 Seed, const FVector4& Coordinates);
	static double GetWhiteNoiseInt4D(int32 Seed, const FIntVector4& Coordinates);

	// Blueprint wrappers
	//2D
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetValue2D"))
	static double Blueprint_GetValue2D(int32 Seed, double Frequency, EInterpolation Interpolation, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetValueFractal2D"))
	static double Blueprint_GetValueFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetPerlin2D"))
	static double Blueprint_GetPerlin2D(int32 Seed, double Frequency, EInterpolation Interpolation, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetPerlinFractal2D"))
	static double Blueprint_GetPerlinFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplex2D"))
	static double Blueprint_GetSimplex2D(int32 Seed, double Frequency, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplexFractal2D"))
	static double Blueprint_GetSimplexFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoise2D"))
	static double Blueprint_GetWhiteNoise2D(int32 Seed, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoiseInt2D"))
	static double Blueprint_GetWhiteNoiseInt2D(int32 Seed, const FIntPoint& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetCubic2D"))
	static double Blueprint_GetCubic2D(int32 Seed, double Frequency, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetCubicFractal2D"))
	static double Blueprint_GetCubicFractal2D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GradientPerturb2D"))
	static void Blueprint_GradientPerturb2D(int32 Seed, double Perturb, double Frequency, EInterpolation Interpolation, FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GradientPerturbFractal2D"))
	static void Blueprint_GradientPerturbFractal2D(int32 Seed, double Perturb, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, FVector2D& Coordinates);

	//3D
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetValue3D"))
	static double Blueprint_GetValue3D(int32 Seed, double Frequency, EInterpolation Interpolation, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetValueFractal3D"))
	static double Blueprint_GetValueFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetPerlin3D"))
	static double Blueprint_GetPerlin3D(int32 Seed, double Frequency, EInterpolation Interpolation, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetPerlinFractal3D"))
	static double Blueprint_GetPerlinFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplex3D"))
	static double Blueprint_GetSimplex3D(int32 Seed, double Frequency, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplexFractal3D"))
	static double Blueprint_GetSimplexFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoise3D"))
	static double Blueprint_GetWhiteNoise3D(int32 Seed, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoiseInt3D"))
	static double Blueprint_GetWhiteNoiseInt3D(int32 Seed, const FIntVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetCubic3D"))
	static double Blueprint_GetCubic3D(int32 Seed, double Frequency, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetCubicFractal3D"))
	static double Blueprint_GetCubicFractal3D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GradientPerturb3D"))
	static void Blueprint_GradientPerturb3D(int32 Seed, double Perturb, double Frequency, EInterpolation Interpolation, UPARAM(ref) FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GradientPerturbFractal3D"))
	static void Blueprint_GradientPerturbFractal3D(int32 Seed, double Perturb, double Frequency, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, UPARAM(ref) FVector& Coordinates);

	//4D
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplex4D"))
	static double Blueprint_GetSimplex4D(int32 Seed, double Frequency, const FVector4& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetSimplexFractal4D"))
	static double Blueprint_GetSimplexFractal4D(int32 Seed, double Frequency, double Lacunarity, double Gain, int32 Octaves, EFractalType FractalType, const FVector4& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoise4D"))
	static double Blueprint_GetWhiteNoise4D(int32 Seed, const FVector4& Coordinates);
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta=(DisplayName="GetWhiteNoiseInt4D"))
	static double Blueprint_GetWhiteNoiseInt4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W);

private:
	//2D
	static double SingleValueFractalFbm2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y);
	static double SingleValueFractalBillow2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y);
	static double SingleValueFractalRigidMulti2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y);
	static double SingleValue2D(int32 Seed, EInterpolation Interpolation, double X, double Y);
	static double SinglePerlinFractalFbm2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y);
	static double SinglePerlinFractalBillow2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y);
	static double SinglePerlinFractalRigidMulti2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y);
	static double SinglePerlin2D(int32 Seed, EInterpolation Interpolation, double X, double Y);
	static double SingleSimplexFractalFbm2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y);
	static double SingleSimplexFractalBillow2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y);
	static double SingleSimplexFractalRigidMulti2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y);
	static double SingleSimplex2D(int32 Seed, double X, double Y);
	static double SingleCubicFractalFbm2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y);
	static double SingleCubicFractalBillow2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y);
	static double SingleCubicFractalRigidMulti2D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y);
	static double SingleCubic2D(int32 Seed, double X, double Y);
	static void SingleGradientPerturb2D(int32 Seed, double Perturb, double Frequency, EInterpolation Interpolation, double& X, double& Y);
	static double SeededCoordinateValue2D(int32 Seed, int32 X, int32 Y);
	static double GradientCoordinateValue2D(int32 Seed, int32 X, int32 Y, double Xd, double Yd);
	
	//3D
	static double SingleValueFractalFbm3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y, double Z);
	static double SingleValueFractalBillow3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y, double Z);
	static double SingleValueFractalRigidMulti3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y, double Z);
	static double SingleValue3D(int32 Seed, EInterpolation Interpolation, double X, double Y, double Z);
	static double SinglePerlinFractalFbm3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y, double Z);
	static double SinglePerlinFractalBillow3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y, double Z);
	static double SinglePerlinFractalRigidMulti3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, EInterpolation Interpolation, double X, double Y, double Z);
	static double SinglePerlin3D(int32 Seed, EInterpolation Interpolation, double X, double Y, double Z);
	static double SingleSimplexFractalFbm3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z);
	static double SingleSimplexFractalBillow3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z);
	static double SingleSimplexFractalRigidMulti3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z);
	static double SingleSimplex3D(int32 Seed, double X, double Y, double Z);
	static double SingleCubicFractalFbm3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z);
	static double SingleCubicFractalBillow3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z);
	static double SingleCubicFractalRigidMulti3D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z);
	static double SingleCubic3D(int32 Seed, double X, double Y, double Z);
	static void SingleGradientPerturb3D(int32 Seed, double Perturb, double Frequency, EInterpolation Interpolation, double& X, double& Y, double& Z);
	static double SeededCoordinateValue3D(int32 Seed, int32 X, int32 Y, int32 Z);
	static double GradientCoordinateValue3D(int32 Seed, int32 X, int32 Y, int32 Z, double Xd, double Yd, double Zd);

	//4D
	static double SingleSimplexFractalFbm4D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z, double W);
	static double SingleSimplexFractalBillow4D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z, double W);
	static double SingleSimplexFractalRigidMulti4D(int32 Seed, double Lacunarity, double Gain, int32 Octaves, double X, double Y, double Z, double W);
	static double SingleSimplex4D(int32 Seed, double X, double Y, double Z, double W);
	static double SeededCoordinateValue4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W);
	static double GradientCoordinateValue4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W, double Xd, double Yd, double Zd, double Wd);
	
	static int32 Hash2D(int32 Seed, const int32& X, const int32& Y);
	static int32 Hash3D(int32 Seed, const int32& X, const int32& Y, const int32& Z);
	static int32 Hash4D(int32 Seed, const int32& X, const int32& Y, const int32& Z, const int32& W);

	static double CalculateFractalBounding(int32 Octaves, double Gain);

	
};
