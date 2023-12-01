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

	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 84.0f , 32.0f }, float4::ZERO, ColType::SPHERE2D);
	InteractiveActor::SetGearName("흔들기");
	InteractiveActor::SetInteractionInputType(EINTERACTION_PRESSTYPE::Press);
}

void BranchTree::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	State.Update(_Delta);
	UpdateBranch(_Delta);
	UpdatePixelCollision();
}

void BranchTree::Release()
{
	StaticEntity::Release();

	BodyRenderer = nullptr;
	BranchRenderers.clear();

	Gauge.Release();
}


void BranchTree::Init()
{
	ApplyDepth();
	RendererSetting();
	BranchRendererSetting();
	Gauge.RendererSetting(this);
	Gauge.SetPosition(float4(60.0f, 30.0f));
	StateSetting();
}

void BranchTree::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Tree_Branch.png"))
	{
		GameEngineSprite::CreateCut("Tree_Branch.png", 3, 2);
		GameEngineSprite::CreateCut("Tree_Branch_Mask.png", 3, 2);

		GameEngineSprite::CreateSingle("Branch.png");
		GameEngineSprite::CreateSingle("Branch_1.png");
	}


	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BodyRenderer->Transform.AddLocalPosition({0.0f , TreeRenderCorrection , 0.0f});
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->CreateAnimation("Idle", "Tree_Branch.png", 5.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Shake", "Tree_Branch.png", 0.1f, 2, 4, false);
}

void BranchTree::BranchRendererSetting()
{
	BranchRenderers.resize(static_cast<int>(EBRANCHFALLORDER::Max));

	const float BranchDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Roof);

	{
		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		BranchRenderer->SetSprite("Branch.png");
		BranchRenderer->Transform.SetLocalPosition(float4(-20.0f, -14.0f + TreeRenderCorrection, BranchDepth));
		BranchRenderer->LeftFlip();
		BranchRenderers[static_cast<int>(EBRANCHFALLORDER::First)] = BranchRenderer;
	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		BranchRenderer->SetSprite("Branch.png");
		BranchRenderer->Transform.SetLocalPosition(float4(50.0f, 26.0f + TreeRenderCorrection, BranchDepth));
		BranchRenderers[static_cast<int>(EBRANCHFALLORDER::Second)] = BranchRenderer;
	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> BranchRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		BranchRenderer->SetSprite("Branch_1.png");
		BranchRenderer->Transform.SetLocalPosition(float4(-22.0f, 54.0f + TreeRenderCorrection, BranchDepth));
		BranchRenderers[static_cast<int>(EBRANCHFALLORDER::Third)] = BranchRenderer;
	}

	BranchTotalTime = DropCoolTime * 4.0f;
	NextFallBranchTime = DropCoolTime;
}


void BranchTree::StateSetting()
{
	CreateStateParameter IdleState;
	IdleState.Start = std::bind(&BranchTree::StartIdle, this, std::placeholders::_1);
	IdleState.Stay = std::bind(&BranchTree::UpdateIdle, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EBRANCHTREESTATE::Idle, IdleState);

	CreateStateParameter ShakeState;
	ShakeState.Start = std::bind(&BranchTree::StartShake, this, std::placeholders::_1);
	ShakeState.Stay = std::bind(&BranchTree::UpdateShake, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EBRANCHTREESTATE::Shake, ShakeState);

	State.ChangeState(EBRANCHTREESTATE::Idle);
}

void BranchTree::ChangeAnimation(std::string_view _SpriteName)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	BodyRenderer->ChangeAnimation(_SpriteName);
}


void BranchTree::StartIdle(GameEngineState* _Parent)
{
	ChangeAnimation("Idle");
}

void BranchTree::UpdateIdle(float _Delta, GameEngineState* _Parent)
{
	if (true == IsShaked)
	{
		State.ChangeState(EBRANCHTREESTATE::Shake);
		return;
	}
}


void BranchTree::StartShake(GameEngineState* _Parent)
{
	IsShaked = false;

	ChangeAnimation("Shake");
	SFXFunction::PlaySFX("SFX_TreeShake.wav");
}

void BranchTree::UpdateShake(float _Delta, GameEngineState* _Parent)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 하지 않습니다.");
		return;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		State.ChangeState(EBRANCHTREESTATE::Idle);
		return;
	}
}

void BranchTree::UpdateBranch(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		isGauging = true;

		ShakingTime += _Delta;
		if (ShakingTime > NextFallBranchTime)
		{
			FallBranch();
			IsShaked = true;	

			PrevFallBranchTime = NextFallBranchTime;

			if (1 == BranchCount)
			{
				NextFallBranchTime = BranchTotalTime;
			}
			else
			{
				NextFallBranchTime += DropCoolTime;
			}

			if (0 == BranchCount)
			{
				if (nullptr == InteractiveCol)
				{
					MsgBoxAssert("충돌체가 존재하지 않습니다.");
					return;
				}

				InteractiveCol->Off();

				isGauging = false;
			}
		}
	}
	else
	{
		if (ShakingTime > PrevFallBranchTime)
		{
			ShakingTime -= _Delta;
			
			if (ShakingTime <= PrevFallBranchTime)
			{
				isGauging = false;
				ShakingTime = PrevFallBranchTime;
			}
		}
	}

	if (true == isGauging)
	{
		if (false == Gauge.IsOn())
		{
			Gauge.On();
		}

		const float TimeRatio = ShakingTime / BranchTotalTime;
		Gauge.SetGauge(TimeRatio);
	}
	else
	{
		if (true == Gauge.IsOn())
		{
			Gauge.Off();
		}
	}
}


void BranchTree::FallBranch()
{
	DropBranchItem();
	EraseBranch();
}

void BranchTree::EraseBranch()
{
	--BranchCount;
	BranchRenderers[BranchCount]->Off();
}

void BranchTree::DropBranchItem()
{
	const std::shared_ptr<BackDrop_PlayLevel>& MainBackDropPtr = PlayLevel::GetPlayLevelPtr()->GetBackDropPtr();
	if (nullptr == MainBackDropPtr)
	{
		MsgBoxAssert("배경 매니저 포인터가 NUll을 가리킵니다.");
		return;
	}

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GlobalValue::GetSeedValue());

	const float MinRange = 5.0f;
	const float MaxRange = 25.0f;

	const float4 RandomFallingPosition = RandomClass.RandomVectorBox2D(MinRange, MaxRange, MinRange, MaxRange);
	const float4 FallingPosition = Transform.GetLocalPosition() + RandomFallingPosition;
	MainBackDropPtr->CreateItem("Branch_Collect", FallingPosition, 1, 80.0f);
}