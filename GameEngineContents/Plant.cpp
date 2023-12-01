#include "PreCompile.h"
#include "Plant.h"

Plant::Plant() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_PlantsRootUp_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Plant");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

Plant::~Plant() 
{
}


void Plant::Start()
{
	InteractiveActor::Start();

	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Near, ECOLLECTION_METHOD::RootUp, ETOOLTYPE::Gloves);
	InteractiveActor::SetNearInteractivePositionAndRange(float4::ZERO, 6.0f);

	StateSetting();
}

void Plant::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
	State.Update(_Delta);
}

void Plant::Release()
{
	InteractiveActor::Release();
}


void Plant::StateSetting()
{
	CreateStateParameter IdleState;
	IdleState.Start = std::bind(&Plant::StartIdle, this, std::placeholders::_1);
	IdleState.Stay = std::bind(&Plant::UpdateIdle, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EPLANTSTATE::Idle, IdleState);

	CreateStateParameter UpRootState;
	UpRootState.Start = std::bind(&Plant::StartUpRoot, this, std::placeholders::_1);
	UpRootState.Stay = std::bind(&Plant::UpdateUpRoot, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EPLANTSTATE::UpRoot, UpRootState);
}


void Plant::ChangePlantAnimation(std::string_view _Name)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("존재하지않는 렌더러를 사용하려 했습니다.");
		return;
	}
	
	BodyRenderer->ChangeAnimation(_Name);
}

void Plant::StartIdle(GameEngineState* _Parent)
{
	ChangePlantAnimation("Idle");
}

void Plant::StartUpRoot(GameEngineState* _Parent)
{
	SetInteractionButtonType(EINTERACTION_BUTTONTYPE::None);
	InteractiveCol->Off();

	SFXFunction::PlaySFX("SFX_PlantsRootUp_01.wav");
	ChangePlantAnimation("UpRoot");
}


void Plant::UpdateIdle(float _Delta, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		State.ChangeState(EPLANTSTATE::UpRoot);
		return;
	}
}

void Plant::UpdateUpRoot(float _Delta, GameEngineState* _Parent)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		RootInternal();
	}
}