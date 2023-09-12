#include "PreCompile.h"
#include "GlobalLoad.h"

#include "GlobalUtils.h"


bool GlobalLoad::IsLoadGlobalResoruce = false;
GlobalLoad::GlobalLoad() 
{
}

GlobalLoad::~GlobalLoad() 
{
}

void GlobalLoad::LoadGlobalResource()
{
	if (false == IsLoadGlobalResoruce)
	{
		LoadGlobalTexture();
		LoadGlobalSprite();

		IsLoadGlobalResoruce = true;
	}
}

void GlobalLoad::LoadGlobalTexture()
{
	GlobalUtils::LoadAllFileInPath("Resources\\GlobalResources");
}

void GlobalLoad::LoadGlobalSprite()
{
	GameEngineSprite::CreateSingle("Fade_Texture.png");
}