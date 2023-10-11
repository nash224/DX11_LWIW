#pragma once


// 설명 : 배경의 소품을 담당하는 클래스입니다.
//		또는 픽셀 충돌을 담당하기도 합니다.
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



	// 픽셀충돌
	void OnlyPixelProp();
	void CreatePixelCollisionRenderer();
	void SetPixelSprite(std::string_view _FileName);

	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });



	// 디버그
	void EnableDebugMode(bool _Value);



	// 릴리즈
	virtual void ActorRelease();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


protected:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer = nullptr;
	float4 m_Position = float4::ZERO;

protected:
	// 픽셀 충돌
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRenderer = nullptr;
	std::string m_PixelFileName = "";

public:
	bool IsOnlyPixelProp = false;
	bool PixelRendererCheck = false;
	float4 m_PixelTextureScale = float4::ZERO;

};