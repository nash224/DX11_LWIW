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
	GlobalUtils::LoadAllDirFile("Resources\\GlobalResources");
}

void GlobalLoad::LoadGlobalSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\GlobalResources");
	std::vector<GameEngineDirectory> Dirs = Dir.GetAllDirectory();
	for (size_t i = 0; i < Dirs.size(); i++)
	{
		GameEngineDirectory Folder = Dirs[i];
		std::vector<GameEngineFile> Files = Folder.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile =  Files[i];
			GameEngineSprite::CreateSingle(pFile.GetFileName());
		}
	}
}