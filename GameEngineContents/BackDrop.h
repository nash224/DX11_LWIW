#pragma once



// Ό³Έν :
class Scenery;
class Prop;
class BackDrop : public GameEngineActor
{
public:
	// constrcuter destructer
	BackDrop();
	~BackDrop();

	// delete Function
	BackDrop(const BackDrop& _Other) = delete;
	BackDrop(BackDrop&& _Other) noexcept = delete;
	BackDrop& operator=(const BackDrop& _Other) = delete;
	BackDrop& operator=(BackDrop&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	const float4& GetBackGroundScale() const;

protected:

protected:
	std::vector<std::shared_ptr<Scenery>> vecScenery;
	std::vector<std::shared_ptr<Prop>> vecProps;

	float4 m_BackScale;

private:

};

