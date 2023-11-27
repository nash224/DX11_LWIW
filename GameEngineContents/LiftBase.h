#pragma once
#include "StaticEntity.h"

// Ό³Έν :
class LiftBase : public StaticEntity
{
public:
	// constrcuter destructer
	LiftBase();
	~LiftBase();

	// delete Function
	LiftBase(const LiftBase& _Other) = delete;
	LiftBase(LiftBase&& _Other) noexcept = delete;
	LiftBase& operator=(const LiftBase& _Other) = delete;
	LiftBase& operator=(LiftBase&& _Other) noexcept = delete;


	inline void SetLiftPosition(const float4& _Pos)
	{
		LiftPos = _Pos;
	}

	inline float4 GetLiftPosition() const
	{
		return LiftPos;
	}

protected:
	float4 LiftPos = float4::ZERO;
	float4 LiftVector = float4::ZERO;

private:

};

