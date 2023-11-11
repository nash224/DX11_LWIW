#include "PreCompile.h"
#include "ContentsUIRenderer.h"

ContentsUIRenderer::ContentsUIRenderer() 
{
}

ContentsUIRenderer::~ContentsUIRenderer() 
{
}


void ContentsUIRenderer::Start()
{
	ContentsSpriteRenderer::Start();
	SetCameraOrder(ECAMERAORDER::UI);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////