#include "Transform.fx"


// 파일명과 함수명을 일치시키고 버텍스 쉐이더면 무조건 뒤에 _VS를 붙입니다.
// 의미있는 버텍스 쉐이더이다.
float4 TextureShader_VS(float4 pos : POSITION) : SV_POSITION
{
    return mul(pos, WorldViewPorjectionMatrix);
}

// b버퍼 14
// t텍스처 
// s샘플러 
// 둘의 슬롯은 공유되지 않는다.

// 보통 샘플러와 텍스처는 1쌍으로 사용되기 때문에
// 샘플러는 텍스처의 색상을 가져올때 보간을 해주거나 특수한 공식등을 내부에서
// 사용해주는 용도가 있다.
Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 TextureShader_PS(float4 pos : SV_Position) : SV_Target0
{
    // 이런 방식으로 사용하면 내가 직접 계산공식을 새워야 한다.
    // DiffuseTex.Load(int3)
    
    // 샘플러의 설정에 의해서 dx가 알아서 계산해주는 방식으로 처리하는것.
    float4 Color = DiffuseTex.Sample(Sampler, float2(0, 0));
    
    // 안에서 사용하지 않으면 아예 존재하지 않는다.
    return Color;
}