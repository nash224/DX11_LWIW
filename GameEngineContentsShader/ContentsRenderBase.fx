
cbuffer ContentRenderBaseInfo : register(b12)
{
    float4 BaseColor;
    int IsMask;
    int BaseColorOnly;
    int MaskMode;
    int BaseTemp2;
    float4 RendererScreenPos;
    float4 RenderScreenScale;
    float4 MaskScreenScale;
    float4 MaskPivot;
    float DeltaTime;
    float AccDeltaTime;
    float t1;
    float t2;
};