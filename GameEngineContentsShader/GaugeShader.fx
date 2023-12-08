#include "../GameEngineCoreShader/Transform.fx"
#include "../GameEngineCoreShader/RenderBase.fx"
#include "Math.fx"


// =====================================================================
//
// 참고 사이트
// https://www.shadertoy.com/view/ldlfD4
//
// =====================================================================

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

cbuffer SpriteData : register(b1)
{
    float Pos2DX;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
};


PixelOutPut GaugeShader_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    
    float4 CalUV = _Input.TEXCOORD;
    
    Result.TEXCOORD.x = (CalUV.x * Scale2DX) + Pos2DX;
    Result.TEXCOORD.y = (CalUV.y * Scale2DY) + Pos2DY;
    
    return Result;
}

cbuffer GaugeInfo : register(b4)
{
    int LineGauge;
    int FromLeft;
    int CircleGuage;
    float Gauge;
};


Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);


static const float PI = 3.141592f;



float4 GaugeShader_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
  
    if (1 == LineGauge) // 라인 진행 바
    {
        float GaugeRatio = Gauge; // 0 ~ 1
        if (0 != FromLeft) // 오른쪽부터 줄어들때
        {
            GaugeRatio *= -1.0f;
            GaugeRatio += 1.0f;
        
            if (_Input.TEXCOORD.x < GaugeRatio)
            {
                discard;
            }
        }
        else
        {
            if (_Input.TEXCOORD.x > GaugeRatio)
            {
                discard;
            }
        }
    }
    
    if (1 == CircleGuage) // 원형 진행 바
    {
        float PI2 = PI * 2.0f;
        float FillAngle = Gauge * PI2; // 0 ~ 360
        
        float UVAngle = -atan2(_Input.TEXCOORD.x - 0.5f, _Input.TEXCOORD.y - 0.5f) + PI; // 중앙점 (0.5f, 0.5f)기준 현재 픽셀 각도
        if (UVAngle > FillAngle) // 현재 각도가 채워지는 각도보다 크면 클립
        {
            discard;
        }
    }
    
    
    if (0.0f >= Color.a)
    {
        discard;
    }
    
    return Color;
}

