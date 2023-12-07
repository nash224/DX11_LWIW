#pragma once
#include "ContentsSpriteRenderer.h"

// Ό³Έν :
class ALightActor : public GameEngineActor
{
public:
	// constrcuter destructer
	ALightActor();
	~ALightActor();

	// delete Function
	ALightActor(const ALightActor& _Other) = delete;
	ALightActor(ALightActor&& _Other) noexcept = delete;
	ALightActor& operator=(const ALightActor& _Other) = delete;
	ALightActor& operator=(ALightActor&& _Other) noexcept = delete;

	void Init();
	void SetSize(float _Size) ;
	void SetColor(const float4& _Color) const;
	void SetAlpha(float _Alpha);
	void SetAlphaCorrection(float _AlphaCorrection);
	void SetInner(float _Inner) const;
	void SetOutter(float _Outter) const;
	void SetImageScale(const float4& _Scale);


protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<ContentsSpriteRenderer> LightRenderer;
	std::shared_ptr<ContentsSpriteRenderer> ALightRenderer;

	float AlphaCorrection = 0.1f;
	float Alpha = 1.0f;

};

