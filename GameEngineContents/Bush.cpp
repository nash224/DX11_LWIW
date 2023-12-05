#include "PreCompile.h"
#include "Bush.h"

#include "PixelSetter.h"


Bush::Bush() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_BushShake_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Bush");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

Bush::~Bush() 
{
}


void Bush::Start()
{
	InteractiveActor::Start();

	DebugRenderer = PixelSetter::SetPixelCollision(this, "Bush_S_1_Pixel.png");
}

void Bush::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);

	UpdateState(_Delta);
}

void Bush::Release()
{
	InteractiveActor::Release();

	FXRenderer = nullptr;
	DebugRenderer = nullptr;
}


// 부쉬타입 설정
void Bush::SetBushType(EBUSHTYPE _Type)
{
	BushType = _Type;
}

// 시작
void Bush::Init()
{
	ContentsActor::SetPlusDepth(-20.0f);
	ContentsActor::ApplyDepth();
	CreateBushAnimation();
	InteractiveOptionSetting();
	BushStateSetting();
}

// 애니메이션 생성
void Bush::CreateBushAnimation()
{
	if (nullptr == GameEngineSprite::Find("Bush_0.png"))
	{
		// Bush & Bug
		GameEngineSprite::CreateCut("Bush_0.png", 4, 3);
		GameEngineSprite::CreateCut("Bush_0_Mask.png", 4, 3);
		GameEngineSprite::CreateCut("Bush_2_Shaking.png", 4, 3);
		GameEngineSprite::CreateCut("Bush_2_Shaking_Mask.png", 4, 3);
		GameEngineSprite::CreateCut("Bush_Animation_1.png", 4, 4);
		GameEngineSprite::CreateCut("BushBug_Appearing.png", 5, 5);
	}


	FXRenderer = CreateComponent<GameEngineSpriteRenderer>();
	FXRenderer->AutoSpriteSizeOn();
	FXRenderer->Off();

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->CreateAnimation("Normal", "Bush_0.png", 5.0f, 9, 9); // 평상시


	if (EBUSHTYPE::BushApple == BushType)
	{
		BodyRenderer->CreateAnimation("Shake", "Bush_0.png", 0.1f, 0, 7, false); // 흔듬
		BodyRenderer->CreateAnimation("Apple", "Bush_0.png", 5.0f, 10, 10, true); // 사과
	}

	if (EBUSHTYPE::BushBug == BushType)
	{
		BodyRenderer->CreateAnimation("Rustle", "Bush_Animation_1.png", 0.1f, 1, 5, true);
		BodyRenderer->FindAnimation("Rustle")->Inter = { 0.1f, 0.1f, 0.1f, 0.1f, 0.8f };
		BodyRenderer->CreateAnimation("AppearBug", "BushBug_Appearing.png", 0.1f, 1, 18, false);

		FXRenderer->CreateAnimation("Rustle_FX", "Bush_Animation_1.png", 0.1f, 6, 13, false); // 부스럭
		FXRenderer->CreateAnimation("AppearBug_FX", "BushBug_Appearing.png", 0.1f, 19, 24, false);	// 벌레 등장

		BodyRenderer->SetStartEvent("Rustle",[&](GameEngineSpriteRenderer* _Renderer)
			{
				FXRenderer->On();
				FXRenderer->ChangeAnimation("Rustle_FX", true);
			});

		BodyRenderer->SetStartEvent("AppearBug", [&](GameEngineSpriteRenderer* _Renderer)
			{
				SFXFunction::PlaySFX(RandomBushShakingSoundFilleName());
			});

		BodyRenderer->SetFrameEvent("AppearBug", 6, [&](GameEngineSpriteRenderer* _Renderer)
			{
				SFXFunction::PlaySFX("SFX_BushShake_01.wav");

				FXRenderer->On();
				FXRenderer->ChangeAnimation("AppearBug_FX");
			});

		FXRenderer->SetEndEvent("Rustle_FX", [](GameEngineSpriteRenderer* _Renderer)
			{
				_Renderer->Off();
			});


		FXRenderer->SetStartEvent("AppearBug_FX", [&](GameEngineSpriteRenderer* _Renderer) 
			{
				SFXFunction::PlaySFX(RandomBushBugAppearSoundFilleName());
			});

		FXRenderer->SetEndEvent("AppearBug_FX", [](GameEngineSpriteRenderer* _Renderer)
			{
				_Renderer->Off();
			});
	}
}

// 상호작용 옵션 설정
void Bush::InteractiveOptionSetting()
{
	switch (BushType)
	{
	case EBUSHTYPE::Bush:
		break;
	case EBUSHTYPE::BushBug:
	case EBUSHTYPE::BushApple:
		InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
		InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 96.0f , 96.0f }, float4::ZERO, ColType::AABBBOX2D);
		InteractiveActor::SetGearName("흔들기");
		break;
	case EBUSHTYPE::None:
	{
		MsgBoxAssert("타입을 지정해주세요.");
		return;
	}
		break;
	default:
		break;
	}
}

// 부쉬 초기 행동 적용
void Bush::BushStateSetting()
{
	switch (BushType)
	{
	case EBUSHTYPE::Bush:
		ChangeState(EBUSHSTATE::Normal);
		break;
	case EBUSHTYPE::BushBug:
		ChangeState(EBUSHSTATE::Rustle);
		break;
	case EBUSHTYPE::BushApple:
		ChangeState(EBUSHSTATE::Apple);
		break;
	case EBUSHTYPE::None:
		break;
	default:
		break;
	}
}


void Bush::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EBUSHSTATE::Normal:					UpdateNormal(_Delta);					break;
	case EBUSHSTATE::Apple:						UpdateApple(_Delta);					break;
	case EBUSHSTATE::Shake:						UpdateShake(_Delta);					break;
	case EBUSHSTATE::Rustle:					UpdateRustle(_Delta);					break;
	case EBUSHSTATE::AppearBug:					UpdateAppearBug(_Delta);				break;
	case EBUSHSTATE::None:
	{
		MsgBoxAssert("해당 상태는 변경할 수 없습니다.");
		return;
	}
	break;
	default:
		break;
	}
}

void Bush::ChangeState(EBUSHSTATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EBUSHSTATE::Normal:					StartNormal();					break;
		case EBUSHSTATE::Apple:						StartApple();					break;
		case EBUSHSTATE::Shake:						StartShake();					break;
		case EBUSHSTATE::Rustle:					StartRustle();					break;
		case EBUSHSTATE::AppearBug:					StartAppearBug();				break;
		case EBUSHSTATE::None:
		{
			MsgBoxAssert("해당 상태는 변경할 수 없습니다.");
			return;
		}
			break;
		default:
			break;
		}

		m_State = _State;
	}
}


void Bush::ChangeBushAnimation(std::string_view _Name)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았습니다.");
		return;
	}

	BodyRenderer->ChangeAnimation(_Name);
}

std::string Bush::RandomBushShakingSoundFilleName()
{
	GameEngineRandom RandomClass;

	std::string_view FileName;
	switch (RandomClass.RandomInt(1, 3))
	{
	case 1:
		FileName = "SFX_BushBug_BushShake_01.wav";
		break;
	case 2:
		FileName = "SFX_BushBug_BushShake_02.wav";
		break;
	case 3:
		FileName = "SFX_BushBug_BushShake_03.wav";
		break;
	default:
		break;
	}

	return FileName.data();
}

std::string Bush::RandomBushBugAppearSoundFilleName()
{
	GameEngineRandom RandomClass;

	std::string_view FileName;
	switch (RandomClass.RandomInt(1, 3))
	{
	case 1:
		FileName = "SFX_BushBug_Appear_01.wav";
		break;
	case 2:
		FileName = "SFX_BushBug_Appear_02.wav";
		break;
	case 3:
		FileName = "SFX_BushBug_Appear_03.wav";
		break;
	default:
		break;
	}

	return FileName.data();
}