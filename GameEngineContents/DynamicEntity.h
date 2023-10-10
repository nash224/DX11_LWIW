#pragma once
#include "InteractiveActor.h"

// ���� :
class DynamicEntity : public InteractiveActor
{
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
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


protected:
	EDIRECTION GetDirectionFromVector(const float4& _MoveVector);
	void ApplyMovement(float _Delta);

protected:
	// ������
	// �� ���� �������Դϴ�.
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;


protected:
	// �ൿ
	float m_StateTime = 0.0f;

	// Ű ����
	EDIRECTION m_Dir = EDIRECTION::LEFT;
	EDIRECTION m_RenderDir = EDIRECTION::CENTER;

	// �̵�
	float4 m_MoveVector = float4::ZERO;
	float4 m_MoveForce = float4::ZERO;

};

