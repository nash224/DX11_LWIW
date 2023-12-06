struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct PixelOutPut
{
    // ÇÈ¼¿½¦ÀÌ´õ¿¡ º¸³»´À ¤¤¿ª
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};
 


PixelOutPut SkyLightEffect_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D SkyTex : register(t0);
Texture2D LightTex : register(t1);
Texture2D ALightTex : register(t2);
SamplerState SkySampler : register(s0);
SamplerState LightSampler : register(s1);
SamplerState ALightSampler : register(s2);

float4 SkyLightEffect_PS(PixelOutPut _Input) : SV_Target0
{
    float4 SkyColor = SkyTex.Sample(SkySampler, _Input.TEXCOORD.xy);
    float4 LightColor = LightTex.Sample(LightSampler, _Input.TEXCOORD.xy);
    float4 ALightColor = ALightTex.Sample(ALightSampler, _Input.TEXCOORD.xy);
    
    float Alpha = max(LightColor.a, ALightColor.a);
    SkyColor.a = SkyColor.a * (1.0f - Alpha);
    
    return SkyColor;
}