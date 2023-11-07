#include "PreCompile.h"
#include "BranchTree.h"


#include "BackDrop_PlayLevel.h"

BranchTree::BranchTree() 
{
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
	m_PressType = EINTERACTION_PRESSTYPE::Press;
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

	m_Tree = nullptr;

	BranchVector.clear();
}

void BranchTree::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void BranchTree::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BranchTree::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
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


	m_Tree = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	m_Tree->CreateAnimation("Idle", "Tree_Branch.png", 5.0f, 0, 0, false);
	m_Tree->CreateAnimation("Shake", "Tree_Branch.png", 0.1f, 2, 4, false);
	m_Tree->AutoSpriteSizeOn();
	m_Tree->Transform.AddLocalPosition({0.0f , TreeRenderCorrection , 0.0f});
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
	BranchTotalInter = BranchFallInter * 4.0f;
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
	if (nullptr == m_Tree)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_Tree->ChangeAnimation(_SpriteName);
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
}

void BranchTree::UpdateShake(float _Delta)
{
	if (nullptr == m_Tree)
	{
		MsgBoxAssert("렌더러가 하지 않습니다.");
		return;
	}

	if (true == m_Tree->IsCurAnimationEnd())
	{
		ChangeState(EBRANCHTREESTATE::Idle);
		return;
	}
}




void BranchTree::UpdateBranch(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		m_BranchStateTime += _Delta;

		if (m_BranchStateTime > BranchFallInter)
		{
			BranchTotalInter -= BranchFallInter;
			m_BranchStateTime -= BranchFallInter;

			FallBranch();
			IsShaked = true;

			if (1 == m_BranchCount)
			{
				BranchFallInter = BranchTotalInter;
			}

			if (0 == m_BranchCount)
			{
				if (nullptr == m_InteractiveCol)
				{
					MsgBoxAssert("충돌체가 존재하지 않습니다.");
					return;
				}

				m_InteractiveCol->Off();
			}
		}
	}
	else
	{
		if (m_BranchStateTime > 0.0f)
		{
			m_BranchStateTime -= _Delta;
			
			if (m_BranchStateTime < 0.0f)
			{
				m_BranchStateTime = 0.0f;
			}
		}
	}
}


void BranchTree::FallBranch()
{
	EraseBranch();
	CreateBranchItem();
	--m_BranchCount;
}

// 나뭇가지 지우고
void BranchTree::EraseBranch()
{
	int FallOrder = m_BranchCount - 1;
	std::shared_ptr<GameEngineSpriteRenderer> BrachRenderer = BranchVector[FallOrder];
	if (nullptr == BrachRenderer)
	{
		MsgBoxAssert("존재하지 않는 렌더러를 참조하려 했습니다.");
		return;
	}

	BrachRenderer->Off();
}

// 아이템 생성시키고
void BranchTree::CreateBranchItem()
{
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("배경 매니저 포인터가 NUll을 가리킵니다.");
		return;
	}

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());

	const float4& FallingPoint = float4{ 60.0f, 40.0f };

	float4 FallingPosition = RandomClass.RandomVectorBox2D(FallingPositionBranchMinRange, FallingPositionBranchMaxRange, FallingPositionBranchMinRange, FallingPositionBranchMaxRange);
	FallingPosition += Transform.GetLocalPosition() + FallingPoint;
	BackDrop_PlayLevel::MainBackDrop->CreateItem("Branch_Collect", FallingPosition, 1, 60.0f);
}