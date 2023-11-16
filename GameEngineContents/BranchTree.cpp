#include "PreCompile.h"
#include "BranchTree.h"


#include "BackDrop_PlayLevel.h"

BranchTree::BranchTree() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_TreeShake.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\TreeShaking");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

BranchTree::~BranchTree() 
{
}


void BranchTree::Start()
{
	StaticEntity::Start();
	StaticEntity::SetPixelCollision("Tree_Pixel.png");

	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	CreateAndSetCollision(ECOLLISION::Entity, { 84.0f , 32.0f }, float4::ZERO, ColType::SPHERE2D);
	PressType = EINTERACTION_PRESSTYPE::Press;
}

void BranchTree::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
	UpdateBranch(_Delta);
	UpdatePixelCollision();
}

void BranchTree::Release()
{
	StaticEntity::Release();

	BodyRenderer = nullptr;

	BranchVector.clear();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BranchTree::Init()
{
	ApplyDepth();
	CreateBranchTreehAnimation();
	CreateBranchRenderer();
	SetBranchInter();
	ChangeState(EBRANCHTREESTATE::Idle);
}

void BranchTree::CreateBranchTreehAnimation()
{
	if (nullptr == GameEngineSprite::Find("Tree_Branch.png"))
	{
		// branchTree
		GameEngineSprite::CreateCut("Tree_Branch.png", 3, 2);
		GameEngineSprite::CreateCut("Tree_Branch_Mask.png", 3, 2);

		GameEngineSprite::CreateSingle("Branch.png");
		GameEngineSprite::CreateSingle("Branch_1.png");
	}


	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	BodyRenderer->CreateAnimation("Idle", "Tree_Branch.png", 5.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Shake", "Tree_Branch.png", 0.1f, 2, 4, false);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->Transform.AddLocalPosition({0.0f , TreeRenderCorrection , 0.0f});
}

void BranchTree::CreateBranchRenderer()
{
	BranchVector.resize(static_cast<int>(EBRANCHFALLORDER::Max));

	{
		float4 Position = { -20.0f , -14.0f };
		Position.Y += TreeRenderCorrection;
		Position.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Roof);

		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		BranchRenderer->SetSprite("Branch.png");
		BranchRenderer->Transform.SetLocalPosition(Position);
		BranchRenderer->LeftFlip();
		BranchVector[static_cast<int>(EBRANCHFALLORDER::First)] = BranchRenderer;
	}

	{
		float4 Position = { 50.0f , 26.0f };
		Position.Y += TreeRenderCorrection;
		Position.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Roof);

		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		BranchRenderer->SetSprite("Branch.png");
		BranchRenderer->Transform.SetLocalPosition(Position);
		BranchVector[static_cast<int>(EBRANCHFALLORDER::Second)] = BranchRenderer;
	}

	{
		float4 Position = { -22.0f , 54.0f };
		Position.Y += TreeRenderCorrection;
		Position.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Roof);

		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		BranchRenderer->SetSprite("Branch_1.png");
		BranchRenderer->Transform.SetLocalPosition(Position);
		BranchVector[static_cast<int>(EBRANCHFALLORDER::Third)] = BranchRenderer;
	}
}

void BranchTree::SetBranchInter()
{
	BranchTotalTime = DropBranchCoolDown * 4.0f;
}



void BranchTree::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EBRANCHTREESTATE::Idle:
		UpdateIdle(_Delta);
		break;
	case EBRANCHTREESTATE::Shake:
		UpdateShake(_Delta);
		break;
	case EBRANCHTREESTATE::None:
	{
		MsgBoxAssert("상태를 지정해주지 않았습니다..");
		return;
	}
		break;
	default:
		break;
	}
}

void BranchTree::ChangeState(EBRANCHTREESTATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EBRANCHTREESTATE::Idle:
			StartIdle();
			break;
		case EBRANCHTREESTATE::Shake:
			StartShake();
			break;
		case EBRANCHTREESTATE::None:
		{
			MsgBoxAssert("없습니다.");
			return;
		}
			break;
		default:
			break;
		}

		m_State = _State;
	}
}



void BranchTree::ChangeBranchTreeAnimation(std::string_view _SpriteName)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	BodyRenderer->ChangeAnimation(_SpriteName);
}



void BranchTree::StartIdle()
{
	ChangeBranchTreeAnimation("Idle");
}

void BranchTree::UpdateIdle(float _Delta)
{
	if (true == IsShaked)
	{
		ChangeState(EBRANCHTREESTATE::Shake);
		return;
	}
}


void BranchTree::StartShake()
{
	IsShaked = false;

	ChangeBranchTreeAnimation("Shake");
	PlaySFX("SFX_TreeShake.wav");
}

void BranchTree::UpdateShake(float _Delta)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 하지 않습니다.");
		return;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EBRANCHTREESTATE::Idle);
		return;
	}
}

void BranchTree::UpdateBranch(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		ShakingTime += _Delta;

		if (ShakingTime > DropBranchCoolDown)
		{
			BranchTotalTime -= DropBranchCoolDown;
			ShakingTime -= DropBranchCoolDown;

			FallBranch();
			IsShaked = true;

			if (1 == BranchCount)
			{
				DropBranchCoolDown = BranchTotalTime;
			}

			if (0 == BranchCount)
			{
				if (nullptr == InteractiveCol)
				{
					MsgBoxAssert("충돌체가 존재하지 않습니다.");
					return;
				}

				InteractiveCol->Off();
			}
		}
	}
	else
	{
		if (ShakingTime > 0.0f)
		{
			ShakingTime -= _Delta;
			
			if (ShakingTime < 0.0f)
			{
				ShakingTime = 0.0f;
			}
		}
	}
}


void BranchTree::FallBranch()
{
	EraseBranch();
	DropBranchItem();
	--BranchCount;
}

void BranchTree::EraseBranch()
{
	int BranchOrder = BranchCount - 1;
	std::shared_ptr<GameEngineSpriteRenderer> BrachRenderer = BranchVector[BranchOrder];
	if (nullptr == BrachRenderer)
	{
		MsgBoxAssert("존재하지 않는 렌더러를 참조하려 했습니다.");
		return;
	}

	BrachRenderer->Off();
}

void BranchTree::DropBranchItem()
{
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("배경 매니저 포인터가 NUll을 가리킵니다.");
		return;
	}

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());

	const float4& FallingPoint = float4{ 30.0f, 30.0f };

	const float4& RandomFallingPosition = RandomClass.RandomVectorBox2D(FallingPositionBranchMinRange, FallingPositionBranchMaxRange, FallingPositionBranchMinRange, FallingPositionBranchMaxRange);
	const float4& FallingPosition = Transform.GetLocalPosition() + RandomFallingPosition;
	BackDrop_PlayLevel::MainBackDrop->CreateItem("Branch_Collect", FallingPosition, 1, 80.0f);
}