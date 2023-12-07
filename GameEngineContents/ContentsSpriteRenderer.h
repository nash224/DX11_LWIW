#pragma once
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

struct GaugeInfo
{
	int LineGauge = 0;
	int FromLeft = 0;
	int CircleGuage = 0;
	float Gauge = 1.0f;
};

struct TransparentInfo
{
	int iTransparent = 0;
	float Inner = 0.0f;
	float Outter = 0.0f;
	float TransTemp = 0.0f;
};

// 설명 :
class ContentsSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	ContentsSpriteRenderer();
	~ContentsSpriteRenderer();

	// delete Function
	ContentsSpriteRenderer(const ContentsSpriteRenderer& _Other) = delete;
	ContentsSpriteRenderer(ContentsSpriteRenderer&& _Other) noexcept = delete;
	ContentsSpriteRenderer& operator=(const ContentsSpriteRenderer& _Other) = delete;
	ContentsSpriteRenderer& operator=(ContentsSpriteRenderer&& _Other) noexcept = delete;

	// 스프라이트는 기본적으로 
	// 강제로 애니메이션을 정지한다는 뜻으로 받아들이겠다.
	void SetSprite(std::string_view _Name, unsigned int index = 0);
	
	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	inline void SetAutoScaleRatio(float _Ratio)
	{
		AutoScaleRatio.X = _Ratio;
		AutoScaleRatio.Y = _Ratio;
	}

	inline void SetAutoScaleRatio(float4 _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}

	bool IsRight()
	{
		return 0 < AutoScaleRatio.X;
	}

	void RightFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 0;
	}

	void LeftFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 1;
	}

	void UpFlip()
	{
		SpriteRendererInfoValue.FlipUp = 1;
	}

	void DownFlip()
	{
		SpriteRendererInfoValue.FlipUp = 0;
	}

	void SetSampler(std::string_view _Name);

	void SetPivotValue(const float4& _Value)
	{
		Pivot = _Value;
	}
	float4 GetPivotValue()
	{
		return Pivot;
	}

	void SetPivotType(PivotType _Type);
	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);

	std::shared_ptr<GameEngineSprite> GetSprite()
	{
		return Sprite;
	}

	const SpriteData& GetCurSprite()
	{
		return CurSprite;
	}

	inline GameEngineTransform& GetImageTransform()
	{
		return ImageTransform;
	}

	inline ColorData& GetColorData()
	{
		return ColorDataValue;
	}

	inline GaugeInfo& GetGaugeInfo()
	{
		return GaugeInfoValue;
	}

	inline TransparentInfo& GetTransparentInfo()
	{
		return TransparentData;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
	void SetMaterialEvent(std::string_view _Name, int _Index) override;

	int Index = 0;


private:
	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;
	SpriteRendererInfo SpriteRendererInfoValue;

	std::shared_ptr<class GameEngineSampler> Sampler;

	bool IsImageSize = false;
	float4 AutoScaleRatio = { 1.0f,1.0f,1.0f };

	float4 Pivot = { 0.5f, 0.5f };

	ColorData ColorDataValue;
	GaugeInfo GaugeInfoValue;
	TransparentInfo TransparentData;

	GameEngineTransform ImageTransform;

	bool IsUserSampler = true;
};
