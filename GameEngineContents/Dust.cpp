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
	CreateAndSetCollision(ECOLLISION::Entity, float4(60.0f), float4::ZERO, ColType::SPHERE2D);
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

void Dust::Init(std::string_view _DustSpriteName)
{
	ApplyDepth(Transform.GetLocalScale());
	RendererSetting(_DustSpriteName);
	ConversationSetting();
	StateSetting();
}

void Dust::RendererSetting(std::string_view _DustSpriteName)
{
	static constexpr const int RenderOrder = 0;

	InteractiveActor::m_Body = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	InteractiveActor::m_Body->SetSprite(_DustSpriteName);
	InteractiveActor::m_Body->Transform.AddLocalPosition(float4(0.0f, 0.0f, -5.0f));
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
				State.ChangeState(EDUSTSTATE::None);
			});
	}
}

void Dust::SetConversationData()
{
	ConversationDatas = 
	{
		{ { L"이렇게 갑자기?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"마녀 까마귀는 그렇게 말이 잘 통하는 편은 아니지." , ECONVERSATIONENTITY::Virgil, 1 ,{ConversationFont::Color_BLACK , GlobalValue::Font_JejuHanlasan}},
		 },
	};
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