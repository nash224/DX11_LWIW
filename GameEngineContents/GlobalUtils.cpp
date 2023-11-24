#include "PreCompile.h"
#include "GlobalUtils.h"


// 경로의 모든 파일을 로드합니다.
void FileLoadFunction::LoadAllFileInPath(std::string_view _Path)
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
void FileLoadFunction::LoadAllDirFile(std::string_view _Path)
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


void FileLoadFunction::ReleaseAllTextureInPath(std::string_view _Path)
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

std::vector<GameEngineFile> FileLoadFunction::GetAllFileInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	return Files;
}

std::vector<GameEngineDirectory> FileLoadFunction::GetAllDirInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineDirectory> Dirs = Dir.GetAllDirectory();
	return Dirs;
}


std::string FileLoadFunction::GetParentString(std::string_view _ChildPath)
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

//bool InputFunction::InputRegister(char _Key, std::function<void()> _Func)
//{
//	std::unordered_map<const char, std::function<void()>>::iterator FindIter = InputEvents.find(_Key);
//	if (FindIter != InputEvents.end())
//	{
//		return false;
//	}
//
//	InputEvents.insert(std::make_pair(_Key, _Func));
//}
//
//void InputFunction::Update()
//{
//	std::unordered_map<const char, std::function<void()>>::iterator StarIter = InputEvents.begin();
//	std::unordered_map<const char, std::function<void()>>::iterator EndIter = InputEvents.end();
//	 
//	for (;StarIter != EndIter; ++StarIter)
//	{
//		if (true == GameEngineInput::IsDown((*StarIter).first, this))
//		{
//			(*StarIter).second();
//			return;
//		}
//	}
//}

float DepthFunction::CalculateObjectDepth(float _BackYScale, float _PositionY, bool _isHill /*= false*/)
{
	if (0.0f == _BackYScale)
	{
		_BackYScale = GlobalValue::GetWindowScale().Y;
	}

	const float Depth = (_BackYScale + _PositionY) / _BackYScale * 100.0f + 100.0f;
	return Depth;
}


float DepthFunction::CalculateFixDepth(const float _Value)
{
	return _Value;
}

GameEngineSoundPlayer SFXFunction::PlaySFX(std::string_view _SoundFileName)
{
	GameEngineSoundPlayer SoundPlayer = GameEngineSound::SoundPlay(_SoundFileName);
	SoundPlayer.SetVolume(GlobalValue::GetSFXVolume());

	return SoundPlayer;
}

int StringFunction::GetNewLineCount(std::string_view _Text)
{
	int NewLineCount = 0;

	for (const char Character : _Text)
	{
		if (Character == '\n')
		{
			++NewLineCount;
		}
	}

	return NewLineCount;
}