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

cbuffer SpriteRendererInfo : register(b3)
{
    int FlipLeft = 0;
    int FlipUp = 0;
    float Temp1;
    float Temp2;
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

    CalUV.x *= VertexUVMul.x;
    CalUV.y *= VertexUVMul.y;
    
       
    CalUV.x += VertexUVPlus.x;
    CalUV.y += VertexUVPlus.y;

    if (0 != FlipLeft)
    {
        CalUV.x *= -1;
        CalUV.x += 1;
    }

    if (0 != FlipUp) 
    {
        CalUV.y *= -1;
        CalUV.y += 1;
    }
    
    Result.TEXCOORD.x = (CalUV.x * Scale2DX) + Pos2DX;
    Result.TEXCOORD.y = (CalUV.y * Scale2DY) + Pos2DY;
    
    return Result;
}



cbuffer ColorData : register(b1)
{
    float4 PlusColor;
    float4 MulColor;
};

cbuffer GaugeInfo : register(b4)
{
    int LineGauge;
    int FromLeft;
    int CircleGuage;
    float Gauge;
};

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

struct PixelOut
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target2;
    float4 Color3 : SV_Target3;
    float4 Color4 : SV_Target4;
    float4 Color5 : SV_Target5;
    float4 Color6 : SV_Target6;
    float4 Color7 : SV_Target7;
};


static const float PI = 3.141592f;



PixelOut GaugeShader_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut)0.0f;
    
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
    
    Color += PlusColor;
    Color *= MulColor;
    
    //if (0 < Target3)
    //{
    //    Result.Color3 = Color;
    //}
    
    if (0 < Target0)
    {
        Result.Color0 = Color;
    }
    if (0 < Target1)
    {
        Result.Color1 = Color;
    }
    if (0 < Target2)
    {
        Result.Color2 = Color;
    }
    if (0 < Target3)
    {
        Result.Color3 = Color;
    }
    if (0 < Target4)
    {
        Result.Color4 = Color;
    }
    
    return Result;
}

