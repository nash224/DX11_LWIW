#include "../GameEngineCoreShader/Transform.fx"
#include "../GameEngineCoreShader/RenderBase.fx"
#include "Math.fx"


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


cbuffer GaugeInfo : register(b4)
{
    int LineGauge;
    int FromLeft;
    int CircleGuage;
    float Gauge;
};

cbuffer ColorData : register(b1)
{
    float4 PlusColor;
    float4 MulColor;
};


Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

struct PixelOut
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target1;
    float4 Color3 : SV_Target1;
    float4 Color4 : SV_Target1;
    float4 Color5 : SV_Target1;
    float4 Color6 : SV_Target1;
    float4 Color7 : SV_Target1;
};


static const float PI = 3.14159265358979323846264338327950288419716939937510f;



PixelOut GaugeShader_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut)0.0f;
    
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    
    if (1 == LineGauge)
    {
        float GaugeRatio = Gauge;
        if (0 != FromLeft)
        {
            GaugeRatio *= -1.0f;
            GaugeRatio += 1.0f;
        
            if (_Input.TEXCOORD.x < GaugeRatio)
            {
                clip(-1);
            }
        }
        else
        {
            if (_Input.TEXCOORD.x > GaugeRatio)
            {
                clip(-1);
            }
        }
    }
    
    if (1 == CircleGuage)
    {
        float PI2 = PI * 2.0f;
        float FillAngle = Gauge * PI2;
        
        float UVAngle = -atan2(_Input.TEXCOORD.x - 0.5f, _Input.TEXCOORD.y - 0.5f) + PI;
        if (UVAngle > FillAngle)
        {
            clip(-1);
        }
    }

    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    Color += PlusColor;
    Color *= MulColor;
    
    //if (0 < Target3)
    //{
    //    Result.Color3 = Color;
    //}
    
    Result.Color0 = Color;
    
    return Result;
}