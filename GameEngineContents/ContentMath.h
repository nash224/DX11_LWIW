#pragma once


struct ContentMathFunction
{
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
