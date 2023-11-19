#include "PreCompile.h"
#include "EndingLevel.h"

#include "RendererActor.h"
#include "CameraControler.h"
#include "FadeObject.h"

EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}


void EndingLevel::Start()
{
	ContentsLevel::Start();

	float4 CameraPosition = GlobalValue::GetWindowScale().Half();
	CameraPosition.Y *= -1.0f;

	GetMainCamera()->Transform.SetLocalPosition(CameraPosition);

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Fix);
	}
}

void EndingLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	UpdateExit();
}

void EndingLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	LoadResource();
	std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade->CallFadeIn();

	BackDrop.RendererSetting(this);
}

void EndingLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop.RendererRelease();
	ReleaseResource();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void EndingLevel::BackDropEnding::RendererSetting(GameEngineLevel* _Level)
{
	enum class EENDINGRENDERDEPTH
	{
		Font = 0,
		Button = 1, 
		Logo = 2,
		BackBase = 3,

	};

	{
		const float BackBaseDepth = GlobalUtils::CalculateFixDepth(EENDINGRENDERDEPTH::BackBase);

		BackBase = _Level->CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
		BackBase->Transform.SetLocalPosition(float4(0.0f, 0.0f, BackBaseDepth));
		const std::shared_ptr<GameEngineUIRenderer>& BackBaseRenderer = BackBase->CreateComponent<GameEngineUIRenderer>();
		BackBaseRenderer->GetColorData().MulColor = float4::ZERO;
		BackBaseRenderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale());
	}

	{
		const float LogoDepth = GlobalUtils::CalculateFixDepth(EENDINGRENDERDEPTH::Logo);

		Logo = _Level->CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
		Logo->Transform.SetLocalPosition(float4(0.0f, 60.0f, LogoDepth));
		const std::shared_ptr<GameEngineUIRenderer>& LogoRenderer = Logo->CreateComponent<GameEngineUIRenderer>();
		LogoRenderer->SetSprite("Ending_Logo.png");
		LogoRenderer->AutoSpriteSizeOn();
		LogoRenderer->SetAutoScaleRatio(0.4f);
	}
	
	const float FontDepth = GlobalUtils::CalculateFixDepth(EENDINGRENDERDEPTH::Font);

	{
		const float FontSize = 30.0f;

		Font = _Level->CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
		Font->Transform.SetLocalPosition(float4(0.0f, -120.0f, FontDepth));
		const std::shared_ptr<GameEngineUIRenderer>& FontRenderer = Font->CreateComponent<GameEngineUIRenderer>();
		FontRenderer->SetText(GlobalValue::Font_Liberation, "Thank you for watching!", FontSize, float4::WHITE, FW1_TEXT_FLAG::FW1_CENTER);
	}
	
	{
		const float FontSize = 24.0f;

		EndText = _Level->CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
		EndText->Transform.SetLocalPosition(float4(0.0f, -190.0f, FontDepth));
		const std::shared_ptr<GameEngineUIRenderer>& FontRenderer = EndText->CreateComponent<GameEngineUIRenderer>();
		FontRenderer->SetText(GlobalValue::Font_Liberation, "Exit", FontSize, float4::WHITE, FW1_TEXT_FLAG::FW1_CENTER);
	}

	{
		const float ButtonDepth = GlobalUtils::CalculateFixDepth(EENDINGRENDERDEPTH::Button);

		EndButton = _Level->CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
		EndButton->Transform.SetLocalPosition(float4(0.0f, -230.0f, ButtonDepth));
		const std::shared_ptr<GameEngineUIRenderer>& ButtonRenderer = EndButton->CreateComponent<GameEngineUIRenderer>();
		ButtonRenderer->SetSprite("ButtonSet_Keyboard_Z.png");
		ButtonRenderer->AutoSpriteSizeOn();
		ButtonRenderer->SetAutoScaleRatio(1.2f);
	}
}

void EndingLevel::BackDropEnding::RendererRelease()
{
	Logo = nullptr;
	BackBase = nullptr;
	Font = nullptr;
	EndButton = nullptr;
	EndText = nullptr;
}



void EndingLevel::LoadResource()
{
	if (nullptr == GameEngineTexture::Find("Ending_Logo.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\Ending\\");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineTexture::Load(pfile.GetStringPath());
		}
	}

	GameEngineSprite::CreateSingle("Ending_Logo.png");
}

void EndingLevel::ReleaseResource()
{
	GameEngineSprite::Release("Ending_Logo.png");

	if (nullptr == GameEngineTexture::Find("Ending_Logo.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\Ending");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineTexture::Release(pfile.GetFileName());
		}
	}
}

void EndingLevel::UpdateExit()
{
	if (true == GameEngineInput::IsDown('Z', this))
	{
		GameEngineWindow::WindowLoopOff();
	}
}