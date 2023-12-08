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


PixelOutPut LightShader_VS(GameEngineVertex2D _Input)
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


cbuffer TransparentInfo : register(b5)
{
    int iTransparent;
    float Inner;
    float Outter;
    float TransTemp;
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



PixelOut LightShader_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut) 0.0f;
    
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
  
    if (1 == iTransparent)
    {
        if (Inner >= Outter)
        {
            discard;
        }
        
        float fOutter = saturate(Outter);
        float fInner = saturate(Inner);
        
        float2 VetorToCenter = _Input.TEXCOORD.xy - float2(0.5f, 0.5f);
        float2 Scalar2Scale = VetorToCenter * 2.0f;
        float Distance = length(Scalar2Scale);
        float Alpha = 1.0f - smoothstep(fInner, fOutter, Distance);
        if (Distance <= fInner)
        {
            Alpha = 1.0f;
        }
        
        Color.a *= Alpha;
    }
    
    
    if (0.0f >= Color.a)
    {
        discard;
    }
    
    Color += PlusColor;
    Color *= MulColor;
    
    
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

