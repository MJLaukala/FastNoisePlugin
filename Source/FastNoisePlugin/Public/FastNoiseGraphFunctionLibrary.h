// Copyright 2021 Matthew Laukala

#pragma once

#include "CoreMinimal.h"

#include <functional>

#include "FastNoiseFunctionLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FastNoiseGraphFunctionLibrary.generated.h"


typedef std::function<float(float X, float Y)> F2DOperationLambda; 

USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DefaultValue;
	
	F2DOperationLambda OperationMathLambda;

	GENERATED_BODY()

		FNoiseOperation2D();
	FNoiseOperation2D(float InDefaultValue);
	
	virtual ~FNoiseOperation2D() = default;

	float GetValue(float X, float Y) const;
	float GetValue(const FVector2D& Vector2D) const;
};


USTRUCT(BlueprintType)
struct FASTNOISEPLUGIN_API FValue2DOperation : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FNoiseOperation2D Frequency;

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
struct FASTNOISEPLUGIN_API FValueFractal2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Gain;

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
struct FASTNOISEPLUGIN_API FPerlin2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Lacunarity;

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
struct FASTNOISEPLUGIN_API FPerlinFractal2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Gain;

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
struct FASTNOISEPLUGIN_API FSimplex2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Frequency;

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
struct FASTNOISEPLUGIN_API FSimplexFractal2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Gain;

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
struct FASTNOISEPLUGIN_API FWhiteNoise2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

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
struct FASTNOISEPLUGIN_API FWhiteNoiseInt2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

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
struct FASTNOISEPLUGIN_API FCubic2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Frequency;

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
struct FASTNOISEPLUGIN_API FCubicFractal2D : public FNoiseOperation2D
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Amplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Frequency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Lacunarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FNoiseOperation2D Gain;

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
class FASTNOISEPLUGIN_API UFastNoiseGraphFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintPure, meta=(DisplayName = "FValue2DOperation To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FValue2DOperationToFNoiseOperation2D(const FValue2DOperation& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FValueFractal2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FValueFractal2DToFValueOperation2D(const FValueFractal2D& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FPerlin2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FPerlin2DToFValueOperation2D(const FPerlin2D& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FPerlinFractal2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FPerlinFractal2DToFValueOperation2D(const FPerlinFractal2D& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FSimplex2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FSimplex2DToFValueOperation2D(const FSimplex2D& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FSimplexFractal2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FSimplexFractal2DToFValueOperation2D(const FSimplexFractal2D& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FWhiteNoise2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FWhiteNoise2DToFValueOperation2D(const FWhiteNoise2D& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FWhiteNoiseInt2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FWhiteNoiseInt2DToFValueOperation2D(const FWhiteNoiseInt2D& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FCubic2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FCubic2DToFValueOperation2D(const FCubic2D& Value) { return Value; }

	UFUNCTION(BlueprintPure, meta = (DisplayName = "FCubicFractal2D To FNoiseOperation2D", CompactNodeTitle = "->", ScriptMethod = "FNoiseOperation2D", BlueprintAutoCast), Category = "FastNoise")
		static FNoiseOperation2D Conv_FCubicFractal2DToFValueOperation2D(const FCubicFractal2D& Value) { return Value; }
		
#undef CONVERSION
	
	// MATHS
	UFUNCTION(BlueprintPure, meta = (DisplayName = "FNoiseOperation2D + FNoiseOperation2D", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FNoiseOperation2D Add_FNoiseOperation2DFNoiseOperation2D(const FNoiseOperation2D& A, const FNoiseOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FNoiseOperation2D - FNoiseOperation2D", CompactNodeTitle = "-", Keywords = "- subtract minus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FNoiseOperation2D Subtract_FNoiseOperation2DFNoiseOperation2D(const FNoiseOperation2D& A, const FNoiseOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FNoiseOperation2D * FNoiseOperation2D", CompactNodeTitle = "*", Keywords = "* multiply times", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FNoiseOperation2D Multiply_FNoiseOperation2DFNoiseOperation2D(const FNoiseOperation2D& A, const FNoiseOperation2D& B);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "FNoiseOperation2D / FNoiseOperation2D", CompactNodeTitle = "/", Keywords = "/ divide divided", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|FastNoise")
	static FNoiseOperation2D Divide_FNoiseOperation2DFNoiseOperation2D(const FNoiseOperation2D& A, const FNoiseOperation2D& B);

	UFUNCTION(BlueprintPure, Category = "FastNoise", meta = (DisplayName = "GetValue"))
	static float CalculateNoiseOperation2D(const FNoiseOperation2D& ValueOperation2D, float X, float Y);

};
