#pragma once


struct ContentMathFunction
{
	static float ReturnClampDegree(float _Degree);
	
	static float GetDegreeToVector2D(const float4& _Vector)
	{
		return std::atan2f(_Vector.Y, _Vector.X)* GameEngineMath::R2D;
	}

	static bool IsAround2D(const float4& _PosA, const float4& _PosB, float _Range)
	{
		const float4& Size = DirectX::XMVector2Length((_PosA - _PosB).DirectXVector);
		if (Size.X < _Range)
		{
			return true;
		}

		return false;
	}
};

struct DirectionFunction
{
public:
	static EDIRECTION GetDirectionToVector(const float4& _MoveVector);
	static EDIRECTION GetDirectionToDegree(const float _Degree);
	static EDIRECTION GetDiagonalDirectionToVector(const float4& _MoveVector);
	static float4 GetVectorToDirection(EDIRECTION _Direction);
};