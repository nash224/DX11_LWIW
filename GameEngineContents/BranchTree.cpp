#include "PreCompile.h"
#include "BranchTree.h"

BranchTree::BranchTree() 
{
}

BranchTree::~BranchTree() 
{
}


void BranchTree::Start()
{
	StaticEntity::Start();

	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	m_PressType = EINTERACTION_PRESSTYPE::Press;
}

void BranchTree::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
	UpdateBranch(_Delta);
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
	CreateAndSetCollision(ECOLLISION::Entity, { 32.0f , 32.0f }, float4::ZERO, ColType::SPHERE2D);
	CreateBranchTreehAnimation();
	CreateBranchRenderer();
	SetBranchInter();
	ChangeState(EBRANCHTREESTATE::Idle);
}

void BranchTree::CreateBranchTreehAnimation()
{
	m_Tree = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == m_Tree)
	{
		MsgBoxAssert("렌더러를 생성하지 못해습니다.");
		return;
	}

	m_Tree->CreateAnimation("Idle", "Tree_Branch.png", 5.0f, 0, 0, false);
	m_Tree->CreateAnimation("Shake", "Tree_Branch.png", 0.1f, 3, 5, false);
	m_Tree->AutoSpriteSizeOn();
	m_Tree->Transform.AddLocalPosition({0.0f , TreeRenderBias , 0.0f});
}

void BranchTree::CreateBranchRenderer()
{
	BranchVector.resize(static_cast<int>(EBRANCHFALLORDER::Max));

	{
		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		if (nullptr == BranchRenderer)
		{
			MsgBoxAssert("렌더러를 생성하지 못했습니다.");
			return;
		}

		BranchRenderer->SetSprite("Branch.png");
		float4 Position = FristBranchPosition;
		Position.Y += TreeRenderBias;
		Position.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::Roof);
		BranchRenderer->Transform.SetLocalPosition(Position);
		BranchRenderer->LeftFlip();
		BranchVector[static_cast<int>(EBRANCHFALLORDER::First)] = BranchRenderer;
	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		if (nullptr == BranchRenderer)
		{
			MsgBoxAssert("렌더러를 생성하지 못했습니다.");
			return;
		}

		BranchRenderer->SetSprite("Branch.png");
		float4 Position = SecondBranchPosition;
		Position.Y += TreeRenderBias;
		Position.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::Roof);
		BranchRenderer->Transform.SetLocalPosition(Position);
		BranchVector[static_cast<int>(EBRANCHFALLORDER::Second)] = BranchRenderer;
	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		if (nullptr == BranchRenderer)
		{
			MsgBoxAssert("렌더러를 생성하지 못했습니다.");
			return;
		}

		BranchRenderer->SetSprite("Branch_1.png");
		float4 Position = ThirdBranchPosition;
		Position.Y += TreeRenderBias;
		Position.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::Roof);
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
	if (true == IsEnalbeActive)
	{
		if (0 != m_BranchCount)
		{
			ChangeState(EBRANCHTREESTATE::Shake);
			return;
		}
	}
}


void BranchTree::StartShake()
{
	ChangeBranchTreeAnimation("Shake");
}

void BranchTree::UpdateShake(float _Delta)
{
	if (nullptr == m_Tree)
	{
		MsgBoxAssert("렌더러가 조냊하지 않습니다.");
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

void BranchTree::CreateBranchItem()
{

}