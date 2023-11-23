#include "PreCompile.h"
#include "LogoLevel.h"

#include "CameraControler.h"

#include "FadeObject.h"
#include "RendererActor.h"

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

	if (nullptr != LevelCamera)
	{
		LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
		GetMainCamera()->Transform.SetLocalPosition(Position);
	}
}

void LogoLevel::Update(float _Delta)
{
	UpdateFade(_Delta);
}

void LogoLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadSprite();
	LoadActor();

	std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
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
	const float4& WinScale = GlobalValue::GetWindowScale();

	float4 Position = WinScale.Half();
	Position.Y *= -1.0f;

	{
		std::shared_ptr<RendererActor> BackPaint = CreateActor<RendererActor>();
		BackPaint->Transform.SetLocalScale(WinScale);
		BackPaint->Transform.SetLocalPosition(Position);
		BackPaint->Transform.AddLocalPosition({ 0.0f, 0.0f, 1.0f });
		BackPaint->Init();
		BackPaint->m_Renderer->GetColorData().MulColor = float4::ZERO;
	}

	{
		std::shared_ptr<RendererActor> Logo = CreateActor<RendererActor>();
		Logo->Transform.SetLocalPosition(Position);
		Logo->Init();
		Logo->m_Renderer->SetSprite("logo_1080p_0.png");
	}
}


void LogoLevel::UpdateFade(float _Delta)
{
	static constexpr const float FadeOutStartTime = 3.0f;

	AccTime += _Delta;
	if (AccTime > FadeOutStartTime)
	{
		if (false == IsFadeOn)
		{
			std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
			Fade->CallFadeOut("MainMenu", 1.2f);
		}

		IsFadeOn = true;
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