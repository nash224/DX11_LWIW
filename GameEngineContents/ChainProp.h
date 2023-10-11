#pragma once



// Ÿ��Ʋ������ ����� �� �ִ� �����Դϴ�.
// ���� : ���� �ð����� ��ǰ�� �����ϴ� �����Դϴ�. ��ǰ�� �����ϴ� Pivot�� ������ Center�Դϴ�.
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

public:
	// Init
	void SetSprite(std::string_view _FileName);
	void SetFirstLocation(const float4& _Position);
	void SetRegenLocation(const float4& _Position);
	void SetSpawnPoint(float _Value);
	void SetAutoSpawnPoint();
	void SetSpeed(float _Speed);
	void CalculateAndSetRegenLocation(const float4& _Position);

	template<typename EnumType>
	void SetDepth(EnumType _Depth)
	{
		SetDepth(static_cast<int>(_Depth));
	}

	void SetDepth(const int _Depth);

private:

private:
	// ������Ʈ 
	void UpdateSeries();
	void EraseOverScreenProp();

	void RegenProp(const float4& _Position = float4::ZERO);

public:
	// Release
	void ActorRelease();

private:
	std::list<std::shared_ptr<SequentialProp>> listProps;

private:
	std::string m_SpriteFileName = "";
	float4 m_TextureScale = float4::ZERO;
	int m_Depth = 0;


	float4 m_FirstLocation = float4::ZERO;	
	float4 m_RegenLocation = float4::ZERO;
	float m_RegenPoint = 0.0f;

	float m_Speed = 0.0f;

	bool isFirstActorCreate = false;
};

