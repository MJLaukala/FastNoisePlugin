// Copyright 2021 Matthew Laukala


#include "FastNoiseGraphFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

FLambdaOperation2D::FLambdaOperation2D()
{
	OperationMathLambda = [=](const float X, const float Y)
	{
		return 0.f;
	};
}

FLambdaOperation2D::FLambdaOperation2D(float Value)
{
	OperationMathLambda = [=](const float X, const float Y)
	{
		return Value;
	};
}

float FLambdaOperation2D::GetValue(float X, float Y) const
{
	return OperationMathLambda(X, Y);
}

float FLambdaOperation2D::GetValue(const FVector2D& Vector2D) const
{
	return OperationMathLambda(Vector2D.X, Vector2D.Y);
}

FStaticValue2D::FStaticValue2D(): Value(0)
{
	OperationMathLambda = [=](const float X, const float Y)
	{
		return Value;
	};
}

FStaticValue2D::FStaticValue2D(float InDefaultValue): Value(InDefaultValue)
{
	OperationMathLambda = [=](const float X, const float Y)
	{
		return Value;
	};
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::ToScalar_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return NoiseOperation2D.OperationMathLambda(X, Y) + 1.f / 2.f;
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::MultiplyMultiply_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& Base, const FLambdaOperation2D& Exponent)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return FMath::Pow(Base.OperationMathLambda(X, Y), Exponent.OperationMathLambda(X, Y));
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Percent_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		const float ValueB = B.OperationMathLambda(X, Y);
		return (ValueB != 0.f) ? FMath::Fmod(A.OperationMathLambda(X, Y), ValueB) : 0.f;
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Fraction_FLambdaOperation2D(const FLambdaOperation2D& NoiseOperation2D)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return FMath::Fractional(NoiseOperation2D.OperationMathLambda(X, Y));
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Add_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) + B.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Subtract_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) - B.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Multiply_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) * B.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Divide_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) / B.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::SafeDivide_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return UKismetMathLibrary::SafeDivide(A.OperationMathLambda(X, Y), B.OperationMathLambda(X, Y));
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Less_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) < B.OperationMathLambda(X, Y) ? TrueOperation.OperationMathLambda(X, Y) : FalseOperation.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::LessEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) <= B.OperationMathLambda(X, Y) ? TrueOperation.OperationMathLambda(X, Y) : FalseOperation.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Greater_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) > B.OperationMathLambda(X, Y) ? TrueOperation.OperationMathLambda(X, Y) : FalseOperation.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::GreaterEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) >= B.OperationMathLambda(X, Y) ? TrueOperation.OperationMathLambda(X, Y) : FalseOperation.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::EqualEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) == B.OperationMathLambda(X, Y) ? TrueOperation.OperationMathLambda(X, Y) : FalseOperation.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::NotEqual_FLambdaOperation2DFLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& TrueOperation, const FLambdaOperation2D& FalseOperation)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) != B.OperationMathLambda(X, Y) ? TrueOperation.OperationMathLambda(X, Y) : FalseOperation.OperationMathLambda(X, Y);
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Min_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return FMath::Min(A.OperationMathLambda(X, Y), B.OperationMathLambda(X, Y));
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Max_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return FMath::Max(A.OperationMathLambda(X, Y), B.OperationMathLambda(X, Y));
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Clamp_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& Min, const FLambdaOperation2D& Max)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return FMath::Clamp(Value.OperationMathLambda(X, Y), Min.OperationMathLambda(X, Y), Max.OperationMathLambda(X, Y));
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Wrap_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& Min, const FLambdaOperation2D& Max)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return FMath::Wrap(Value.OperationMathLambda(X, Y), Min.OperationMathLambda(X, Y), Max.OperationMathLambda(X, Y));
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::Lerp_FLambdaOperation2D(const FLambdaOperation2D& A, const FLambdaOperation2D& B, const FLambdaOperation2D& Alpha)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return FMath::Lerp(A.OperationMathLambda(X, Y), B.OperationMathLambda(X, Y), Alpha.OperationMathLambda(X, Y));
	};
	return Operation;
}

FLambdaOperation2D UFastNoiseGraphFunctionLibrary::NormalizeToRange_FLambdaOperation2D(const FLambdaOperation2D& Value, const FLambdaOperation2D& RangeMin, const FLambdaOperation2D& RangeMax)
{
	FLambdaOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return UKismetMathLibrary::NormalizeToRange(Value.OperationMathLambda(X, Y), RangeMin.OperationMathLambda(X, Y), RangeMax.OperationMathLambda(X, Y));
	};
	return Operation;
}

float UFastNoiseGraphFunctionLibrary::CalculateNoiseOperation2D(const FLambdaOperation2D& ValueOperation2D, float X, float Y)
{
	return ValueOperation2D.GetValue(X, Y);
}
