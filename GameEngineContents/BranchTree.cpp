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
	CreateAndSetCollision(ECOLLISION::Entity, { 64.0f , 32.0f }, float4::ZERO, ColType::SPHERE2D);
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
	m_Tree->CreateAnimation("Shake", "Tree_Branch.png", 0.1f, 2, 4, false);
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
	// 상호작용이 되면
	if (true == IsEnalbeActive)
	{
		// 시간 더 해줘서
		m_BranchStateTime += _Delta;

		// 일정시간이 넘을경우
		if (m_BranchStateTime > BranchFallInter)
		{
			// 그 시만만큼 빼주고
			BranchTotalInter -= BranchFallInter;
			m_BranchStateTime -= BranchFallInter;

			// 나뭇가지를 떨어트린다.
			FallBranch();
			IsShaked = true;

			// 대신 떨어지고 남은 나뭇가지 수가 1일때는
			if (1 == m_BranchCount)
			{
				// 다음 떨어지는 시간은 남은 시간으로 대체한다.
				BranchFallInter = BranchTotalInter;
			}

			// 만약 남은 나뭇가지수가 0이면
			if (0 == m_BranchCount)
			{
				 //충돌체는 필요없음으로 끈다.
				if (nullptr == m_InteractiveCol)
				{
					MsgBoxAssert("충돌체가 존재하지 않습니다.");
					return;
				}

				m_InteractiveCol->Off();
			}
		}
	}
	// 만약 상호작용을 안하고 있을때
	else
	{
		// 나뭇가지 업데이트 시간이 있다면
		if (m_BranchStateTime > 0.0f)
		{
			// 시간만큼 뺴준다
			m_BranchStateTime -= _Delta;
			
			// 뺸값이 0보다 작게 넘어갔다면
			if (m_BranchStateTime < 0.0f)
			{
				// 0으로 맞춤
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

	// 떨어지는 위치를 나무 중심으로부터 오른쪽 위로 정하고
	// 떨어지는 시작점을 오른쪽 위로 올림
	// 떨어지는 목표 거리는 60.0f로 고정

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
	float4 FallingPosition = RandomClass.RandomVectorBox2D(FallingPositionBranchMinRange, FallingPositionBranchMaxRange, FallingPositionBranchMinRange, FallingPositionBranchMaxRange);
	FallingPosition += Transform.GetLocalPosition() + float4{ 60.0f, 40.0f };
	BackDrop_PlayLevel::MainBackDrop->CreateItem("Branch_Collect.png", FallingPosition, 1, 60.0f);
}