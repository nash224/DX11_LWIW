#pragma once

// Ό³Έν :
class ALightLerp
{
	friend class AlightInitial;
public:
	void SetLightRendererSetting(const float4& _Color);
	void UpdateLightLerp();


protected:

private:
	float4 LightColor = float4::ZERO;
	static float LightDepth;

public:
	std::shared_ptr<GameEngineSpriteRenderer> LightRenderer;


};

