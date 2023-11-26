#pragma once


struct ContentMathFunction
{
	static bool IsAround2D(const float4& _PosA, const float4& _PosB, float _Range)
	{
		const float4& DistanceToEach = _PosA - _PosB;
		const float4& Size = DirectX::XMVector2Length(DistanceToEach.DirectXVector);
		if (Size.X < _Range)
		{
			return true;
		}

		return false;
	}
};

// Ό³Έν :
class ContentMath
{
public:
	// constrcuter destructer
	ContentMath();
	~ContentMath();

	// delete Function
	ContentMath(const ContentMath& _Other) = delete;
	ContentMath(ContentMath&& _Other) noexcept = delete;
	ContentMath& operator=(const ContentMath& _Other) = delete;
	ContentMath& operator=(ContentMath&& _Other) noexcept = delete;

protected:

private:


};

