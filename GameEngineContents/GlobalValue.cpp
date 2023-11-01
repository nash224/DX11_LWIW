#include "PreCompile.h"
#include "GlobalValue.h"


float4 GlobalValue::WindowScale = float4::ZERO;
float4 GlobalValue::ItemScale = { 40.0f , 40.0f };
int GlobalValue::RandomSeed = 0;
std::shared_ptr<CameraControler> GlobalValue::g_CameraControler = nullptr;
float GlobalValue::SoundVolume = 1.0f;
float GlobalValue::SFXVolume = 1.0f;
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
	if (100000 == ++RandomSeed)
	{
		RandomSeed = 0;
	}
	
	return RandomSeed;
}


float GlobalValue::GetSoundVolume()
{
	return SoundVolume;
}

void GlobalValue::SetSoundVolume(float _Volume)
{
	SoundVolume = _Volume;
}

float GlobalValue::GetSFXVolume()
{
	return SoundVolume * SFXVolume;
}

void GlobalValue::SetSFXVolume(float _Volume)
{
	SFXVolume = _Volume;
}