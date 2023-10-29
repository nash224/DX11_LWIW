#include "PreCompile.h"
#include "Conversation.h"

#include "Ellie.h"
#include "UIManager.h"


Conversation::Conversation()
{
	GameEngineInput::AddInputObject(this);
}


void Conversation::Init()
{
	
}

void Conversation::RendererSetting()
{

}


void Conversation::CreateConversationData(int _ConversationType, const std::vector<ConversationData>& _Topic)
{
	ConversationDatas.insert(std::make_pair(_ConversationType, _Topic));
}

const std::vector<ConversationData>& Conversation::FindData(int _ConversationType)
{
	const std::vector<ConversationData>& topic = ConversationDatas.find(_ConversationType)->second;
	if (topic.empty())
	{
		MsgBoxAssert("�������� �ʴ� �����͸� ��ȯ�Ϸ� �߽��ϴ�.");
		return topic;
	}

	return topic;
}


void Conversation::StartConversation(int _ConversationType)
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	UIManager::MainUIManager->UseUIComponent();

	CurTopic = FindData(_ConversationType);

	CurLine = 0;
}


void Conversation::NextConversation()
{
	if (CurTopic.empty())
	{
		return;
	}

	bool isLast = (CurLine == static_cast<int>(CurTopic.size()));
	if (isLast)
	{
		EndConversation();
		return;
	}

	if (nullptr != CurTopic[CurLine].Event)
	{
		ConversationEvent();
	}

	++CurLine;
}

void Conversation::ConversationEvent()
{
	CurTopic[CurLine].Event();
}

void Conversation::EndConversation()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	UIManager::MainUIManager->DoneUIComponent();
}


void Conversation::UpdateConversation(float _Delta)
{
	if (CurTopic.empty())
	{
		return;
	}

	ConversationTime += _Delta;

	if (ConversationTime > Interaction_Cooldown)
	{
		if (true == GameEngineInput::IsDown('Z', this))
		{
			NextConversation();
			ConversationTime = 0.0f;
		}
	}
}