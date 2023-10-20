#include "PreCompile.h"
#include "LogoLevel.h"

#include "NormalProp.h"

#include "FadeObject.h"
#include "CameraControler.h"

LogoLevel::LogoLevel() 
{
}

LogoLevel::~LogoLevel() 
{
}


void LogoLevel::Start()
{
	ContentsLevel::Start();

	float4 Position= GlobalValue::GetWindowScale().Half();
	Position.Y *= -1.0f;

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Fix);
		GetMainCamera()->Transform.SetLocalPosition(Position);
	}
}

void LogoLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	UpdateFade(_Delta);
}

void LogoLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	Init();

	std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
	if (nullptr == Fade)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}
	Fade-> CallFadeIn(1.2f);
}

void LogoLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);

	ReleaseSprite();
	ReleaseTexture();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void LogoLevel::Init()
{
	LoadTexture();
	LoadSprite();
	LoadActor();
}


void LogoLevel::LoadTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Logo");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile pFile = Files[i];
		GameEngineTexture::Load(pFile.GetStringPath());
	}
}

void LogoLevel::LoadSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Logo");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile pFile = Files[i];
		GameEngineSprite::CreateSingle(pFile.GetFileName());
	}
}

void LogoLevel::LoadActor()
{
	float4 WinScale = GlobalValue::GetWindowScale();

	std::shared_ptr<NormalProp> m_BackPaint = CreateActor<NormalProp>();
	if (nullptr == m_BackPaint)
	{
		MsgBoxAssert("로고를 생성하지 못했습니다.");
		return;
	}

	m_BackPaint->Transform.SetLocalScale(WinScale);
	float4 Position = WinScale.Half();
	Position.Y *= -1.0f;
	m_BackPaint->Transform.SetLocalPosition(Position);
	m_BackPaint->Transform.AddLocalPosition({ 0.0f, 0.0f, 1.0f });
	m_BackPaint->Init();
	m_BackPaint->m_Renderer->SetSprite("Fade_Texture.png");

	std::shared_ptr<NormalProp> m_Logo = CreateActor<NormalProp>();
	if (nullptr == m_Logo)
	{
		MsgBoxAssert("로고를 생성하지 못했습니다.");
		return;
	}

	m_Logo->Transform.SetLocalPosition(Position);
	m_Logo->Init();
	m_Logo->m_Renderer->SetSprite("logo_1080p_0.png");

}


void LogoLevel::UpdateFade(float _Delta)
{
	m_LogoTime += _Delta;
	if (m_LogoTime >= 3.0f)
	{
		if (true == IsFadeOn)
		{
			return;
		}

		IsFadeOn = true;

		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		if (nullptr == Fade)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}
		Fade->CallFadeOut("MainMenu", 1.2f);
	}
}



void LogoLevel::ReleaseSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Logo");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile pFile = Files[i];
		GameEngineSprite::Release(pFile.GetFileName());
	}

}

void LogoLevel::ReleaseTexture()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Logo");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile pFile = Files[i];
		GameEngineTexture::Release(pFile.GetFileName());
	}
}