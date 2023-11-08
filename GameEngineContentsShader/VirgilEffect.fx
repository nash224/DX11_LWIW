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
 


PixelOutPut VirgilEffect_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D Texure0 : register(t0);
Texture2D Texure1 : register(t1);
SamplerState Tex0Sampler : register(s0);
SamplerState Tex1Sampler : register(s1);

float4 VirgilEffect_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Color0 = Texure0.Sample(Tex0Sampler, _Input.TEXCOORD.xy);
    float4 Color1 = Texure1.Sample(Tex1Sampler, _Input.TEXCOORD.xy);
    
    if (0 != Color0.a && 0 != Color1.a)
    {
        Color0.a = 0.0f;
    }
    
    return Color0;
}