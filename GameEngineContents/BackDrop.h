#pragma once



// Ό³Έν :
class BackDrop : public GameEngineActor
{
public:
	// constrcuter destructer
	BackDrop();
	~BackDrop();

	// delete Functions
	BackDrop(const BackDrop& _Other) = delete;
	BackDrop(BackDrop&& _Other) noexcept = delete;
	BackDrop& operator=(const BackDrop& _Other) = delete;
	BackDrop& operator=(BackDrop&& _Other) noexcept = delete;

	const float4& GetBackGroundScale() const;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


protected:
	float4 m_BackScale = float4::ZERO;
};