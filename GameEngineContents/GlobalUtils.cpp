#include "PreCompile.h"
#include "GlobalUtils.h"

GlobalUtils::GlobalUtils() 
{
}

GlobalUtils::~GlobalUtils() 
{
}

// 경로의 모든 파일을 로드합니다.
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

// 모든 경로의 파일을 로드합니다.
void GlobalUtils::LoadAllDirFile(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);


	//std::vector<GameEngineFile> Files = Dir.GetAllFile();
	
	std::vector<GameEngineDirectory> Directory = Dir.GetAllDirectory();
	
	for (size_t DirectoryCount = 0; DirectoryCount < Directory.size(); DirectoryCount++)
	{
		std::vector<GameEngineFile> Files = Directory[DirectoryCount].GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
}


void GlobalUtils::ReleaseAllTextureInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		std::string FileName = File.GetFileName();
		GameEngineTexture::Release(File.GetFileName());
	}
}

std::vector<GameEngineFile> GlobalUtils::GetAllFileInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	return Files;
}

std::vector<GameEngineDirectory> GlobalUtils::GetAllDirInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineDirectory> Dirs = Dir.GetAllDirectory();
	return Dirs;
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


float GlobalUtils::CalculateObjectDepth(float _BackYScale, float _PositionY, bool _isHill /*= false*/)
{
	float BackYScale = _BackYScale;
	if (0.0f == _BackYScale)
	{
		_BackYScale = GlobalValue::GetWindowScale().Y;
	}

	float Depth = (_BackYScale + _PositionY) / _BackYScale * 100.0f + 100.0f;

	if (true == _isHill)
	{
		Depth -= (_BackYScale + 50.0f) / _BackYScale * 100.0f;
	}

	return Depth;
}


float GlobalUtils::CalculateFixDepth(const float _Value)
{
	return _Value;
}

GameEngineSoundPlayer GlobalUtils::PlaySFX(std::string_view _SoundFileName)
{
	GameEngineSoundPlayer SoundPlayer = GameEngineSound::SoundPlay(_SoundFileName);
	SoundPlayer.SetVolume(GlobalValue::GetSFXVolume());

	return SoundPlayer;
}