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


	// SpriteRenderer Setting
	template<typename OrderType>
	void CreateRenderer(OrderType _Order)
	{
		CreateRenderer(static_cast<int>(_Order));
	}

	void CreateRenderer(int _Order = 0);

	void SetSprite(std::string_view _SpriteName);
	void SetRendererPivotType(PivotType _Direction = PivotType::Center);
	void SetRendererImageScale(const float4& _Scale);

	template<typename EnumType>
	void SetPositionAndDepth(const float4& _Position, EnumType _Depth)
	{
		Transform.SetLocalPosition({ _Position.X, _Position.Y, GlobalUtils::CalculateDepth(_Depth) });
	}

	void SetPositionAndDepth(const float4& _Position);

	// �ִϸ��̼� 
	void CreateAndSetAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f
	);

	void SetAutoSpriteSize(float _Ratio, bool _Value = true);



	// �ȼ��浹
	void CreatePixelCollisionRenderer();
	void SetPixelSprite(std::string_view _FileName);

	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });



	// �����
	void EnableDebugMode(bool _Value);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


public:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer = nullptr;
	float4 m_Position = float4::ZERO;

protected:
	// �ȼ� �浹
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRenderer = nullptr;
	std::string m_PixelFileName = "";

public:
	bool PixelRendererCheck = false;
	float4 m_PixelTextureScale = float4::ZERO;

};