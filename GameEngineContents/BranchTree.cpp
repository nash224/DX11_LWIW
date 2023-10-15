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
		MsgBoxAssert("�������� �������� ���ؽ��ϴ�.");
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
			MsgBoxAssert("�������� �������� ���߽��ϴ�.");
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
			MsgBoxAssert("�������� �������� ���߽��ϴ�.");
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
			MsgBoxAssert("�������� �������� ���߽��ϴ�.");
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
		MsgBoxAssert("���¸� ���������� �ʾҽ��ϴ�..");
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
			MsgBoxAssert("�����ϴ�.");
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
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("�������� ���� �ʽ��ϴ�.");
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
	// ��ȣ�ۿ��� �Ǹ�
	if (true == IsEnalbeActive)
	{
		// �ð� �� ���༭
		m_BranchStateTime += _Delta;

		// �����ð��� �������
		if (m_BranchStateTime > BranchFallInter)
		{
			// �� �ø���ŭ ���ְ�
			BranchTotalInter -= BranchFallInter;
			m_BranchStateTime -= BranchFallInter;

			// ���������� ����Ʈ����.
			FallBranch();
			IsShaked = true;

			// ��� �������� ���� �������� ���� 1�϶���
			if (1 == m_BranchCount)
			{
				// ���� �������� �ð��� ���� �ð����� ��ü�Ѵ�.
				BranchFallInter = BranchTotalInter;
			}

			// ���� ���� ������������ 0�̸�
			if (0 == m_BranchCount)
			{
				 //�浹ü�� �ʿ�������� ����.
				if (nullptr == m_InteractiveCol)
				{
					MsgBoxAssert("�浹ü�� �������� �ʽ��ϴ�.");
					return;
				}

				m_InteractiveCol->Off();
			}
		}
	}
	// ���� ��ȣ�ۿ��� ���ϰ� ������
	else
	{
		// �������� ������Ʈ �ð��� �ִٸ�
		if (m_BranchStateTime > 0.0f)
		{
			// �ð���ŭ ���ش�
			m_BranchStateTime -= _Delta;
			
			// �A���� 0���� �۰� �Ѿ�ٸ�
			if (m_BranchStateTime < 0.0f)
			{
				// 0���� ����
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

// �������� �����
void BranchTree::EraseBranch()
{
	int FallOrder = m_BranchCount - 1;
	std::shared_ptr<GameEngineSpriteRenderer> BrachRenderer = BranchVector[FallOrder];
	if (nullptr == BrachRenderer)
	{
		MsgBoxAssert("�������� �ʴ� �������� �����Ϸ� �߽��ϴ�.");
		return;
	}

	BrachRenderer->Off();
}

// ������ ������Ű��
void BranchTree::CreateBranchItem()
{
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("��� �Ŵ��� �����Ͱ� NUll�� ����ŵ�ϴ�.");
		return;
	}

	// �������� ��ġ�� ���� �߽����κ��� ������ ���� ���ϰ�
	// �������� �������� ������ ���� �ø�
	// �������� ��ǥ �Ÿ��� 60.0f�� ����

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
	float4 FallingPosition = RandomClass.RandomVectorBox2D(FallingPositionBranchMinRange, FallingPositionBranchMaxRange, FallingPositionBranchMinRange, FallingPositionBranchMaxRange);
	FallingPosition += Transform.GetLocalPosition() + float4{ 60.0f, 40.0f };
	BackDrop_PlayLevel::MainBackDrop->CreateItem("Branch_Collect.png", FallingPosition, 1, 60.0f);
}