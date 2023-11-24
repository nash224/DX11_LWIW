#pragma once

// Ό³Έν :
class DustFx : public GameEngineActor
{
public:
	// constrcuter destructer
	DustFx();
	~DustFx();

	// delete Function
	DustFx(const DustFx& _Other) = delete;
	DustFx(DustFx&& _Other) noexcept = delete;
	DustFx& operator=(const DustFx& _Other) = delete;
	DustFx& operator=(DustFx&& _Other) noexcept = delete;

	void Init(const float4& _ParentPosition, float DustScaleRatio = 1.0f);

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> DustRenderer;


};

