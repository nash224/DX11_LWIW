#include "PreCompile.h"
#include "ContentsMath.h"


float ContentMathFunction::ReturnClampDegree(float _Degree)
{
	while (_Degree < 0.0f || _Degree >= 360.0f)
	{
		if (_Degree < 0.0f)
		{
			_Degree += 360.0f;
		}
		else if (_Degree >= 360.0f)
		{
			_Degree -= 360.0f;
		}
	}

	return _Degree;
}


// 8방향 반환
EDIRECTION DirectionFunction::GetDirectionToVector(const float4& _MoveVector)
{
	float Degree = std::atan2f(_MoveVector.Y, _MoveVector.X) * GameEngineMath::R2D;
	return DirectionFunction::GetDirectionToDegree(Degree);
}

// 8방향 변환
EDIRECTION DirectionFunction::GetDirectionToDegree(const float _Degree)
{
	float Degree = ContentMathFunction::ReturnClampDegree(_Degree);
	const float Cake16OnePieceDegree = 360.0f / 16.0f;

	if (Degree <= Cake16OnePieceDegree || Degree >= Cake16OnePieceDegree * 15.0f)
	{
		return EDIRECTION::RIGHT;
	}

	if (Degree > Cake16OnePieceDegree * 1.0f && Degree <= Cake16OnePieceDegree * 3.0f)
	{
		return EDIRECTION::RIGHTUP;
	}

	if (Degree > Cake16OnePieceDegree * 3.0f && Degree <= Cake16OnePieceDegree * 5.0f)
	{
		return EDIRECTION::UP;
	}

	if (Degree > Cake16OnePieceDegree * 5.0f && Degree <= Cake16OnePieceDegree * 7.0f)
	{
		return EDIRECTION::LEFTUP;
	}

	if (Degree > Cake16OnePieceDegree * 7.0f && Degree <= Cake16OnePieceDegree * 9.0f)
	{
		return EDIRECTION::LEFT;
	}

	if (Degree > Cake16OnePieceDegree * 9.0f && Degree <= Cake16OnePieceDegree * 11.0f)
	{
		return EDIRECTION::LEFTDOWN;
	}

	if (Degree > Cake16OnePieceDegree * 11.0f && Degree <= Cake16OnePieceDegree * 13.0f)
	{
		return EDIRECTION::DOWN;
	}

	if (Degree > Cake16OnePieceDegree * 13.0f && Degree <= Cake16OnePieceDegree * 15.0f)
	{
		return EDIRECTION::RIGHTDOWN;
	}

	MsgBoxAssert("잘못된 반환입니다.");
	return EDIRECTION::CENTER;
}

// 대각선 방향 반환
EDIRECTION DirectionFunction::GetDiagonalDirectionToVector(const float4& _MoveVector)
{
	float Degree = ContentMathFunction::ReturnClampDegree(ContentMathFunction::GetDegreeToVector2D(_MoveVector));

	if (Degree >= 0.0f && Degree < 90.0f)
	{
		return EDIRECTION::RIGHTUP;
	}
	else if (Degree >= 90.0f && Degree < 180.0f)
	{
		return EDIRECTION::LEFTUP;
	}
	else if (Degree >= 180.0f && Degree < 270.0f)
	{
		return EDIRECTION::LEFTDOWN;
	}
	else
	{
		return EDIRECTION::RIGHTDOWN;
	}

	MsgBoxAssert("잘못된 반환입니다.");
	return EDIRECTION::CENTER;
}

float4 DirectionFunction::GetVectorToDirection(EDIRECTION _Direction)
{
	float4 DirVector = float4::ZERO;

	switch (_Direction)
	{
	case EDIRECTION::UP:
		DirVector = { 0.0f , 1.0f };
		break;
	case EDIRECTION::LEFTUP:
		DirVector = { -1.0f , 1.0f };
		DirVector.Normalize();
		break;
	case EDIRECTION::LEFT:
		DirVector = { -1.0f , 0.0f };
		break;
	case EDIRECTION::LEFTDOWN:
		DirVector = { -1.0f , -1.0f };
		DirVector.Normalize();
		break;
	case EDIRECTION::RIGHTUP:
		DirVector = { 1.0f , 1.0f };
		DirVector.Normalize();
		break;
	case EDIRECTION::RIGHT:
		DirVector = { 1.0f , 0.0f };
		break;
	case EDIRECTION::RIGHTDOWN:
		DirVector = { 1.0f , -1.0f };
		DirVector.Normalize();
		break;
	case EDIRECTION::DOWN:
		DirVector = { 0.0f , -1.0f };
		break;
	default:
		break;
	}

	return DirVector;
}