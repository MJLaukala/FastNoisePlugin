// Copyright 2021 Matthew Laukala


#include "FastNoiseGraphFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

FLambdaOperation2D::FLambdaOperation2D()
{
	OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return 0.f;
	});
}

FLambdaOperation2D::FLambdaOperation2D(float DefaultValue)
{
	OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return DefaultValue;
	});
}

float FLambdaOperation2D::GetValue(const float X, const float Y) const
{
	if (OperationDelegate.IsBound())
	{
		return OperationDelegate.Execute(X, Y);
	}

	return 0.f;
}

float FLambdaOperation2D::GetValue(const FVector2D& Vector2D) const
{
	return GetValue(Vector2D.X, Vector2D.Y);
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::MakeLambdaOperation2D(float Value)
{
	return FLambdaOperation2D(Value);
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::ToScalar_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return (NoiseOperation2D.GetValue(X, Y) + 1.f) / 2.f;
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Sin_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Sin(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Asin_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Asin(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Sinh_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Sinh(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Cos_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Cos(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Acos_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Acos(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Tan_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Tan(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Atan_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Atan(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Atan2_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Atan2(A.GetValue(X, Y), B.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::SquareRoot_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Sqrt(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::InverseSquareRoot_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::InvSqrt(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::MultiplyMultiply_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D Base, FLambdaOperation2D Exponent)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Pow(Base.GetValue(X, Y), Exponent.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Floor_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Floor(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Percent_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		const float ValueB = B.GetValue(X, Y);
		return (ValueB != 0.f) ? FMath::Fmod(A.GetValue(X, Y), ValueB) : 0.f;
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Fraction_FLambdaOperation2D(FLambdaOperation2D NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Fractional(NoiseOperation2D.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Add_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) + B.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Subtract_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) - B.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Multiply_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) * B.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Divide_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) / B.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::SafeDivide_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return UKismetMathLibrary::SafeDivide(A.GetValue(X, Y), B.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Less_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) < B.GetValue(X, Y) ? TrueOperation.GetValue(X, Y) : FalseOperation.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::LessEqual_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) <= B.GetValue(X, Y) ? TrueOperation.GetValue(X, Y) : FalseOperation.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Greater_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) > B.GetValue(X, Y) ? TrueOperation.GetValue(X, Y) : FalseOperation.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::GreaterEqual_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) >= B.GetValue(X, Y) ? TrueOperation.GetValue(X, Y) : FalseOperation.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::EqualEqual_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) == B.GetValue(X, Y) ? TrueOperation.GetValue(X, Y) : FalseOperation.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::NotEqual_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return A.GetValue(X, Y) != B.GetValue(X, Y) ? TrueOperation.GetValue(X, Y) : FalseOperation.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::InRange_FLambdaOperation2DFLambdaOperation2D(FLambdaOperation2D In, FLambdaOperation2D Min, FLambdaOperation2D Max, FLambdaOperation2D TrueOperation, FLambdaOperation2D FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		const float InValue = In.GetValue(X, Y);
		return (InValue > Min.GetValue(X, Y) && InValue < Max.GetValue(X, Y)) ? TrueOperation.GetValue(X, Y) : FalseOperation.GetValue(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Min_FLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Min(A.GetValue(X, Y), B.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Max_FLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Max(A.GetValue(X, Y), B.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Clamp_FLambdaOperation2D(FLambdaOperation2D Value, FLambdaOperation2D Min, FLambdaOperation2D Max)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Clamp(Value.GetValue(X, Y), Min.GetValue(X, Y), Max.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Wrap_FLambdaOperation2D(FLambdaOperation2D Value, FLambdaOperation2D Min, FLambdaOperation2D Max)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Wrap(Value.GetValue(X, Y), Min.GetValue(X, Y), Max.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Lerp_FLambdaOperation2D(FLambdaOperation2D A, FLambdaOperation2D B, FLambdaOperation2D Alpha)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FMath::Lerp(A.GetValue(X, Y), B.GetValue(X, Y), Alpha.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::NormalizeToRange_FLambdaOperation2D(FLambdaOperation2D Value, FLambdaOperation2D RangeMin, FLambdaOperation2D RangeMax)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return UKismetMathLibrary::NormalizeToRange(Value.GetValue(X, Y), RangeMin.GetValue(X, Y), RangeMax.GetValue(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::PingPong_FLambdaOperation2D(FLambdaOperation2D Value, FLambdaOperation2D Amplitude, FLambdaOperation2D Frequency)
{
	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		const float InValue = Value.GetValue(X, Y);
		const float InAmplitude = Amplitude.GetValue(X, Y);
		const float InFrequency = Frequency.GetValue(X, Y);

		return InAmplitude - FMath::Abs(FMath::Fmod(FMath::Abs(InValue * InFrequency), (2.f * InAmplitude)) - InAmplitude);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::ApplyCurve_FLambdaOperation2D(FLambdaOperation2D Value, UCurveFloat* Curve)
{
	FRichCurve FloatCurve;
	if (Curve)
	{
		FloatCurve = Curve->FloatCurve;
	}
	else
	{
		FloatCurve.AddKey(0.f, 0.f);
		FloatCurve.AddKey(1.f, 1.f);
	}

	FLambdaOperation2D Operation;
	Operation.BindLambda([=](const float X, const float Y)
	{
		return FloatCurve.Eval(Value.GetValue(X, Y));
	});
	return Operation;
}

float UFastNoiseGraphFunctionLibrary::CalculateNoiseOperation2D(FLambdaOperation2D ValueOperation2D, float X, float Y)
{
	return ValueOperation2D.GetValue(X, Y);
}
