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

	std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade->CallFadeIn(1.2f);

	State.ChangeState(EDREAMSTATE::Stay);
}

void DreamLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ResRelease();
	BGMPlayer.Stop();

	PlayLevel::GetTimeManager()->ChangeDay();
}


void DreamLevel::RendererSetting()
{
	const float4 HWinScale = GlobalValue::GetWindowScale().Half();
	float4 BasePosition = HWinScale;
	BasePosition.Y *= -1.0f;
	BasePosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

	std::shared_ptr<RendererActor> BaseBackGround = CreateActor<RendererActor>(EUPDATEORDER::Objects);
	BaseBackGround->Transform.SetLocalPosition(BasePosition);
	BaseBackGround->Init();
	BaseBackGround->Renderer->GetColorData().PlusColor = float4(-1.0f, -1.0f, -1.0f, 1.0f);
	BaseBackGround->Renderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale());


	float4 BackGroundPosition = HWinScale;
	BackGroundPosition.Y *= -1.0f;
	BackGroundPosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Object);


	std::shared_ptr<RendererActor> EndingBackGround = CreateActor<RendererActor>(EUPDATEORDER::Objects);
	EndingBackGround->Transform.SetLocalPosition(BackGroundPosition);
	EndingBackGround->Init();
	EndingBackGround->Renderer->AutoSpriteSizeOn();
	EndingBackGround->Renderer->CreateAnimation("Dream", "Sleep_1.png", 0.18f, 1, 11);
	EndingBackGround->Renderer->ChangeAnimation("Dream");
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
	const float MaxDreamTime = 6.0f;

	if (_Parent->GetStateTime() > MaxDreamTime)
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