#include "PreCompile.h"
#include "GlobalValue.h"


float4 GlobalValue::WindowScale = float4::ZERO;
int GlobalValue::RandomSeed = 0;
float GlobalValue::GlobalSoundVolume = 1.0f;
float GlobalValue::SFXVolume = 1.0f;
float GlobalValue::BGMVolume = 1.0f;
void GlobalValue::SetWindowScale(const float4& _Scale)
{
	WindowScale = _Scale;
}

float4 GlobalValue::GetWindowScale()
{
	return WindowScale;
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
	return GlobalSoundVolume;
}

void GlobalValue::SetSoundVolume(float _Volume)
{
	GlobalSoundVolume = _Volume;
}

float GlobalValue::GetSFXVolume()
{
	return GlobalSoundVolume * SFXVolume;
}

void GlobalValue::SetSFXVolume(float _Volume)
{
	SFXVolume = _Volume;
}

float GlobalValue::GetBGMVolume()
{
	return GlobalSoundVolume * BGMVolume;
}

void GlobalValue::SetBGMVolume(float _Volume)
{
	if (_Volume > 1.0f)
	{
		_Volume = 1.0f;
	}

	BGMVolume = _Volume;
}

float& GlobalValue::GetSFXVolumePointer()
{
	return SFXVolume;
}

float& GlobalValue::GetGlobalVolumePointer()
{
	return GlobalSoundVolume;
}

float& GlobalValue::GetBGMVolumePointer()
{
	return BGMVolume;
}