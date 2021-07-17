// Copyright 2021 Matthew Laukala


#include "FastNoiseGraphFunctionLibrary.h"

FNoiseOperation2D::FNoiseOperation2D() : DefaultValue(0)
{
	OperationMathLambda = [=](const float X, const float Y)
	{
		return DefaultValue;
	};
}

FNoiseOperation2D::FNoiseOperation2D(float InDefaultValue) : DefaultValue(InDefaultValue)
{
	OperationMathLambda = [=](const float X, const float Y)
	{
		return DefaultValue;
	};
}

float FNoiseOperation2D::GetValue(float X, float Y) const
{
	return OperationMathLambda(X, Y);
}

float FNoiseOperation2D::GetValue(const FVector2D& Vector2D) const
{
	return OperationMathLambda(Vector2D.X, Vector2D.Y);
}

FNoiseOperation2D UFastNoiseGraphFunctionLibrary::Add_FNoiseOperation2DFNoiseOperation2D(const FNoiseOperation2D& A, const FNoiseOperation2D& B)
{
	FNoiseOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) + B.OperationMathLambda(X, Y);
	};
	return Operation;
}

FNoiseOperation2D UFastNoiseGraphFunctionLibrary::Subtract_FNoiseOperation2DFNoiseOperation2D(const FNoiseOperation2D& A, const FNoiseOperation2D& B)
{
	FNoiseOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) - B.OperationMathLambda(X, Y);
	};
	return Operation;
}

FNoiseOperation2D UFastNoiseGraphFunctionLibrary::Multiply_FNoiseOperation2DFNoiseOperation2D(const FNoiseOperation2D& A, const FNoiseOperation2D& B)
{
	FNoiseOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) * B.OperationMathLambda(X, Y);
	};
	return Operation;
}

FNoiseOperation2D UFastNoiseGraphFunctionLibrary::Divide_FNoiseOperation2DFNoiseOperation2D(const FNoiseOperation2D& A, const FNoiseOperation2D& B)
{
	FNoiseOperation2D Operation;
	Operation.OperationMathLambda = [=](const float X, const float Y)
	{
		return A.OperationMathLambda(X, Y) / B.OperationMathLambda(X, Y);
	};
	return Operation;
}

float UFastNoiseGraphFunctionLibrary::CalculateNoiseOperation2D(const FNoiseOperation2D& ValueOperation2D, float X, float Y)
{
	return ValueOperation2D.GetValue(X, Y);
}
