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
 
cbuffer OutLineEffectInfo : register(b1)
{
    float4 OutLineColor;
    float4 ScreenSize;
    float Thickness;
    int temp1;
    int temp2;
    int temp3;
}


PixelOutPut OutLineEffect_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}




Texture2D OutLineTex : register(t0);
SamplerState OutLineSampler : register(s0);

float4 OutLineEffect_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Result = (float4) 0.0f;
    
    for (int y = -1; y <= 1;++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            float2 Offset = float2(x * Thickness / ScreenSize.x, y * Thickness / ScreenSize.y);
            
            float4 TexColor = OutLineTex.Sample(OutLineSampler, _Input.TEXCOORD.xy + Offset);
            if (TexColor.r > 0 || TexColor.g > 0 || TexColor.b > 0)
            {
                float4 CurColor = OutLineTex.Sample(OutLineSampler, _Input.TEXCOORD.xy);
                if (CurColor.a == 0.0f)
                {
                    Result = OutLineColor;
                }
            }
        }
    }
    
    return Result;
}