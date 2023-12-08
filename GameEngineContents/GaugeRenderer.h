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

// Ό³Έν :
class GaugeRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GaugeRenderer();
	~GaugeRenderer();

	// delete Function
	GaugeRenderer(const GaugeRenderer& _Other) = delete;
	GaugeRenderer(GaugeRenderer&& _Other) noexcept = delete;
	GaugeRenderer& operator=(const GaugeRenderer& _Other) = delete;
	GaugeRenderer& operator=(GaugeRenderer&& _Other) noexcept = delete;


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

	void SetPivotValue(const float4& _Value)
	{
		Pivot = _Value;
	}
	float4 GetPivotValue()
	{
		return Pivot;
	}

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

	bool IsImageSize = false;
	float4 AutoScaleRatio = { 1.0f,1.0f,1.0f };

	float4 Pivot = { 0.5f, 0.5f };

	ColorData ColorDataValue;
	GaugeInfo GaugeInfoValue;

	GameEngineTransform ImageTransform;

	bool IsUserSampler = true;
};
