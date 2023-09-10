#pragma once



// 타이틀에서만 사용할 수 있는 액터입니다.
// 설명 : 일정 시간마다 소품을 생성하는 액터입니다. 소품을 생성하는 Pivot의 기준은 Center입니다.
class SequentialProp;
class ChainProp : public GameEngineActor
{
public:
	// constrcuter destructer
	ChainProp();
	~ChainProp();

	// delete Function
	ChainProp(const ChainProp& _Other) = delete;
	ChainProp(ChainProp&& _Other) noexcept = delete;
	ChainProp& operator=(const ChainProp& _Other) = delete;
	ChainProp& operator=(ChainProp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


public:
	template<typename DataType>
	void SetRenderOrder(DataType _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}

	void SetRenderOrder(int _Order);

	void SetSprite(std::string_view _FileName);
	void SetFirstLocation(const float4& _Position);
	void SetRegenLocation(const float4& _Position);
	void CalculateAndSetRegenLocationInputFirstLocation(const float4& _Position);
	void SetRegenTime(float _Time);
	void SetSpeed(float _Speed);

private:

private:
	void UpdateSeries(float _Delta);
	void EraseOverScreenProp();

	void RegenProp(const float4& _Position = float4::ZERO);

public:

public:
	void ActorRelease();

private:
	std::list<std::shared_ptr<SequentialProp>> listProps;

private:
	std::string m_SpriteFileName = "";
	float4 m_TextureScale = float4::ZERO;
	int m_Order = 0;


	float4 m_FirstLocation = float4::ZERO;	
	float4 m_RegenLocation = float4::ZERO;	



	float m_StateTime;							// 진행된 시간
	float m_RegenTime;							// 리젠 간격
	float m_Speed;							

	float m_DelayDistance = 0.0f;				// 지체된 시간

	bool isFirstActor = true;
};

