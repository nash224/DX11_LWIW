#include "PreCompile.h"
#include "Conversation.h"

#include "Ellie.h"
#include "UIManager.h"


Conversation::Conversation()
{
	GameEngineInput::AddInputObject(this);
}



void Conversation::CreateTopic(int _ConversationType, const std::vector<ConversationData>& _Topic, std::string_view _SpriteName)
{
	std::shared_ptr<Topic> topic = std::make_shared<Topic>();
	topic->Data = _Topic;
	topic->EntitySpriteName = _SpriteName;

	Topics.insert(std::make_pair(_ConversationType, topic));
}

const std::shared_ptr<Topic> Conversation::FindTopic(int _ConversationType)
{
	const std::shared_ptr<Topic>& topic = Topics.find(_ConversationType)->second;
	if (nullptr == topic)
	{
		MsgBoxAssert("존재하지 않는 주제를 반환하려 했습니다.");
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
	// UI

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