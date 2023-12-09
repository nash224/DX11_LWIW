#include "PreCompile.h"
#include "MongSiri.h"

#include "MongSiri_Population.h"

#include "Ellie.h"
#include "UI_Inventory.h"
#include "ContentsMath.h"


FrameAnimationHelper MongSiri::ShadowRenderHelper;
MongSiri::MongSiri()
{
	if (nullptr == GameEngineSound::FindSound("SFX_MongsiriJump_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Mongsiri");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

MongSiri::~MongSiri()
{
}


void MongSiri::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 200, 200 }, float4::ZERO, ColType::SPHERE2D);
	InteractiveActor::SetNearInteractivePositionAndRange(float4::ZERO, 1.0f);
	InteractiveActor::SetInteractionOption(
		EINTERACTION_BUTTONTYPE::Gathering, 
		EINTERACTION_TYPE::Near, 
		ECOLLECTION_METHOD::MongSiri, 
		ETOOLTYPE::Gloves);
}

void MongSiri::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);

	UpdateState(_Delta);
	Emotion.Update(_Delta);
	InteractiveActor::UpdateSoundVolumeByDistance();
}

void MongSiri::Release()
{
	InteractiveActor::Release();

	ShadowRenderer = nullptr;
	Emotion.Release();
}


void MongSiri::Init()
{
	ApplyDepth();
	RendererSetting();
	Emotion.Init(this, float4(0.0f, 40.0f));
	LookStateSetting();
	InitDirection();
	ChangeState(EMONGSIRISTATE::Idle);
}

void MongSiri::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Mongsiri_Collected.png"))
	{
		// MongSiri
		GameEngineSprite::CreateCut("Mongsiri_Collected.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_CollectedA.png", 4, 1);
		GameEngineSprite::CreateCut("Mongsiri_Disappear.png", 6, 6);
		GameEngineSprite::CreateCut("Mongsiri_Escape.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_Idle.png", 3, 3);
		GameEngineSprite::CreateCut("Mongsiri_IdleA.png", 3, 3);
		GameEngineSprite::CreateCut("Mongsiri_IdleB.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_IdleD.png", 3, 3);
		GameEngineSprite::CreateCut("Mongsiri_Jump.png", 5, 5);
	}

	InteractiveActor::BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>();

	ShadowRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, DepthFunction::CalculateFixDepth(ERENDERDEPTH::ObjectShadow)));

	InteractiveActor::BodyRenderer->AutoSpriteSizeOn();
	InteractiveActor::BodyRenderer->CreateAnimation("Idle", "Mongsiri_IdleB.png", 0.2f, 4, 7);
	InteractiveActor::BodyRenderer->CreateAnimation("Idle_Back", "Mongsiri_IdleB.png", 0.2f, 8, 11);
	InteractiveActor::BodyRenderer->CreateAnimation("Jump", "Mongsiri_Jump.png", 0.1f, 5, 14);
	InteractiveActor::BodyRenderer->CreateAnimation("Jump_Back", "Mongsiri_Jump.png", 0.1f, 15, 24);
	InteractiveActor::BodyRenderer->CreateAnimation("Look", "Mongsiri_IdleD.png", 0.06f, 1, 4);
	InteractiveActor::BodyRenderer->FindAnimation("Look")->Inter[3] = 2.0f;
	InteractiveActor::BodyRenderer->CreateAnimation("Look_Back", "Mongsiri_IdleD.png", 0.06f, 5, 8);
	InteractiveActor::BodyRenderer->FindAnimation("Look_Back")->Inter[3] = 2.0f;
	InteractiveActor::BodyRenderer->CreateAnimation("Collected", "Mongsiri_Collected.png", 0.2f, 3, 8, false);
	InteractiveActor::BodyRenderer->FindAnimation("Collected")->Inter = { 0.1f, 0.1f, 0.1f, 0.2f, 0.3f, 0.4f };
	InteractiveActor::BodyRenderer->CreateAnimation("CollectedA", "Mongsiri_CollectedA.png", 0.06f, -1, -1, false);
	InteractiveActor::BodyRenderer->CreateAnimation("CollectedB", "Mongsiri_Collected.png", 0.12f, 6, 4, false);
	InteractiveActor::BodyRenderer->CreateAnimation("Disappear", "Mongsiri_Disappear.png", 0.1f, 10, 33, false);

	const std::shared_ptr<GameEngineFrameAnimation>& Animation = InteractiveActor::BodyRenderer->FindAnimation("Disappear");
	if (nullptr == Animation)
	{
		MsgBoxAssert("애니메이션을 찾지 못했습니다.");
		return;
	}

	Animation->Inter =
	{ 0.2f, 0.2f,
		0.2f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f, 0.1f
	};

	ShadowRenderHelper.CreateFrameInfo("Idle", {1,2,3,2});
	ShadowRenderHelper.CreateFrameInfo("Idle_Back", {1,2,3,2});
	ShadowRenderHelper.CreateFrameInfo("Jump", {1,2,3,4,4, 4,4,4,1,1});
	ShadowRenderHelper.CreateFrameInfo("Jump_Back", {1,2,3,4,4, 4,4,4,1,1});
	ShadowRenderHelper.CreateFrameInfo("Disappear", { 1,2,3,4,4, 4,4,4,6,6, 6,6,6,6,7, 8,9,9,9,0 ,0,0,0,0 });

	InteractiveActor::BodyRenderer->SetFrameEvent("Jump", 8, [&](GameEngineSpriteRenderer*)
		{
			SoundPlayer = SFXFunction::PlaySFX("SFX_MongsiriJump_01.wav");
		});

	InteractiveActor::BodyRenderer->SetFrameEvent("Jump_Back", 18, [&](GameEngineSpriteRenderer*)
		{
			SoundPlayer = SFXFunction::PlaySFX("SFX_MongsiriJump_01.wav");
		});


	InteractiveActor::BodyRenderer->SetStartEvent("Look", [&](GameEngineSpriteRenderer* _Renderer)
		{
			ShadowRenderer->SetSprite("Mongsiri_Jump.png", 1);
		});

	InteractiveActor::BodyRenderer->SetStartEvent("Look_Back", [&](GameEngineSpriteRenderer* _Renderer)
		{
			ShadowRenderer->SetSprite("Mongsiri_Idle.png", 1);
		});

	InteractiveActor::BodyRenderer->SetStartEvent("Collected", [&](GameEngineSpriteRenderer* _Renderer)
		{
			ShadowRenderer->SetSprite("Mongsiri_Collected.png", 1);
		});
	InteractiveActor::BodyRenderer->SetFrameEvent("Collected", 4, [&](GameEngineSpriteRenderer* _Renderer)
		{
			ShadowRenderer->SetSprite("Mongsiri_Jump.png", 4);
		});


	InteractiveActor::BodyRenderer->SetFrameEvent("Collected", 7, [&](GameEngineSpriteRenderer* _Renderer)
		{
			SoundPlayer = SFXFunction::PlaySFX("SFX_MongsiriRootUp.wav");
		});

	InteractiveActor::BodyRenderer->SetEndEvent("Collected", [&](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("CollectedA");
		});

	InteractiveActor::BodyRenderer->SetEndEvent("CollectedA", [&](GameEngineSpriteRenderer* _Renderer)
		{
			UI_Inventory::PushItem("Mongsiri_Collect");

			_Renderer->ChangeAnimation("CollectedB");
		});

	// 10, 33

	InteractiveActor::BodyRenderer->SetFrameEvent("Disappear", 21, [&](GameEngineSpriteRenderer*)
		{
			SoundPlayer = SFXFunction::PlaySFX("SFX_MongsiriHoleIn_01.wav");
		});
}

void MongSiri::InitDirection()
{
	GameEngineRandom RandomClass;
	switch (RandomClass.RandomInt(0, 3))
	{
	case 0:
		Dir = EDIRECTION::UP;
		break;
	case 1:
		Dir = EDIRECTION::RIGHT;
		break;
	case 2:
		Dir = EDIRECTION::DOWN;
		break;
	case 3:
		Dir = EDIRECTION::LEFT;
		break;
	default:
		break;
	}
}

void MongSiri::LookStateSetting()
{
	CreateStateParameter RecognizeState;
	RecognizeState.Start = std::bind(&MongSiri::StartRecognize, this, std::placeholders::_1);
	RecognizeState.Stay = std::bind(&MongSiri::UpdateRecognize, this, std::placeholders::_1, std::placeholders::_2);
	LookState.CreateState(ELOOKSTATE::Recognize, RecognizeState);

	CreateStateParameter NotRecognizeState;
	NotRecognizeState.Stay = std::bind(&MongSiri::UpdateNotRecognize, this, std::placeholders::_1, std::placeholders::_2);
	NotRecognizeState.End = std::bind(&MongSiri::EndNotRecognize, this, std::placeholders::_1);
	LookState.CreateState(ELOOKSTATE::NotRecognize, NotRecognizeState);

	CreateStateParameter NoneState;
	LookState.CreateState(ELOOKSTATE::None, NoneState);
}

/////////////////////////////////////////////////////////////////////////////////////

void MongSiri::UpdateState(float _Delta)
{
	switch (State)
	{
	case EMONGSIRISTATE::Idle:								UpdateIdle(_Delta);				break;
	case EMONGSIRISTATE::Jump:								UpdateJump(_Delta);				break;
	case EMONGSIRISTATE::Look:								UpdateLook(_Delta);				break;
	case EMONGSIRISTATE::Caught:							UpdateCaught(_Delta);			break;
	case EMONGSIRISTATE::Collected:							UpdateCollected(_Delta);		break;
	case EMONGSIRISTATE::Disappear:							UpdateDisappear(_Delta);		break;
	case EMONGSIRISTATE::None:																break;
		break;
	default:
		break;
	}
}

void MongSiri::ChangeState(EMONGSIRISTATE _State)
{
	if (State != _State)
	{
		switch (State)
		{
		case EMONGSIRISTATE::Idle:							EndIdle();						break;
		case EMONGSIRISTATE::Jump:							EndJump();						break;
		case EMONGSIRISTATE::Look:															break;
		case EMONGSIRISTATE::Collected:						EndCollected();					break;
		case EMONGSIRISTATE::Disappear:														break;
		case EMONGSIRISTATE::None:															break;
		default:
			break;
		}

		switch (_State)
		{
		case EMONGSIRISTATE::Idle:							StartIdle();					break;
		case EMONGSIRISTATE::Jump:							StartJump();					break;
		case EMONGSIRISTATE::Look:							StartLook();					break;
		case EMONGSIRISTATE::Caught:						StartCaught();					break;
		case EMONGSIRISTATE::Collected:						StartCollected();				break;
		case EMONGSIRISTATE::Disappear:						StartDisappear();				break;
		case EMONGSIRISTATE::None:
		{
			MsgBoxAssert("행동패턴을 지정해주세요.");
		}
		break;
		default:
			break;
		}

		State = _State;
	}
}

void MongSiri::ChangeAnimation(std::string_view _StateName)
{
	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	InteractiveActor::BodyRenderer->ChangeAnimation(_StateName);
}

void MongSiri::ChangeAnimationByDircetion(std::string_view _StateName, unsigned int _Index /*= 0*/)
{
	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	std::string AnimationName = _StateName.data();

	switch (Dir)
	{
	case EDIRECTION::CENTER:
		break;
	case EDIRECTION::UP:
		AnimationName += "_Back";
		break;
	case EDIRECTION::RIGHTUP:
		AnimationName += "_Back";
		InteractiveActor::BodyRenderer->LeftFlip();
		break;
	case EDIRECTION::RIGHT:
		InteractiveActor::BodyRenderer->LeftFlip();
		break;
	case EDIRECTION::RIGHTDOWN:
		InteractiveActor::BodyRenderer->LeftFlip();
		break;
	case EDIRECTION::DOWN:
		break;
	case EDIRECTION::LEFTDOWN:
		InteractiveActor::BodyRenderer->RightFlip();
		break;
	case EDIRECTION::LEFT:
		InteractiveActor::BodyRenderer->RightFlip();
		break;
	case EDIRECTION::LEFTUP:
		AnimationName += "_Back";
		InteractiveActor::BodyRenderer->RightFlip();
		break;
	default:
		break;
	}

	InteractiveActor::RenderDir = InteractiveActor::Dir;

	InteractiveActor::BodyRenderer->ChangeAnimation(AnimationName, false, _Index);
}



void MongSiri::GetCaught()
{
	ChangeState(EMONGSIRISTATE::Caught);
}


void MongSiri::AutoChangeDirAnimation(std::string_view _StateName)
{
	const float4 ElliePos = PlayLevel::GetCurLevel()->GetPlayerPtr()->Transform.GetLocalPosition();
	const float4 MyPos = Transform.GetLocalPosition();
	const float4 VectorToEllie = ElliePos - MyPos;
	const float Radian = std::atan2f(VectorToEllie.Y, VectorToEllie.X);
	InteractiveActor::Dir = DirectionFunction::GetDirectionToDegree(Radian * GameEngineMath::R2D);

	if (InteractiveActor::RenderDir != InteractiveActor::Dir)
	{
		const std::shared_ptr<GameEngineFrameAnimation>& Animation = InteractiveActor::BodyRenderer->CurAnimation();
		if (nullptr == Animation)
		{
			MsgBoxAssert("애니메이션이 존재하지 않습니다.");
			return;
		}

		ChangeAnimationByDircetion(_StateName, static_cast<unsigned int>(Animation->CurIndex));
	}
}