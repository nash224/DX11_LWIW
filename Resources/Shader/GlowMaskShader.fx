#include "../../GameEngineCoreShader/Transform.fx"
#include "ContentsRenderBase.fx"

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

// _Input 0.5 0.5
PixelOutPut GlowMaskShader_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut)0;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    
    float4 CalUV = _Input.TEXCOORD;
    
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
    
    // UV
    Result.TEXCOORD.x = (CalUV.x * Scale2DX) + Pos2DX;
    Result.TEXCOORD.y = (CalUV.y * Scale2DY) + Pos2DY;
    
    return Result;
}

// ���� ���÷��� �ؽ�ó�� 1������ ���Ǳ� ������
// ���÷��� �ؽ�ó�� ������ �����ö� ������ ���ְų� Ư���� ���ĵ��� ���ο���
// ������ִ� �뵵�� �ִ�.

// �츮 ��Ģ

cbuffer ColorData : register(b1)
{
    float4 PlusColor; 
    float4 MulColor; 
};

Texture2D DiffuseTex : register(t0);
Texture2D MaskTex : register(t1);
SamplerState DiffuseTexSampler : register(s0);

struct PixelOut
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target2;
};

float4 GlowMaskShader_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    
    int2 ScreenPos = int2(_Input.POSITION.x, _Input.POSITION.y);
    if (MaskMode == 1)
    {
        ScreenPos.x = ScreenPos.x - RendererScreenPos.x;
        ScreenPos.y = ScreenPos.y - RendererScreenPos.y;
        
        ScreenPos.x += MaskScreenScale.x * 0.5f;
        ScreenPos.y += MaskScreenScale.y * 0.5f;
        
        ScreenPos.x -= MaskPivot.x;
        ScreenPos.y += MaskPivot.y;
    }
    
    if (IsMask == 1 && MaskTex[ScreenPos].r <= 0.0f)
    {
         clip(-1);
    }
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    if (BaseColorOnly != 0)
    {
        Color = BaseColor;
        Color.a = 1;
    }
        
    Color += PlusColor;
    Color *= MulColor;
    
    return Color;
}