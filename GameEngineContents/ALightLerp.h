#pragma once

class ALightLerpParameter
{
	friend class ALightLerp;

public:
	ALightLerpParameter(const float4& _Color, 
		std::string_view _SpriteName,
		const float4& _Scale = float4::ZERO,
		const float4& _Position = float4::ZERO)
		: Color(_Color), SpriteName(_SpriteName), Scale(_Scale), Position(_Position)
	{

	}

private:
	float4 Color;
	std::string SpriteName;
	float4 Scale;
	float4 Position;
};


// Ό³Έν :
class ALightLerp
{
public:
	// delete Function
	/*ALightLerp(const ALightLerp& _Other) = delete;*/
	/*ALightLerp(ALightLerp&& _Other) noexcept = delete;*/
	ALightLerp& operator=(const ALightLerp& _Other) = delete;
	ALightLerp& operator=(ALightLerp&& _Other) noexcept = delete;

	void Init(GameEngineActor* _Actor, const ALightLerpParameter& _Para);

	void SetLightAlpha(float _Alpha);
	void SetPosition(const float4& _Pos);
	void SetLightRendererSetting(const float4& _Color = float4::ONE);
	void UpdateLightLerp();

	inline void On()
	{
		LightRenderer->On();
	}

	inline void Off()
	{
		LightRenderer->On();
	}

	inline void Release()
	{
		LightRenderer = nullptr;
	}


protected:
	std::shared_ptr<GameEngineSpriteRenderer> LightRenderer;

private:
	float4 LightColor = float4::ZERO;
	float Alpha = 1.0f;

};

