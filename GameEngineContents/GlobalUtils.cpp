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
	for (GameEngineFile& pFile : Files)
	{
		GameEngineTexture::Load(pFile.GetStringPath());
	}
}

void FileLoadFunction::LoadTextureAndCreateSingleSpriteInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile : Files)
	{
		GameEngineTexture::Load(pFile.GetStringPath());
		GameEngineSprite::CreateSingle(pFile.GetFileName());
	}
}

// 모든 경로의 파일을 로드합니다.
void FileLoadFunction::LoadAllDirFile(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
	for (GameEngineDirectory& Direction : Directorys)
	{
		std::vector<GameEngineFile> Files = Direction.GetAllFile();
		for (GameEngineFile& pFile: Files)
		{
			GameEngineTexture::Load(pFile.GetStringPath());
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
	for (GameEngineFile& pFile : Files)
	{
		GameEngineTexture::Release(pFile.GetFileName());
	}
}

void FileLoadFunction::ReleaseAllTextureAndSpriteInPath(std::string_view _Path)
{
	GameEngineDirectory Dir;
	std::string ParentString = GetParentString(_Path);
	Dir.MoveParentToExistsChild(ParentString);
	Dir.MoveChild(_Path);
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile : Files)
	{
		GameEngineSprite::Release(pFile.GetFileName());
		GameEngineTexture::Release(pFile.GetFileName());
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

void SFXFunction::LoadSoundFile(const std::vector<GameEngineFile>& _Files)
{
	for (GameEngineFile pFile : _Files)
	{
		if (nullptr == GameEngineSound::FindSound(pFile.GetFileName()))
		{
			GameEngineSound::SoundLoad(pFile.GetStringPath());
		}
	}
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

int StringFunction::GetNewLineCount(std::wstring_view _Text)
{
	int NewLineCount = 0;

	for (const wchar_t Character : _Text)
	{
		if (Character == '\n')
		{
			++NewLineCount;
		}
	}

	return NewLineCount;
}

std::string StringFunction::InsertNewLineBTWWord(std::string_view _Text, int _NumCharPerLine)
{
	std::wstring Result = InsertNewLine(GameEngineString::AnsiToUnicode(_Text), _NumCharPerLine);
	return GameEngineString::UnicodeToAnsi(Result);
}

std::wstring StringFunction::InsertNewLineBTWWord(std::wstring_view _Text, int _NumCharPerLine)
{
	return InsertNewLine(_Text, _NumCharPerLine);
}

std::wstring StringFunction::InsertNewLine(std::wstring_view _Text, int _NumCharPerLine)
{
	int NewLineCnt = 0;
	int LineCharCnt = 0;
	int ESCapeAndSignCnt = 0;

	std::wstring Text = _Text.data();
	std::wstring Result;
	std::wstring Word;

	Result.reserve(128);

	for (int i = 0; i != Text.size(); i++)
	{
		const wchar_t Char = Text[i];
		if (Char == ' ' || Char == '.' || Char == ',' || Char == '!' || Char == '\'' || Char == ')' || Char == '?')
		{
			if (Word.empty())
			{
				Result.push_back(Text[i]);
			}
			else
			{
				if (Word.size() + LineCharCnt >= _NumCharPerLine)
				{
					Result.push_back('\n');
					LineCharCnt = static_cast<int>(Word.size());
					ESCapeAndSignCnt = 0;
				}

				Result += Word;
				Result.push_back(Text[i]);
				Word.clear();
			}

			if (++ESCapeAndSignCnt > 3)
			{
				++LineCharCnt;
				ESCapeAndSignCnt = 0;
			}
		}
		else
		{
			Word.push_back(Text[i]);
			++LineCharCnt;
		}

		if (_NumCharPerLine <= LineCharCnt)
		{
			Result.push_back('\n');
			LineCharCnt = 0;
			ESCapeAndSignCnt = 0;
		}
	}

	if (false == Word.empty())
	{
		if (Word.size() + LineCharCnt >= _NumCharPerLine)
		{
			Result.push_back('\n');
			LineCharCnt = static_cast<int>(Word.size());
			ESCapeAndSignCnt = 0;
		}

		Result += Word;
	}

	return Result;
}



float RandomFunction::GetRandomfValue(float _Min, float _Max)
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GlobalValue::GetSeedValue());
	return RandomClass.RandomFloat(_Min, _Max);
}


float ArrangementHelper::Speed = 1.0f;
void ArrangementHelper::RegisterInput(void* _Ptr)
{
	GameEngineInput::AddInputObject(_Ptr);
}

void ArrangementHelper::InputUpdate(GameEngineObject* _Target, void* _Ptr)
{
	if (ArrangeRendererOnePixel(_Target, '7', _Ptr, float4::LEFT))
	{
		return;
	}
	if (ArrangeRendererOnePixel(_Target, '8', _Ptr, float4::RIGHT))
	{
		return;
	}
	if (ArrangeRendererOnePixel(_Target, '9', _Ptr, float4::UP))
	{
		return;
	}
	if (ArrangeRendererOnePixel(_Target, '0', _Ptr, float4::DOWN))
	{
		return;
	}
	if (true == GameEngineInput::IsDown('K', _Ptr))
	{
		Speed *= 10.0f;
		return;
	}
	if (true == GameEngineInput::IsDown('L', _Ptr))
	{
		Speed *= 0.1f;
		return;
	}
}

bool ArrangementHelper::ArrangeRendererOnePixel(GameEngineObject* _Target, char _Character, void* _Ptr, const float4& _MoveVector)
{
	if (true == GameEngineInput::IsDown(_Character, _Ptr))
	{
		const float4& MoveVector = _MoveVector * Speed;

		_Target->Transform.AddLocalPosition(MoveVector);
		OutputDebugStringA(_Target->Transform.GetLocalPosition().ToString().c_str());
		return true;
	}

	return false;
}