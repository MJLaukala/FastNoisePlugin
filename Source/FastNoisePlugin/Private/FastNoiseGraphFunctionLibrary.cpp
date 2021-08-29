// Copyright 2021 Matthew Laukala


#include "FastNoiseGraphFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

FLambdaOperation2D::FLambdaOperation2D()
{
	OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		// TODO:: Default to 1.f until Custom thunks or node are written.
		return 1.f;
	});
}

FLambdaOperation2D::FLambdaOperation2D(float Value)
{
	OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return Value;
	});
}

float FLambdaOperation2D::GetValue(float X, float Y) const
{
	return OperationDelegate.Execute(X, Y);
}

float FLambdaOperation2D::GetValue(const FVector2D& Vector2D) const
{
	return OperationDelegate.Execute(Vector2D.X, Vector2D.Y);
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::ToScalar_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return (NoiseOperation2D.OperationDelegate.Execute(X, Y) + 1.f) / 2.f;
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Sin_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Sin(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Asin_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Asin(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Sinh_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Sinh(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Cos_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Cos(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Acos_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Acos(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Tan_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Tan(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Atan_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Atan(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Atan2_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Atan2(A.OperationDelegate.Execute(X, Y), B.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::SquareRoot_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Sqrt(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::InverseSquareRoot_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::InvSqrt(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::MultiplyMultiply_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& Base, const FLambdaOperation2D& Exponent)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Pow(Base.OperationDelegate.Execute(X, Y), Exponent.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Percent_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		const float ValueB = B.OperationDelegate.Execute(X, Y);
		return (ValueB != 0.f) ? FMath::Fmod(A.OperationDelegate.Execute(X, Y), ValueB) : 0.f;
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Fraction_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Fractional(NoiseOperation2D.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Add_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) + B.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Subtract_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) - B.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Multiply_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) * B.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Divide_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) / B.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::SafeDivide_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return UKismetMathLibrary::SafeDivide(A.OperationDelegate.Execute(X, Y), B.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Less_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) < B.OperationDelegate.Execute(X, Y) ? TrueOperation.OperationDelegate.Execute(X, Y) : FalseOperation.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::LessEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) <= B.OperationDelegate.Execute(X, Y) ? TrueOperation.OperationDelegate.Execute(X, Y) : FalseOperation.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Greater_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) > B.OperationDelegate.Execute(X, Y) ? TrueOperation.OperationDelegate.Execute(X, Y) : FalseOperation.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::GreaterEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) >= B.OperationDelegate.Execute(X, Y) ? TrueOperation.OperationDelegate.Execute(X, Y) : FalseOperation.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::EqualEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) == B.OperationDelegate.Execute(X, Y) ? TrueOperation.OperationDelegate.Execute(X, Y) : FalseOperation.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::NotEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return A.OperationDelegate.Execute(X, Y) != B.OperationDelegate.Execute(X, Y) ? TrueOperation.OperationDelegate.Execute(X, Y) : FalseOperation.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::InRange_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& In, const FLambdaOperation2D& Min, const FLambdaOperation2D& Max, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		const float InValue = In.OperationDelegate.Execute(X, Y);
		return (InValue > Min.OperationDelegate.Execute(X, Y) && InValue < Max.OperationDelegate.Execute(X, Y)) ? TrueOperation.OperationDelegate.Execute(X, Y) : FalseOperation.OperationDelegate.Execute(X, Y);
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Min_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Min(A.OperationDelegate.Execute(X, Y), B.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Max_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Max(A.OperationDelegate.Execute(X, Y), B.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Clamp_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& Min, const FLambdaOperation2D& Max)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Clamp(Value.OperationDelegate.Execute(X, Y), Min.OperationDelegate.Execute(X, Y), Max.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Wrap_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& Min, const FLambdaOperation2D& Max)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Wrap(Value.OperationDelegate.Execute(X, Y), Min.OperationDelegate.Execute(X, Y), Max.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Lerp_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& Alpha)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return FMath::Lerp(A.OperationDelegate.Execute(X, Y), B.OperationDelegate.Execute(X, Y), Alpha.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::NormalizeToRange_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& RangeMin, const FLambdaOperation2D& RangeMax)
{
	FLambdaOperation2D Operation;
	Operation.OperationDelegate.BindLambda([=](const float X, const float Y)
	{
		return UKismetMathLibrary::NormalizeToRange(Value.OperationDelegate.Execute(X, Y), RangeMin.OperationDelegate.Execute(X, Y), RangeMax.OperationDelegate.Execute(X, Y));
	});
	return Operation;
}

float UFastNoiseGraphFunctionLibrary::CalculateNoiseOperation2D(const FLambdaOperation2D& ValueOperation2D, float X, float Y)
{
	return ValueOperation2D.GetValue(X, Y);
}
