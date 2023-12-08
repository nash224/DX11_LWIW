#include "PreCompile.h"
#include "GlobalLoad.h"

#include "GlobalUtils.h"


GlobalLoad::GlobalLoad() 
{
}

GlobalLoad::~GlobalLoad() 
{
}

void GlobalLoad::LoadGlobalResource()
{
	LoadGlobalTexture();
	LoadGlobalSprite();
}

void GlobalLoad::LoadGlobalTexture()
{
	FileLoadFunction::LoadAllDirFile("Resources\\GlobalResources");
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
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSprite::CreateSingle(pFile.GetFileName());
		}
	}
}