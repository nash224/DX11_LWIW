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

	UIManager::MainUIManager->UseUIComponent();

	CurTopic = FindTopic(_ConversationType);

	CurLine = 0;
	ConverseLine();
}

void Conversation::ConverseLine()
{
	CurTopic->Data[CurLine].Question;
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

	ConverseLine();

	bool isLast = (CurLine == static_cast<int>(Data.size() - 1));
	if (isLast)
	{
		EndConversationEvent();
		EndConversation();
		return;
	}
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

	UIManager::MainUIManager->DoneUIComponent();

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