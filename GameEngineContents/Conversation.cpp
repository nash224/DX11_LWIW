#include "PreCompile.h"
#include "Conversation.h"

#include "Ellie.h"
#include "UIManager.h"
#include "UI_Conversation.h"



Conversation::Conversation()
{
	GameEngineInput::AddInputObject(this);
}



void Conversation::CreateTopic(int _ConversationType, const Topic& _Topic)
{
	std::shared_ptr<Topic> topic = std::make_shared<Topic>(_Topic);

	Topics.insert(std::make_pair(_ConversationType, topic));
}

const std::shared_ptr<Topic> Conversation::FindTopic(int _ConversationType)
{
	const std::shared_ptr<Topic>& topic = Topics.find(_ConversationType)->second;
	if (nullptr == topic)
	{
		MsgBoxAssert("존재하지 않는 주제입니다.");
		return nullptr;
	}

	return topic;
}

void Conversation::SetConversationEndEvent(int _Topic, std::function<void()> _Function)
{
	if (nullptr == Topics[_Topic])
	{
		MsgBoxAssert("존재하지 않는 주제에 이벤트를 설정하려 했습니다.");
		return;
	}

	Topics[_Topic]->EndEvent = _Function;
}



void Conversation::StartConversation(int _ConversationType)
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI 매니저가 존재하지 않습니다.");
		return;
	}

	if (nullptr == UI_Conversation::MainConversationUI)
	{
		MsgBoxAssert("대화 UI가 존재하지 않습니다.");
		return;
	}

	UIManager::MainUIManager->UseUIComponent();

	CurTopic = FindTopic(_ConversationType);
	CurLine = 0;

	UI_Conversation::MainConversationUI->StartConversation(CurTopic->EntitySpriteName);

	ConverseLine();
}

void Conversation::ConverseLine()
{
	if (nullptr == CurTopic)
	{
		MsgBoxAssert("주제를 정하지 않고 대화를 시도하려 했습니다.");
		return;
	}

	if (nullptr == UI_Conversation::MainConversationUI)
	{
		MsgBoxAssert("대화 UI가 존재하지 않습니다.");
		return;
	}

	const ConversationData& Data =  CurTopic->Data[CurLine];
	UI_Conversation::MainConversationUI->ShowConversation(
		{ Data.ConversationEntity,
		Data.FileIndex,
		Data.Question,
		Data.Font });

	ConversationBTWEvent();
}

void Conversation::NextConversationLine()
{
	const std::vector<ConversationData>& Data = CurTopic->Data;

	if (Data.empty())
	{
		return;
	}

	++CurLine;

	bool isLast = (CurLine == static_cast<int>(Data.size()));
	if (isLast)
	{
		EndConversationEvent();
		EndConversation();
		return;
	}

	ConverseLine();
}

void Conversation::ConversationBTWEvent()
{
	if (nullptr != CurTopic->Data[CurLine].Event)
	{
		CurTopic->Data[CurLine].Event();
	}
}

void Conversation::EndConversationEvent()
{
	if (nullptr != CurTopic->EndEvent)
	{
		CurTopic->EndEvent();
	}
}

void Conversation::EndConversation()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI 매니저가 존재하지 않습니다.");
		return;
	}

	if (nullptr == UI_Conversation::MainConversationUI)
	{
		MsgBoxAssert("대화 UI가 존재하지 않습니다.");
		return;
	}


	UIManager::MainUIManager->DoneUIComponent();

	UI_Conversation::MainConversationUI->EndConversation();

	CurTopic = nullptr;
}


void Conversation::UpdateConversation(float _Delta)
{
	if (nullptr == CurTopic)
	{
		return;
	}

	ConversationTime += _Delta;

	if (ConversationTime > Interaction_Cooldown)
	{
		if (true == GameEngineInput::IsDown('Z', this))
		{
			NextConversationLine();
			ConversationTime = 0.0f;
		}
	}
}