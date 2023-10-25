#pragma once


// 설명 : 배경의 소품을 담당하는 클래스입니다.
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

	// 애니메이션 
	void CreateAndSetAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f
	);

	void SetAutoSpriteSize(float _Ratio, bool _Value = true);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


public:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRenderer = nullptr;
	std::string m_PixelFileName = "";

	float4 m_Position = float4::ZERO;
	float4 m_PixelTextureScale = float4::ZERO;
	bool PixelRendererCheck = false;

};