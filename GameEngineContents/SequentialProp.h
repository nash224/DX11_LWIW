#pragma once
#include "Prop.h"

// 설명 : ChainProp에서 생성되는 객체입니다. 
// 일정 시간마다 생성되고 기준선에서 넘어가면 자동으로 정리됩니다.
class SequentialProp : public Prop
{
	friend class ChainProp;

public:
	// constrcuter destructer
	SequentialProp();
	~SequentialProp();

	// delete Function
	SequentialProp(const SequentialProp& _Other) = delete;
	SequentialProp(SequentialProp&& _Other) noexcept = delete;
	SequentialProp& operator=(const SequentialProp& _Other) = delete;
	SequentialProp& operator=(SequentialProp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	void SetTextureScale(const float4& _Scale);
	void SetSpeed(float _Speed);

private:
	void UpdateSequential(float _Delta);

private:
	float4 m_TextureScale = float4::ZERO;

	float m_Speed = 0.0f;
	bool isOverScreen = false;
};

