#include "PreCompile.h"
#include "WorkSpaceSkyLerp.h"

WorkSpaceSkyLerp::WorkSpaceSkyLerp() 
{
}

WorkSpaceSkyLerp::~WorkSpaceSkyLerp() 
{
}


void WorkSpaceSkyLerp::Start()
{
	SkyLerp::Start();
	FollowCamera();
}

void WorkSpaceSkyLerp::Release()
{
	SkyLerp::Release();
}

void WorkSpaceSkyLerp::SetSkyData()
{
	SkyData.push_back(float4(0.0f, 0.0f, 0.0f, 0.30f));
}