#include "PreCompile.h"
#include "GaugeUIRenderer.h"

GaugeUIRenderer::GaugeUIRenderer() 
{
}

GaugeUIRenderer::~GaugeUIRenderer() 
{
}


void GaugeUIRenderer::Start()
{
	GaugeRenderer::Start();
	SetCameraOrder(ECAMERAORDER::UI);
}

