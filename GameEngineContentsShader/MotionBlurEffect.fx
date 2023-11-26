struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};
 
//cbuffer MotionBlurInfo : register(c1)
//{
//    float4 WindowScale;
//    float4 MoveDirection;
//};

PixelOutPut MotionBlurEffect_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D Texure : register(t0);
SamplerState TexSampler : register(s0);

// 카메라 벡터 => 방향 및 스칼라
// NumSample
// 

float4 MotionBlurEffect_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Result = (float4) 0.0f;
    
    Result += Texure.Sample(TexSampler, _Input.TEXCOORD.xy);
    
    return Result;
}