#pragma once



// ���� : ����� ��ǰ�� ����ϴ� Ŭ�����Դϴ�.
//		�Ǵ� �ȼ� �浹�� ����ϱ⵵ �մϴ�.
class Prop : public GameEngineActor
{
public:
	// constrcuter destructer
	Prop();
	~Prop();

	// delete Function
	Prop(const Prop& _Other) = delete;
	Prop(Prop&& _Other) noexcept = delete;
	Prop& operator=(const Prop& _Other) = delete;
	Prop& operator=(Prop&& _Other) noexcept = delete;

public:
	template<typename RenderOrder>
	void CreateRenderer(RenderOrder _Order)
	{
		CreateRenderer(static_cast<int>(_Order));
	}

	virtual void CreateRenderer(int _Order);

	void SetSprite(std::string_view _SpriteName);
	void SetRendererLocalPosition(const float4& _Position, PivotType _Direction = PivotType::Center);

public:
	// �ִϸ��̼� 
	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f,
		int _Start = -1,
		int _End = -1,
		bool _Loop = true
	);

	void ChangeAnimation(std::string_view _AnimationName);
	void SetAutoSpriteSize(float _Ratio, bool _Value = true);

	void CreateAutomatedAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f,
		int _Start = -1,
		int _End = -1,
		bool _Loop = true,
		float _Raito = 1.0f
	);


public:
	// �ȼ��浹
	void CreatePixelCollisionRenderer();
	void SetPixelSprite(std::string_view _FileName);

	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

public:
	void EnableDebugMode(bool _Value);
	

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	void ActorRelease();

	

public:
	bool PixelRendererCheck = false;

protected:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer = nullptr;
	float4 m_TextureScale;
	float4 m_Position;

protected:
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRenderer = nullptr;
	std::string m_PixelFileName = "";
};

