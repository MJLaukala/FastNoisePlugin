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

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FStaticValue2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;
	
	GENERATED_BODY()

	FStaticValue2D();
	// ReSharper disable once CppNonExplicitConvertingConstructor
	FStaticValue2D(float InDefaultValue);
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FValue2DOperation : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInterpolation Interpolation;

	GENERATED_BODY()

	FValue2DOperation() : Seed(0), Amplitude(1), Frequency(0), Interpolation(EInterpolation::Linear)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetValue2D(Seed, Frequency.GetValue(X, Y), Interpolation, X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FValueFractal2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Gain;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Octaves;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInterpolation Interpolation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EFractalType FractalType;

	GENERATED_BODY()

	FValueFractal2D() : Seed(0), Amplitude(1), Octaves(0), Interpolation(EInterpolation::Linear), FractalType(EFractalType::Billow)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetValueFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, Interpolation, FractalType, X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FPerlin2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInterpolation Interpolation;

	GENERATED_BODY()

	FPerlin2D() : Seed(0), Amplitude(1), Interpolation(EInterpolation::Linear)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetPerlin2D(Seed, Frequency.GetValue(X, Y), Interpolation, X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FPerlinFractal2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Gain;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Octaves;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EInterpolation Interpolation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EFractalType FractalType;

	GENERATED_BODY()

	FPerlinFractal2D() : Seed(0), Amplitude(1), Octaves(0), Interpolation(EInterpolation::Linear), FractalType(EFractalType::Billow)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetPerlinFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, Interpolation, FractalType, X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FSimplex2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Frequency;

	GENERATED_BODY()

	FSimplex2D() : Seed(0), Amplitude(1)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetSimplex2D(Seed, Frequency.GetValue(X, Y), X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FSimplexFractal2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Gain;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Octaves;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EFractalType FractalType;

	GENERATED_BODY()

	FSimplexFractal2D() : Seed(0), Amplitude(1), Octaves(0), FractalType(EFractalType::Billow)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetSimplexFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, FractalType, X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FWhiteNoise2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	GENERATED_BODY()

	FWhiteNoise2D() : Seed(0), Amplitude(1)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetWhiteNoise2D(Seed, X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FWhiteNoiseInt2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	GENERATED_BODY()

	FWhiteNoiseInt2D() : Seed(0), Amplitude(1)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetWhiteNoiseInt2D(Seed, X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FCubic2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Frequency;

	GENERATED_BODY()

	FCubic2D() : Seed(0), Amplitude(1)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetCubic2D(Seed, Frequency.GetValue(X, Y), X, Y);
		};
	}
};

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FCubicFractal2D : public FLambdaOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLambdaOperation2D Gain;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Octaves;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EFractalType FractalType;

	GENERATED_BODY()

	FCubicFractal2D() : Seed(0), Amplitude(1), Octaves(0), FractalType(EFractalType::Billow)
	{
		OperationMathLambda = [=](const float X, const float Y)
		{
			return Amplitude.GetValue(X, Y) * UFastNoiseFunctionLibrary::GetCubicFractal2D(Seed, Frequency.GetValue(X, Y), Lacunarity.GetValue(X, Y), Gain.GetValue(X, Y), Octaves, FractalType, X, Y);
		};
	}
};

/**
 * 
 */
UCLASS()
class FASTNOISEPLUGIN_API UFastNoiseGraphFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta=(DisplayName = "float To FLambdaOperation2D", CompactNodeTitle = "->", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FloatToFLambdaOperation2D(const float& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FStaticValue2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FStaticValue2DToFLambdaOperation2D(const FStaticValue2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FValue2DOperation To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FValue2DOperationToFLambdaOperation2D(const FValue2DOperation& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FValueFractal2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FValueFractal2DToFValueOperation2D(const FValueFractal2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FPerlin2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FPerlin2DToFValueOperation2D(const FPerlin2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FPerlinFractal2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FPerlinFractal2DToFValueOperation2D(const FPerlinFractal2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FSimplex2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FSimplex2DToFValueOperation2D(const FSimplex2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FSimplexFractal2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FSimplexFractal2DToFValueOperation2D(const FSimplexFractal2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FWhiteNoise2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FWhiteNoise2DToFValueOperation2D(const FWhiteNoise2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FWhiteNoiseInt2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FWhiteNoiseInt2DToFValueOperation2D(const FWhiteNoiseInt2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FCubic2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FCubic2DToFValueOperation2D(const FCubic2D& Value) { return FLambdaOperation2D(Value); }

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FCubicFractal2D To FLambdaOperation2D", CompactNodeTitle = "->", ScriptMethod = "FLambdaOperation2D", BlueprintAutoCast), Category = "FastNoise")
	static FLambdaOperation2D Conv_FCubicFractal2DToFValueOperation2D(const FCubicFractal2D& Value) { return static_cast<FLambdaOperation2D>(Value); }

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
