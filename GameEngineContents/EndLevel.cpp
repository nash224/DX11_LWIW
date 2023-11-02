#include "PreCompile.h"
#include "EndLevel.h"


#include "CameraControler.h"

#include "RendererActor.h"
#include "FadeObject.h"


EndLevel::EndLevel()
{
}

EndLevel::~EndLevel()
{
}


void EndLevel::Start()
{
	ContentsLevel::Start();


	const float4 HWinScale = GlobalValue::GetWindowScale().Half();
	float4 CameraPosition = HWinScale;
	CameraPosition.Y *= -1.0f;

	GetMainCamera()->Transform.SetLocalPosition(CameraPosition);

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Fix);
	}

}

void EndLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);
}

void EndLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	ResLoad();

	static constexpr const float Ending_FadeIn_Duration = 1.2f;

	std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade->CallFadeIn(Ending_FadeIn_Duration);


	const float4 WinScale = GlobalValue::GetWindowScale();
	float4 BasePosition = WinScale.Half();
	BasePosition.Y *= -1.0f;
	BasePosition.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

	std::shared_ptr<RendererActor> BaseBackGround = CreateActor<RendererActor>(EUPDATEORDER::Objects);
	BaseBackGround->Transform.SetLocalPosition(BasePosition);
	BaseBackGround->Init();
	BaseBackGround->m_Renderer->GetColorData().PlusColor = float4(-1.0f, -1.0f, -1.0f, 1.0f);
	BaseBackGround->m_Renderer->GetImageTransform().SetLocalScale(WinScale);

	Init();
	PlayEndingBGM();
}

void EndLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ResRelease();
	BGMPlayer.Stop();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void EndLevel::Init()
{
	const float4 HWinScale = GlobalValue::GetWindowScale().Half();
	float4 BackGroundPosition = HWinScale;
	BackGroundPosition.Y *= -1.0f;
	BackGroundPosition.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Object);


	static constexpr const float Ending_Animation_Inter = 0.18f;

	std::shared_ptr<RendererActor> EndingBackGround = CreateActor<RendererActor>(EUPDATEORDER::Objects);
	EndingBackGround->Transform.SetLocalPosition(BackGroundPosition);
	EndingBackGround->Init();
	EndingBackGround->m_Renderer->AutoSpriteSizeOn();
	EndingBackGround->m_Renderer->CreateAnimation("Dream", "Sleep_1.png", Ending_Animation_Inter, 1, 11);
	EndingBackGround->m_Renderer->ChangeAnimation("Dream");
}

void EndLevel::ResLoad()
{
	if (nullptr == GameEngineTexture::Find("Sleep_1.png"))
	{
		GameEngineFile pfile;
		pfile.MoveParentToExistsChild("Resources");
		pfile.MoveChild("Resources\\PlayContents\\PlayResourecs\\UI\\UI_SpriteCut\\Dream");
		GameEngineTexture::Load(pfile.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Sleep_1.png"))
	{
		GameEngineSprite::CreateCut("Sleep_1.png", 4, 3);
	}

	if (nullptr == GameEngineSound::FindSound("SFX_Sleep_01.wav"))
	{
		std::vector<GameEngineFile> SoundFiles = GlobalUtils::GetAllFileInPath("Resources\\Sound\\BGM\\Sleep");
		for (GameEngineFile& pFile : SoundFiles)
		{
			GameEngineSound::SoundLoad(pFile.GetStringPath());
		}
	}
}

void EndLevel::ResRelease()
{
	if (nullptr != GameEngineSprite::Find("Sleep_1.png"))
	{
		GameEngineSprite::Release("Sleep_1.png");
	}
}

void EndLevel::PlayEndingBGM()
{
	BGMPlayer = GameEngineSound::SoundPlay("SFX_Sleep_01.wav", 999);
	BGMPlayer.SetVolume(GlobalValue::GetSFXVolume());
}