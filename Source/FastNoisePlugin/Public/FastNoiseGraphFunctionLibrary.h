// Copyright 2021 Matthew Laukala

#pragma once

#include "CoreMinimal.h"

#include <functional>

#include "FastNoiseFunctionLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FastNoiseGraphFunctionLibrary.generated.h"


typedef std::function<float(float X, float Y)> F2DOperationLambda;

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FLambdaOperation2D
{
	F2DOperationLambda OperationMathLambda;

	GENERATED_BODY()

	FLambdaOperation2D();
	// ReSharper disable once CppNonExplicitConvertingConstructor
	FLambdaOperation2D(float Value);

	virtual ~FLambdaOperation2D() = default;

	float GetValue(float X, float Y) const;
	float GetValue(const FVector2D& Vector2D) const;
};

/**
 * 
 */
UCLASS()
class FASTNOISEPLUGIN_API UFastNoiseGraphFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/*UFUNCTION(BlueprintPure, CustomThunk, meta=(DisplayName="GetValue2D", Keywords="Value 2D", CustomStructureParam = "Amplitude"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetValue2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, const int32 Seed = 1337, const EInterpolation Interpolation = EInterpolation::Linear)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetValue2D(Seed, Frequency.GetValue(X, Y), Interpolation, X, Y);
		};
		return Operation;
	}
	
	DECLARE_FUNCTION(execBlueprintGraphFunction_GetValue2D)
	{
		//P_GET_STRUCT(FLambdaOperation2D, Amplitude);
	
		FLambdaOperation2D Amplitude;
	
		Stack.MostRecentProperty = nullptr;
		Stack.Step(Stack.Object, nullptr);
		if (FStructProperty* StructProperty = ExactCastField<FStructProperty>(Stack.MostRecentProperty))
		{
			StructProperty->InitializeValue(&Amplitude);
		}
		else if(FFloatProperty* FloatProperty = ExactCastField<FFloatProperty>(Stack.MostRecentProperty))
		{
			float FloatAmplitude;
			FloatProperty->InitializeValue(&FloatAmplitude);
			Amplitude = FLambdaOperation2D(FloatAmplitude);
		}
		else
		{
			Stack.bArrayContextFailed = true;
			return;
		}
	
		P_GET_STRUCT(FLambdaOperation2D, Frequency);
		P_GET_PROPERTY(FIntProperty, Seed);
		P_GET_ENUM(EInterpolation, Interpolation);
	
		P_FINISH;
	
		*static_cast<FLambdaOperation2D*>(RESULT_PARAM) = BlueprintGraphFunction_GetValue2D(Amplitude, Frequency, Seed, Interpolation);
	}*/

	UFUNCTION(BlueprintPure, meta=(DisplayName="GetValue2D", Keywords="Value 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetValue2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, const int32 Seed = 1337, const EInterpolation Interpolation = EInterpolation::Linear)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetValue2D(Seed, Frequency.GetValue(X, Y), Interpolation, X, Y);
		};
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetValueFractal2D", Keywords="Value Fractal 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetValueFractal2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, FLambdaOperation2D Gain, const int32 Seed = 1337, const int32 Octaves = 1, const EInterpolation Interpolation = EInterpolation::Linear, const EFractalType FractalType = EFractalType::FBM)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetValueFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, Interpolation, FractalType, X, Y);
		};
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetPerlin2D", Keywords="Perlin 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetPerlin2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, const int32 Seed = 1337, const EInterpolation Interpolation = EInterpolation::Linear)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetPerlin2D(Seed, Frequency.GetValue(X, Y), Interpolation, X, Y);
		};
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetPerlinFractal2D", Keywords="Perlin Fractal 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetPerlinFractal2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, FLambdaOperation2D Gain, const int32 Seed = 1337, const int32 Octaves = 1, const EInterpolation Interpolation = EInterpolation::Linear, const EFractalType FractalType = EFractalType::FBM)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetPerlinFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, Interpolation, FractalType, X, Y);
		};
		return Operation;
	}

	UFUNCTION(BlueprintPure, meta=(DisplayName="GetSimplex2D", Keywords="Simplex 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetSimplex2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, const int32 Seed = 1337)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetSimplex2D(Seed, Frequency.GetValue(X, Y), X, Y);
		};
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetSimplexFractal2D", Keywords="Simplex Fractal 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetSimplexFractal2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, FLambdaOperation2D Gain, const int32 Seed = 1337, const int32 Octaves = 1, const EFractalType FractalType = EFractalType::FBM)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetSimplexFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, FractalType, X, Y);
		};
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetWhiteNoise2D", Keywords="White Noise 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetWhiteNoise2D(FLambdaOperation2D Amplitude, const int32 Seed = 1337)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetWhiteNoise2D(Seed, X, Y);
		};
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetWhiteNoiseInt2D", Keywords="White Noise Int 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetWhiteNoiseInt2D(FLambdaOperation2D Amplitude, const int32 Seed = 1337)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetWhiteNoiseInt2D(Seed, X, Y);
		};
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetCubic2D", Keywords="Cubic 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetCubic2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, const int32 Seed = 1337)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetCubic2D(Seed, Frequency.GetValue(X, Y), X, Y);
		};
		return Operation;
	}
	
	UFUNCTION(BlueprintPure, meta=(DisplayName="GetCubicFractal2D", Keywords="Cubic Fractal 2D"), Category="Math|FastNoise|GraphFunctions")
	static FLambdaOperation2D BlueprintGraphFunction_GetCubicFractal2D(FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency, FLambdaOperation2D Lacunarity, FLambdaOperation2D Gain, const int32 Seed = 1337, const int32 Octaves = 1, const EFractalType FractalType = EFractalType::FBM)
	{
		FLambdaOperation2D Operation;
		Operation.OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetCubicFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, FractalType, X, Y);
		};
		return Operation;
	}







	
	UFUNCTION(BlueprintPure, meta=(DisplayName = "float To FLambdaOperation2D", CompactNodeTitle = "->", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FloatToFLambdaOperation2D(const float& Value) { return FLambdaOperation2D(Value); }

	// MATHS
	UFUNCTION(BlueprintPure, meta=(DisplayName = "To Scalar", CompactNodeTitle = "To Scalar", Keywords = "Scalar"), Category = "Math|FastNoise")
	static FLambdaOperation2D ToScalar_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D);

	UFUNCTION(BlueprintPure, meta=(DisplayName="Power", Keywords="^ power"), Category="Math|FastNoise")
	static FLambdaOperation2D MultiplyMultiply_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& Base, const FLambdaOperation2D& Exponent);

	UFUNCTION(BlueprintPure, meta=(DisplayName="Modulus", CompactNodeTitle="%", Keywords="% modulus"), Category="Math|FastNoise")
	static FLambdaOperation2D Percent_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName="Fraction", CompactNodeTitle="F", Keywords="Fraction"), Category="Math|FastNoise")
	static FLambdaOperation2D Fraction_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D);
	
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Plus", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FLambdaOperation2D Add_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Minus", CompactNodeTitle = "-", Keywords = "- subtract minus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FLambdaOperation2D Subtract_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Multiply", CompactNodeTitle = "*", Keywords = "* multiply times", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FLambdaOperation2D Multiply_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Divide", CompactNodeTitle = "/", Keywords = "/ divide divided"), Category = "Math|FastNoise")
	static FLambdaOperation2D Divide_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Safe Divide", CompactNodeTitle = "÷(Safe)", Keywords = "safe / divide divided"), Category = "Math|FastNoise")
	static FLambdaOperation2D SafeDivide_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Less Than", Keywords = "< less"), Category = "Math|FastNoise")
	static FLambdaOperation2D Less_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Less Than Equal To", Keywords = "<= less"), Category = "Math|FastNoise")
	static FLambdaOperation2D LessEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Greater Than", Keywords = "> greater"), Category = "Math|FastNoise")
	static FLambdaOperation2D Greater_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Greater Than Equal To", Keywords = ">= Greater"), Category = "Math|FastNoise")
	static FLambdaOperation2D GreaterEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal To", Keywords = "== equal"), Category = "Math|FastNoise")
	static FLambdaOperation2D EqualEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Not Equal To", Keywords = "!= not equal"), Category = "Math|FastNoise")
	static FLambdaOperation2D NotEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "In Range", Keywords = "in range"), Category = "Math|FastNoise")
	static FLambdaOperation2D InRange_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& In, const FLambdaOperation2D& Min, const FLambdaOperation2D& Max, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Min", CompactNodeTitle = "Min", CommutativeAssociativeBinaryOperator = "true", Keywords = "Min"), Category = "Math|FastNoise")
	static FLambdaOperation2D Min_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Max", CompactNodeTitle = "Max", CommutativeAssociativeBinaryOperator = "true", Keywords = "Max"), Category = "Math|FastNoise")
	static FLambdaOperation2D Max_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Clamp", Keywords = "Clamp"), Category = "Math|FastNoise")
	static FLambdaOperation2D Clamp_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& Min, const FLambdaOperation2D& Max);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Wrap", Keywords = "Wrap"), Category = "Math|FastNoise")
	static FLambdaOperation2D Wrap_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& Min, const FLambdaOperation2D& Max);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Lerp", Keywords = "Lerp"), Category = "Math|FastNoise")
	static FLambdaOperation2D Lerp_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& Alpha);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Normalize To Range", Keywords = "Normalize Range"), Category = "Math|FastNoise")
	static FLambdaOperation2D NormalizeToRange_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& RangeMin, const FLambdaOperation2D& RangeMax);
	
	UFUNCTION(BlueprintPure, Category = "FastNoise", meta = (DisplayName = "GetValue"))
	static float CalculateNoiseOperation2D(const FLambdaOperation2D& ValueOperation2D, float X, float Y);
};
