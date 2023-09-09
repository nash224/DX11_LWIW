#pragma once




// 설명 :
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
	void SetRegenLocation(const float4& _Position);
	void SetRegenTime(float _Time);
	void SetSpeed(float _Speed);

private:

private:
	void UpdateSeries(float _Delta);

	void RegenProp();

public:
	void ActorRelease();

private:
	std::list<std::shared_ptr<SequentialProp>> listProps;

private:
	std::string m_SpriteFileName = "";
	float4 m_TextureScale = float4::ZERO;
	int m_Order = 0;

	float4 m_RegenLocation = float4::ZERO;	



	float m_StateTime;							// 진행된 시간
	float m_RegenTime;							// 리젠 간격
	float m_Speed;							

	float m_DelayDistance = 0.0f;				// 지체된 시간

	bool isFirstActor = true;
};

