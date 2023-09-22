#pragma once


class PropParameter
{
public:
	std::string_view FileName;
	float4& TransformLocalPosition;
	PivotType ImagePivotType = PivotType::Center;

	PropParameter(std::string_view _FileName, float4& _TransformLocalPosition, PivotType _ImagePivotType = PivotType::Center)
		:
		FileName(_FileName),
		TransformLocalPosition(_TransformLocalPosition),
		ImagePivotType(_ImagePivotType)
	{

	}
};


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

public:
	template<typename RenderOrder>
	void CreateRenderer(RenderOrder _Order)
	{
		CreateRenderer(static_cast<int>(_Order));
	}

	virtual void CreateRenderer(int _Order);

	void SetSprite(std::string_view _SpriteName);
	void SetPosition(const float4& _Position, PivotType _Direction = PivotType::Center);
	void SetRendererImageScale(const float4& _Scale);


	// std::string_view FileName;
	// float4& TransformLocalPosition;
	// PivotType ImagePivotType;
	void SetSpriteRenderer(const PropParameter& _Parameter);
	void SetSpriteRenderer(std::string_view _FileName, const float4& _Position = float4::ZERO, PivotType _Type = PivotType::Center);
		
public:
	// 애니메이션 
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
	// 픽셀충돌
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
	float4 m_Position;

protected:
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRenderer = nullptr;
	std::string m_PixelFileName = "";

public:
	float4 m_PixelTextureScale = float4::ZERO;
};