#pragma once
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

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

private:
	void SetSprite(std::string_view _Name, unsigned int index = 0);
	void SetSampler(std::string_view _Name);
	void SetImageScale(const float4& _Scale)
	{
		ImageTransform.SetLocalScale(_Scale);
	}

	void AddImageScale(const float4& _Scale)
	{
		ImageTransform.AddLocalScale(_Scale);
	}

	std::shared_ptr<GameEngineSprite> GetSprite()
	{
		return Sprite;
	}

	inline GameEngineTransform& GetImageTransform()
	{
		return ImageTransform;
	}

	inline ColorData& GetColorData()
	{
		return ColorDataValue;
	}

	/*GaugeInfo& GetGaugeInfo()
	{
		return GaugeInfoValue;
	}*/

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
	void SetMaterialEvent(std::string_view _Name, int _Index) override;

private:
	std::shared_ptr<GameEngineSprite> Sprite;
	std::shared_ptr<class GameEngineSampler> Sampler;

	SpriteData CurSprite;
	float4 Pivot = { 0.5f, 0.5f };
	ColorData ColorDataValue;
	/*GaugeInfo GaugeInfoValue;*/

	GameEngineTransform ImageTransform;
};
