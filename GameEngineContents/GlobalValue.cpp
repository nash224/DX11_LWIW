#include "PreCompile.h"
#include "GlobalValue.h"


float4 GlobalValue::WindowScale = float4::ZERO;
float4 GlobalValue::ItemScale = { 40.0f , 40.0f };
int GlobalValue::RandomSeed = 0;
std::shared_ptr<CameraControler> GlobalValue::g_CameraControler = nullptr;
void GlobalValue::Init()
{
	ItemScale = float4{ 40.0f , 40.0f };
}





void GlobalValue::SetWindowScale(const float4& _Scale)
{
	WindowScale = _Scale;
}

float4 GlobalValue::GetWindowScale()
{
	return WindowScale;
}


float4 GlobalValue::GetItemScale()
{
	return ItemScale;
}


int GlobalValue::GetSeedValue()
{
	if (100 == ++RandomSeed)
	{
		RandomSeed = 0;
	}
	
	return RandomSeed;
}