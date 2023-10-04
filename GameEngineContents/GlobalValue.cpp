#include "PreCompile.h"
#include "GlobalValue.h"


float4 GlobalValue::WindowScale = float4::ZERO;
std::shared_ptr<CameraControler> GlobalValue::g_CameraControler = nullptr;
void GlobalValue::SetWindowScale(const float4& _Scale)
{
	WindowScale = _Scale;
}

float4 GlobalValue::GetWindowScale()
{
	return WindowScale;
}