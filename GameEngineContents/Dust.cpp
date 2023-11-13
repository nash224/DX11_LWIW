#include "PreCompile.h"
#include "Dust.h"

#include "UIManager.h"

#include "DustFx.h"

Dust::Dust() 
{
}

Dust::~Dust() 
{
}


void Dust::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, float4(90.0f), float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void Dust::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	AboutConversation.UpdateConversation(_Delta);
	State.Update(_Delta);
}

void Dust::Release()
{
	StaticEntity::Release();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Dust::Init(std::string_view _DustSpriteName, bool _isGroundDust /*= false*/)
{
	if (true == _isGroundDust)
	{
		const float Depth = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::GroundDust);
		Transform.AddLocalPosition(float4(0.0f, 0.0f, Depth));
	}
	else
	{
		ApplyDepth(Transform.GetLocalPosition());
	}
	RendererSetting(_DustSpriteName);
	ConversationSetting();
	StateSetting();
}

void Dust::AddDepth(float _PlusDepth)
{
	Transform.AddLocalPosition(float4(0.0f, 0.0f, _PlusDepth));
}

void Dust::RendererSetting(std::string_view _DustSpriteName)
{
	static constexpr const int RenderOrder = 0;

	InteractiveActor::m_Body = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	InteractiveActor::m_Body->SetSprite(_DustSpriteName);
	InteractiveActor::m_Body->Transform.AddLocalPosition(float4(0.0f, 0.0f, -2.0f));
}


void Dust::ConversationSetting()
{
	{
		Topic AboutTopic;

		AboutTopic.Data.reserve(64);
		AboutTopic.Data = ConversationDatas;

		AboutTopic.Data.shrink_to_fit();
		AboutConversation.CreateTopic(EDUSTTOPICTYPE::About, AboutTopic);

		AboutConversation.SetConversationEndEvent(EDUSTTOPICTYPE::About, [&]()
			{
				if (nullptr != EndEvent)
				{
					EndEvent();
				}

				State.ChangeState(EDUSTSTATE::None);
			});
	}
}

void Dust::SetConversationData(const std::vector<ConversationData>& _ConversationDatas)
{
	ConversationDatas = _ConversationDatas;
}

void Dust::SetEndEvnet(std::function<void()> _EndEvent)
{
	EndEvent = _EndEvent;
}


void Dust::StateSetting()
{
	CreateStateParameter IdleState;
	IdleState.Stay = std::bind(&Dust::UpdateIdle, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EDUSTSTATE::Idle, IdleState);

	CreateStateParameter RemoveState;
	RemoveState.Start = std::bind(&Dust::StartRemove, this, std::placeholders::_1);
	RemoveState.Stay = std::bind(&Dust::UpdateRemove, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EDUSTSTATE::Remove, RemoveState);

	CreateStateParameter ConverseState;
	ConverseState.Start = std::bind(&Dust::StartConverse, this, std::placeholders::_1);
	ConverseState.End = std::bind(&Dust::EndConverse, this, std::placeholders::_1);
	State.CreateState(EDUSTSTATE::Converse, ConverseState);

	State.ChangeState(EDUSTSTATE::Idle);
}



void Dust::StartRemove(GameEngineState* _Parent)
{
	if (nullptr != UIManager::MainUIManager)
	{
		UIManager::MainUIManager->UseUIComponent();
	}

	InteractiveActor::m_Body->Off();

	std::shared_ptr<DustFx> Dust = GetLevel()->CreateActor<DustFx>(EUPDATEORDER::Objects);
	Dust->Init(Transform.GetLocalPosition());
}

void Dust::StartConverse(GameEngineState* _Parent)
{
	if (nullptr != UIManager::MainUIManager)
	{
		UIManager::MainUIManager->DoneUIComponent();
	}

	AboutConversation.StartConversation(EDUSTTOPICTYPE::About);
}

void Dust::UpdateIdle(float _DeltaTime, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		State.ChangeState(EDUSTSTATE::Remove);
	}
}

void Dust::UpdateRemove(float _DeltaTime, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > RemoveDustTime)
	{
		State.ChangeState(EDUSTSTATE::Converse);
	}
}

void Dust::EndConverse(GameEngineState* _Parent)
{
	Death();
}