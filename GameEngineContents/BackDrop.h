#pragma once



// 설명 :
class Scenery;
class Prop;
class BackDrop : public GameEngineActor
{
public:
	static BackDrop* MainBackDrop;

public:
	// constrcuter destructer
	BackDrop();
	~BackDrop();

	// delete Function
	BackDrop(const BackDrop& _Other) = delete;
	BackDrop(BackDrop&& _Other) noexcept = delete;
	BackDrop& operator=(const BackDrop& _Other) = delete;
	BackDrop& operator=(BackDrop&& _Other) noexcept = delete;


	const float4& GetBackGroundScale() const;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


public:
	bool IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor,  GameEngineColor _DefaultColor = { 255, 255, 255, 255 });
	void EnableBackDropDebugMode(bool _Value);

protected:
	// Scenery, Prop 텍스처 외에 자식에서 해주고 싶은 작업이 있을때
	virtual void EnableBackDropElemnetDebugMode(bool _Value) {}

public:
	void ActorRelease();

protected:
	std::vector<std::shared_ptr<Scenery>> vecScenery;
	std::vector<std::shared_ptr<Prop>> vecProps;
	std::vector<std::shared_ptr<Prop>> vecPixelProps;

	float4 m_BackScale = float4::ZERO;
};