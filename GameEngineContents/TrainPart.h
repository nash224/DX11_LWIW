#pragma once



// 설명 : 타이틀 메인 메뉴에서 가차의 부품입니다.
class TrainPart : public GameEngineActor
{
	friend class MainMenu_Trains;

public:
	// constrcuter destructer
	TrainPart();
	~TrainPart();

	// delete Function
	TrainPart(const TrainPart& _Other) = delete;
	TrainPart(TrainPart&& _Other) noexcept = delete;
	TrainPart& operator=(const TrainPart& _Other) = delete;
	TrainPart& operator=(TrainPart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;




private:
	void CreateLastTrainRenderer();
	void CreateRenderer();
	void SetSprite(std::string_view _TrainFileName , std::string_view _LightFileName = "");
	void SetLocalPosition(const float4& _TrainPosition, const float4& _LightPosition = float4::ZERO, PivotType _Pivot = PivotType::LeftTop);
	void AddLocalPosition(const float4& _float4);


public:
	void ActorRelease();

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_TrainRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_LightRenderer;
};

