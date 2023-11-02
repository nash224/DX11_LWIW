#include "PreCompile.h"
#include "RendererActor.h"

RendererActor::RendererActor() 
{
}

RendererActor::~RendererActor() 
{
}


void RendererActor::Release()
{
	m_Renderer = nullptr;
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void RendererActor::Init(int _Order)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
}


