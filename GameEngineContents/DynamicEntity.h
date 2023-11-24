#pragma once
#include "InteractiveActor.h"

// Ό³Έν :
class DynamicEntity : public InteractiveActor
{
private:
	friend class UI_InterativeMark;

public:
	// constrcuter destructer
	DynamicEntity();
	~DynamicEntity();

	// delete Function
	DynamicEntity(const DynamicEntity& _Other) = delete;
	DynamicEntity(DynamicEntity&& _Other) noexcept = delete;
	DynamicEntity& operator=(const DynamicEntity& _Other) = delete;
	DynamicEntity& operator=(DynamicEntity&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override{}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

protected:
	EDIRECTION GetDirectionFromVector(const float4& _MoveVector);
	EDIRECTION GetDiagonalDirectionFromVector(const float4& _MoveVector);
	EDIRECTION GetDirectionToDegree(const float _Degree);

	inline void ResetMoveVector()
	{
		m_MoveVector = float4::ZERO;
	}

	inline float4 GetMoveVector() const
	{
		return m_MoveVector;
	}

	inline void SetMoveVector(const float4& _Vector)
	{
		m_MoveVector = _Vector;
	}

	inline void AddMoveVector(const float4& _Vector)
	{
		m_MoveVector += _Vector;
	}

	void ApplyMovement(float _Delta);
	void ApplyOnlyMovement(float _Delta);

	float GetVolumeReductionByDistance();
	void PlaySFX(std::string_view _FileName);

protected:
	EDIRECTION m_Dir = EDIRECTION::LEFT;
	EDIRECTION m_RenderDir = EDIRECTION::CENTER;

	float4 m_MoveVector = float4::ZERO;
	float4 m_MoveForce = float4::ZERO;

};

