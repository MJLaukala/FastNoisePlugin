// Copyright 2021 Matthew Laukala

#pragma once

#include "CoreMinimal.h"

#include "FastNoiseFunctionLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FastNoiseGraphFunctionLibrary.generated.h"


//typedef std::function<double(double X, double Y)> F2DOperationLambda;
typedef TDelegate<double(double X, double Y)> F2DOperationDelegate;

USTRUCT(BlueprintType, meta=(HasNativeMake="FastNoisePlugin.FastNoiseGraphFunctionLibrary.MakeLambdaOperation2D"))
struct FASTNOISEPLUGIN_API FLambdaOperation2D
{
	GENERATED_BODY()

	FLambdaOperation2D();
	// ReSharper disable once CppNonExplicitConvertingConstructor
	FLambdaOperation2D(double DefaultValue);

	virtual ~FLambdaOperation2D() = default;

	double GetValue(double X, double Y) const;
	double GetValue(const FVector2D& Vector2D) const;

	template<typename FunctorType, typename... VarTypes>
	void BindLambda(FunctorType&& InFunctor, VarTypes... Vars)
	{
		OperationDelegate.BindLambda(InFunctor, Vars...);
	}

private:
	F2DOperationDelegate OperationDelegate;
};

/**
 * 
 */
UCLASS()
class FASTNOISEPLUGIN_API UFastNoiseGraphFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (Keywords = "construct build", NativeMakeFunc), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D MakeLambdaOperation2D(double Value);
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetSin2D", Keywords="Sin 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetSin2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			const auto F = Frequency.GetValue(X, Y);
			const auto A = Amplitude.GetValue(X, Y);
			return (FMath::Sin(X * F) + FMath::Sin(Y * F)) / 2.0 * A;
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetValue2D", Keywords="Value 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetValue2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, const int32 Seed = 1337, const EInterpolation Interpolation = EInterpolation::Linear)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetValue2D(Seed, Frequency.GetValue(X, Y), Interpolation, X, Y);
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetValueFractal2D", Keywords="Value Fractal 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetValueFractal2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, FLambdaOperation2D Gain, const int32 Seed = 1337, const int32 Octaves = 1, const EInterpolation Interpolation = EInterpolation::Linear, const EFractalType FractalType = EFractalType::FBM)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetValueFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, Interpolation, FractalType, X, Y);
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetPerlin2D", Keywords="Perlin 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetPerlin2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, const int32 Seed = 1337, const EInterpolation Interpolation = EInterpolation::Linear)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetPerlin2D(Seed, Frequency.GetValue(X, Y), Interpolation, X, Y);
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetPerlinFractal2D", Keywords="Perlin Fractal 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetPerlinFractal2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, FLambdaOperation2D Gain, const int32 Seed = 1337, const int32 Octaves = 1, const EInterpolation Interpolation = EInterpolation::Linear, const EFractalType FractalType = EFractalType::FBM)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetPerlinFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, Interpolation, FractalType, X, Y);
		});
		return Operation;
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="GetSimplex2D", Keywords="Simplex 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetSimplex2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, const int32 Seed = 1337)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetSimplex2D(Seed, Frequency.GetValue(X, Y), X, Y);
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetSimplexFractal2D", Keywords="Simplex Fractal 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetSimplexFractal2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, FLambdaOperation2D Gain, const int32 Seed = 1337, const int32 Octaves = 1, const EFractalType FractalType = EFractalType::FBM)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetSimplexFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, FractalType, X, Y);
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetWhiteNoise2D", Keywords="White Noise 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetWhiteNoise2D(FLambdaOperation2D Amplitude, const int32 Seed = 1337)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetWhiteNoise2D(Seed, X, Y);
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetWhiteNoiseInt2D", Keywords="White Noise Int 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetWhiteNoiseInt2D(FLambdaOperation2D Amplitude, const int32 Seed = 1337)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetWhiteNoiseInt2D(Seed, X, Y);
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetCubic2D", Keywords="Cubic 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetCubic2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, const int32 Seed = 1337)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetCubic2D(Seed, Frequency.GetValue(X, Y), X, Y);
		});
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetCubicFractal2D", Keywords="Cubic Fractal 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetCubicFractal2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, FLambdaOperation2D Gain, const int32 Seed = 1337, const int32 Octaves = 1, const EFractalType FractalType = EFractalType::FBM)
	{
		FLambdaOperation2D Operation;
		Operation.BindLambda([=](const double X, const double Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetCubicFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, FractalType, X, Y);
		});
		return Operation;
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName = "double To FLambdaOperation2D", CompactNodeTitle = "->", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FloatToFLambdaOperation2D(const double& Value) { return FLambdaOperation2D(Value); }

	// MATHS
	UFUNCTION(BlueprintPure, meta=(DisplayName = "To Scalar", CompactNodeTitle = "To Scalar", Keywords = "Scalar"), Category = "Math|FastNoise")
	static FLambdaOperation2D ToScalar_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Sin", CompactNodeTitle = "Sin", Keywords = "Sin"), Category = "Math|FastNoise")
	static FLambdaOperation2D Sin_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Asin", CompactNodeTitle = "Asin", Keywords = "Asin"), Category = "Math|FastNoise")
	static FLambdaOperation2D Asin_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Sinh", CompactNodeTitle = "Sinh", Keywords = "Sinh"), Category = "Math|FastNoise")
	static FLambdaOperation2D Sinh_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Cos", CompactNodeTitle = "Cos", Keywords = "Cos"), Category = "Math|FastNoise")
	static FLambdaOperation2D Cos_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Acos", CompactNodeTitle = "Acos", Keywords = "Acos"), Category = "Math|FastNoise")
	static FLambdaOperation2D Acos_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Tan", CompactNodeTitle = "Tan", Keywords = "Tan"), Category = "Math|FastNoise")
	static FLambdaOperation2D Tan_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Atan", CompactNodeTitle = "Atan", Keywords = "Atan"), Category = "Math|FastNoise")
	static FLambdaOperation2D Atan_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Atan2", CompactNodeTitle = "Atan2", Keywords = "Atan2"), Category = "Math|FastNoise")
	static FLambdaOperation2D Atan2_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "SquareRoot", CompactNodeTitle = "SquareRoot", Keywords = "SquareRoot"), Category = "Math|FastNoise")
	static FLambdaOperation2D SquareRoot_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "InverseSquareRoot", CompactNodeTitle = "InverseSquareRoot", Keywords = "InverseSquareRoot"), Category = "Math|FastNoise")
	static FLambdaOperation2D InverseSquareRoot_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName="Power", Keywords="^ power"), Category="Math|FastNoise")
	static FLambdaOperation2D MultiplyMultiply_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D Base, FLambdaOperation2D Exponent);

	UFUNCTION(BlueprintPure, meta=(DisplayName="Floor", CompactNodeTitle="Floor", Keywords="Floor"), Category="Math|FastNoise")
	static FLambdaOperation2D Floor_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="Modulus", CompactNodeTitle="%", Keywords="% modulus"), Category="Math|FastNoise")
	static FLambdaOperation2D Percent_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName="Fraction", CompactNodeTitle="F", Keywords="Fraction"), Category="Math|FastNoise")
	static FLambdaOperation2D Fraction_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D);
	
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Plus", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FLambdaOperation2D Add_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Minus", CompactNodeTitle = "-", Keywords = "- subtract minus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FLambdaOperation2D Subtract_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Multiply", CompactNodeTitle = "*", Keywords = "* multiply times", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FLambdaOperation2D Multiply_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Divide", CompactNodeTitle = "/", Keywords = "/ divide divided"), Category = "Math|FastNoise")
	static FLambdaOperation2D Divide_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Safe Divide", CompactNodeTitle = "÷(Safe)", Keywords = "safe / divide divided"), Category = "Math|FastNoise")
	static FLambdaOperation2D SafeDivide_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Less Than", Keywords = "< less"), Category = "Math|FastNoise")
	static FLambdaOperation2D Less_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Less Than Equal To", Keywords = "<= less"), Category = "Math|FastNoise")
	static FLambdaOperation2D LessEqual_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Greater Than", Keywords = "> greater"), Category = "Math|FastNoise")
	static FLambdaOperation2D Greater_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Greater Than Equal To", Keywords = ">= Greater"), Category = "Math|FastNoise")
	static FLambdaOperation2D GreaterEqual_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal To", Keywords = "== equal"), Category = "Math|FastNoise")
	static FLambdaOperation2D EqualEqual_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Not Equal To", Keywords = "!= not equal"), Category = "Math|FastNoise")
	static FLambdaOperation2D NotEqual_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "In Range", Keywords = "in range"), Category = "Math|FastNoise")
	static FLambdaOperation2D InRange_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D In, FLambdaOperation2D Min, FLambdaOperation2D Max, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Min", CompactNodeTitle = "Min", CommutativeAssociativeBinaryOperator = "true", Keywords = "Min"), Category = "Math|FastNoise")
	static FLambdaOperation2D Min_FLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Max", CompactNodeTitle = "Max", CommutativeAssociativeBinaryOperator = "true", Keywords = "Max"), Category = "Math|FastNoise")
	static FLambdaOperation2D Max_FLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Clamp", Keywords = "Clamp"), Category = "Math|FastNoise")
	static FLambdaOperation2D Clamp_FLambdaOperation2D(FLambdaOperation2D Value, FLambdaOperation2D Min, FLambdaOperation2D Max);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Wrap", Keywords = "Wrap"), Category = "Math|FastNoise")
	static FLambdaOperation2D Wrap_FLambdaOperation2D(FLambdaOperation2D Value, FLambdaOperation2D Min, FLambdaOperation2D Max);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Lerp", Keywords = "Lerp"), Category = "Math|FastNoise")
	static FLambdaOperation2D Lerp_FLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D Alpha);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Normalize To Range", Keywords = "Normalize Range"), Category = "Math|FastNoise")
	static FLambdaOperation2D NormalizeToRange_FLambdaOperation2D(FLambdaOperation2D Value, FLambdaOperation2D RangeMin, FLambdaOperation2D RangeMax);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "PingPong", Keywords = "Ping Pong"), Category = "Math|FastNoise")
	static FLambdaOperation2D PingPong_FLambdaOperation2D(FLambdaOperation2D Value, FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency);
	
	UFUNCTION(BlueprintPure, meta=(DisplayName = "ApplyCurve", Keywords = "Apply Curve"), Category = "Math|FastNoise")
	static FLambdaOperation2D ApplyCurve_FLambdaOperation2D(FLambdaOperation2D Value, UCurveFloat* Curve);

	UFUNCTION(BlueprintPure, Category = "FastNoise", meta = (DisplayName = "GetValue"))
	static double CalculateNoiseOperation2D(FLambdaOperation2D ValueOperation2D, double X, double Y);
};
