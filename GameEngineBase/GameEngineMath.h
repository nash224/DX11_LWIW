#pragma once
#include "GameEngineDebug.h"
#include <Windows.h>

// 설명 :
class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;

	static const float D2R;
	static const float R2D;

	// 3.14 => 180도
	// float R = 3.14;
	// float Result = R * (180.0f / 3.14);

};

class float4
{
public:
	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;

	inline int iX() const
	{
		return static_cast<int>(X);
	}

	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	inline float hX() const
	{
		return X * 0.5f;
	}

	inline float hY() const
	{
		return Y * 0.5f;
	}


	inline int ihX() const
	{
		return static_cast<int>(hX());
	}

	inline int ihY() const
	{
		return static_cast<int>(hY());
	}

	inline float4 Half() const
	{
		return { hX(), hY(), Z, W };
	}

	float4 operator-() const
	{
		float4 ReturnValue = *this;

		ReturnValue.X = -ReturnValue.X;
		ReturnValue.Y = -ReturnValue.Y;
		ReturnValue.Z = -ReturnValue.Z;
		return ReturnValue;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X - _Other.X;
		ReturnValue.Y = Y - _Other.Y;
		ReturnValue.Z = Z - _Other.Z;

		return ReturnValue;
	}



	float4 operator+(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X + _Other.X;
		ReturnValue.Y = Y + _Other.Y;
		ReturnValue.Z = Z + _Other.Z;

		return ReturnValue;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Other.X;
		ReturnValue.Y = Y * _Other.Y;
		ReturnValue.Z = Z * _Other.Z;

		return ReturnValue;
	}


	float4 operator*(const float _Value) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Value;
		ReturnValue.Y = Y * _Value;
		ReturnValue.Z = Z * _Value;

		return ReturnValue;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}


	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	bool operator==(const float4 _Value) const
	{
		return X == _Value.X &&
			Y == _Value.Y &&
			Z == _Value.Z;
	}

	inline void Normalize()
	{
		// 길이를 1로 만드는 함수입니다.
		float Len = Size();

		if (0.0f == Len)
		{
			// MsgBoxAssert("0으로 나누려고 했습니다.");
			return;
		}

		X /= Len;
		Y /= Len;
		Z /= Len;
	}

	inline float4 NormalizeReturn()
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	inline float Size()
	{
		float Value = X * X + Y * Y; // == 빗변 * 빗변

		// 제곱수이다.
		// 제곱을 풀어서 제곱근이라고 합니다.
		Value; // 빗변 * 빗변 => 빗변

		return sqrtf(Value);
	}

	float Max2D() const
	{
		return X > Y ? X : Y;
	}

	POINT WindowPOINT()
	{
		return POINT{ iX(), iY() };
	}



public:
	inline float AngleDeg()
	{
		return AngleRad() * GameEngineMath::R2D;
	}

	inline float AngleRad()
	{
		float4 AngleVector = NormalizeReturn();

		// 라디안 각도만 나오게 된다. = acosf(AngleVector.X);

		float Angle = acosf(AngleVector.X);

		if (0 >= AngleVector.Y)
		{
			Angle = GameEngineMath::PI + GameEngineMath::PI - Angle;
		}

		return Angle;
	}


	float4 VectorRotationToDegX(const float _Deg)
	{
		return VectorRotationToDegX(*this, _Deg);
	}

	static float4 VectorRotationToDegX(const float4& _Value, const float _Deg)
	{
		return VectorRotationToRadX(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 VectorRotationToRadX(const float4& _Value, const float _Rad)
	{
		// 왜 이 공식인지를 이해해야 합니다.
		float4 Rot;
		Rot.X = _Value.X;
		Rot.Y = _Value.Y * sinf(_Rad) + _Value.Z * cosf(_Rad);
		Rot.Z = _Value.Y * cosf(_Rad) - _Value.Z * sinf(_Rad);
		return Rot;
	}

	float4 VectorRotationToDegY(const float _Deg)
	{
		return VectorRotationToDegY(*this, _Deg);
	}


	static float4 VectorRotationToDegY(const float4& _Value, const float _Deg)
	{
		return VectorRotationToRadY(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 VectorRotationToRadY(const float4& _Value, const float _Rad)
	{
		// 왜 이 공식인지를 이해해야 합니다.
		float4 Rot;
		Rot.X = _Value.Z * cosf(_Rad) - _Value.X * sinf(_Rad);
		Rot.Y = _Value.Y;
		Rot.Z = _Value.Z * sinf(_Rad) + _Value.X * cosf(_Rad);
		return Rot;
	}

	float4 VectorRotationToDegZ(const float _Deg)
	{
		return VectorRotationToDegZ(*this, _Deg);
	}

	static float4 VectorRotationToDegZ(const float4& _Value, const float _Deg)
	{
		return VectorRotationToRadZ(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 VectorRotationToRadZ(const float4& _Value, const float _Rad)
	{
		// 왜 이 공식인지를 이해해야 합니다.
		float4 Rot;
		Rot.X = _Value.X * cosf(_Rad) - _Value.Y * sinf(_Rad);
		Rot.Y = _Value.X * sinf(_Rad) + _Value.Y * cosf(_Rad);
		Rot.Z = _Value.Z;
		return Rot;
	}


	//                                       90.0f
	static float4 GetUnitVectorFromRad(const float _Rad)
	{
		// cosf(_Rad)반지름의 길이 1일때의 cosf값이 구해집니다.
		// sinf(_Rad)반지름의 길이 1일때의 sinf값이 구해집니다.
		// => 빗변의 길이가 1일때의 결과가 나온다.

		// 
		// 1.57
		return { cosf(_Rad) , sinf(_Rad) };
	}

	// GetUnitVectorFromDeg(45)

	static float4 LerpClimp(const float4& Start, const float4& _End, float _Ratio)
	{

		if (1.0f <= _Ratio)
		{
			_Ratio = 1.0f;
		}

		return (Start * (1.0f - _Ratio)) + (_End * _Ratio);
	}


	static float4 GetUnitVectorFromDeg(const float _Degree)
	{
		// 90 => 1.57
		return GetUnitVectorFromRad(_Degree * GameEngineMath::D2R);
	}

};

class GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	float4 CenterLeftTop()
	{
		return { CenterLeft(), CenterTop() };
	}

	float4 CenterRightTop()
	{
		return{ CenterRight(), CenterTop() };
	}

	float4 CenterLeftBot()
	{
		return{ CenterLeft(), CenterBot() };
	}

	float4 CenterRightBot()
	{
		return{ CenterRight(), CenterBot() };
	}

	float CenterLeft()
	{
		return Pos.X - Scale.hX();
	}

	float CenterRight()
	{
		return Pos.X + Scale.hX();
	}

	float CenterTop()
	{
		return Pos.Y - Scale.hY();
	}

	float CenterBot()
	{
		return Pos.Y + Scale.hY();
	}

	int iCenterLeft()
	{
		return Pos.iX() - Scale.ihX();
	}

	int iCenterRight()
	{
		return Pos.iX() + Scale.ihX();
	}

	int iCenterTop()
	{
		return Pos.iY() - Scale.ihY();
	}

	int iCenterBot()
	{
		return Pos.iY() + Scale.ihY();
	}
};