#include "PreCompile.h"
#include "DreamLevel.h"


#include "CameraControler.h"
#include "BGMManager.h"

#include "RendererActor.h"
#include "FadeObject.h"


DreamLevel::DreamLevel()
{
}

DreamLevel::~DreamLevel()
{
}


void DreamLevel::Start()
{
	ContentsLevel::Start();

	float4 CameraPosition = GlobalValue::GetWindowScale().Half();
	CameraPosition.Y *= -1.0f;

	GetMainCamera()->Transform.SetLocalPosition(CameraPosition);
	
	if (nullptr != ContentsLevel::LevelCamera)
	{
		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
	}

	StateSetting();
}

void DreamLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	AutoPlayBGM();
	State.Update(_Delta);
}

void DreamLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	ResLoad();
	RendererSetting();

	static constexpr const float Ending_FadeIn_Duration = 1.2f;

	std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade->CallFadeIn(Ending_FadeIn_Duration);

	State.ChangeState(EDREAMSTATE::Stay);
}

void DreamLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ResRelease();
	BGMPlayer.Stop();

	PlayLevel::s_TimeManager->ChangeDay();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void DreamLevel::RendererSetting()
{
	const float4& WinScale = GlobalValue::GetWindowScale();
	const float4& HWinScale = WinScale.Half();
	float4 BasePosition = HWinScale;
	BasePosition.Y *= -1.0f;
	BasePosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

	std::shared_ptr<RendererActor> BaseBackGround = CreateActor<RendererActor>(EUPDATEORDER::Objects);
	BaseBackGround->Transform.SetLocalPosition(BasePosition);
	BaseBackGround->Init();
	BaseBackGround->m_Renderer->GetColorData().PlusColor = float4(-1.0f, -1.0f, -1.0f, 1.0f);
	BaseBackGround->m_Renderer->GetImageTransform().SetLocalScale(WinScale);


	float4 BackGroundPosition = HWinScale;
	BackGroundPosition.Y *= -1.0f;
	BackGroundPosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Object);


	static constexpr const float Ending_Animation_Inter = 0.18f;

	std::shared_ptr<RendererActor> EndingBackGround = CreateActor<RendererActor>(EUPDATEORDER::Objects);
	EndingBackGround->Transform.SetLocalPosition(BackGroundPosition);
	EndingBackGround->Init();
	EndingBackGround->m_Renderer->AutoSpriteSizeOn();
	EndingBackGround->m_Renderer->CreateAnimation("Dream", "Sleep_1.png", Ending_Animation_Inter, 1, 11);
	EndingBackGround->m_Renderer->ChangeAnimation("Dream");
}

void DreamLevel::StateSetting() 
{
	CreateStateParameter StayState;
	StayState.Stay = std::bind(&DreamLevel::UpdateStay, this, std::placeholders::_1, std::placeholders::_2);
	StayState.End = std::bind(&DreamLevel::EndStay, this, std::placeholders::_1);
	State.CreateState(EDREAMSTATE::Stay, StayState);

	CreateStateParameter NoneState;
	State.CreateState(EDREAMSTATE::None, NoneState);
}

void DreamLevel::UpdateStay(float _Delta, GameEngineState* _Parent)
{
	static constexpr float Max_Dream_Time = 6.0f;

	if (_Parent->GetStateTime() > Max_Dream_Time)
	{
		_Parent->ChangeState(EDREAMSTATE::None);
	}
}

void DreamLevel::EndStay(GameEngineState* _Parent)
{
	std::shared_ptr<FadeObject> NextLevelFade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
	NextLevelFade->CallFadeOut("WitchHouse_UpFloor", 1.2f);
}


void DreamLevel::ResLoad()
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
		std::vector<GameEngineFile> SoundFiles = FileLoadFunction::GetAllFileInPath("Resources\\Sound\\BGM\\Sleep");
		for (GameEngineFile& pFile : SoundFiles)
		{
			GameEngineSound::SoundLoad(pFile.GetStringPath());
		}
	}
}

void DreamLevel::ResRelease()
{
	if (nullptr != GameEngineSprite::Find("Sleep_1.png"))
	{
		GameEngineSprite::Release("Sleep_1.png");
	}

	if (nullptr == GameEngineTexture::Find("Sleep_1.png"))
	{
		GameEngineFile pfile;
		pfile.MoveParentToExistsChild("Resources");
		pfile.MoveChild("Resources\\PlayContents\\PlayResourecs\\UI\\UI_SpriteCut\\Dream");
		GameEngineTexture::Release(pfile.GetStringPath());
	}
}

void DreamLevel::AutoPlayBGM()
{
	if (nullptr != MainPlaySound)
	{
		const int bgmType = MainPlaySound->GetPlayType();
		if (static_cast<int>(EPLAYBGMTYPE::Dream) != bgmType)
		{
			MainPlaySound->PlayBGM(EPLAYBGMTYPE::Dream, "SFX_Sleep_01.wav");
		}
	}
}