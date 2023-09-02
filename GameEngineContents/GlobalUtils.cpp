#include "PreCompile.h"
#include "GlobalUtils.h"

GlobalUtils::GlobalUtils() 
{
}

GlobalUtils::~GlobalUtils() 
{
}

void GlobalUtils::LoadAllFileInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);


	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}
}


std::string GlobalUtils::GetParentString(std::string_view _ChildPath)
{
	int CountBeforeBackSlash = 0;

	std::string ChildPath = _ChildPath.data();

	while (true)
	{
		if ('\\' == ChildPath[CountBeforeBackSlash])
		{
			break;
		}

		++CountBeforeBackSlash;
	}

	
	ChildPath.resize(CountBeforeBackSlash);

	return ChildPath;
}