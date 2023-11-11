#include "PreCompile.h"
#include "Conversation.h"

#include "Ellie.h"
#include "UIManager.h"
#include "UI_Conversation.h"


const float4 ConversationFont::Color_RED = float4(0.6f, 0.1f, 0.1f, 1.0f);
const float4 ConversationFont::Color_BLACK = float4(0.0f, 0.0f, 0.0f, 1.0f);
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
		MsgBoxAssert("�������� �ʴ� �����Դϴ�.");
		return nullptr;
	}

	return topic;
}


void Conversation::SetConversationEvent(int _Topic, int _index, std::function<void()> _Function)
{
	std::shared_ptr<Topic> CurTopic = Topics[_Topic];
	if (nullptr == CurTopic)
	{
		MsgBoxAssert("�������� �ʴ� ������ �̺�Ʈ�� �����Ϸ� �߽��ϴ�.");
		return;
	}

	CurTopic->Data[_index].Event = _Function;
}

void Conversation::SetConversationEndEvent(int _Topic, std::function<void()> _Function)
{
 	if (nullptr == Topics[_Topic])
	{
		MsgBoxAssert("�������� �ʴ� ������ �̺�Ʈ�� �����Ϸ� �߽��ϴ�.");
		return;
	}

	Topics[_Topic]->EndEvent = _Function;
}



void Conversation::StartConversation(int _ConversationType)
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	if (nullptr == UI_Conversation::MainConversationUI)
	{
		MsgBoxAssert("��ȭ UI�� �������� �ʽ��ϴ�.");
		return;
	}

	UIManager::MainUIManager->UseUIComponent();

	CurTopic = FindTopic(_ConversationType);
	CurLine = 0;

	UI_Conversation::MainConversationUI->StartConversation(CurTopic->EntitySpriteName, CurTopic->Default_Npc_Sprite_Index);

	ConverseLine();
}

void Conversation::ConverseLine()
{
	if (nullptr == CurTopic)
	{
		MsgBoxAssert("������ ������ �ʰ� ��ȭ�� �õ��Ϸ� �߽��ϴ�.");
		return;
	}

	if (nullptr == UI_Conversation::MainConversationUI)
	{
		MsgBoxAssert("��ȭ UI�� �������� �ʽ��ϴ�.");
		return;
	}

	UI_Conversation::MainConversationUI->ShowConversation(CurTopic->Data[CurLine]);

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
		EndConversation();
		return;
	}

	ConverseLine();
}

void Conversation::ConversationBTWEvent()
{
	const ConversationData& LineData = CurTopic->Data[CurLine];
	if (nullptr != LineData.Event)
	{
		LineData.Event();
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
		MsgBoxAssert("UI �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	if (nullptr == UI_Conversation::MainConversationUI)
	{
		MsgBoxAssert("��ȭ UI�� �������� �ʽ��ϴ�.");
		return;
	}


	UI_Conversation::MainConversationUI->EndConversation();

	UIManager::MainUIManager->DoneUIComponent();
	
	std::shared_ptr<Topic> TempTopic = CurTopic;
	EndConversationEvent();

	if (TempTopic == CurTopic)
	{
		CurTopic = nullptr;
	}
}


void Conversation::UpdateConversation(float _Delta)
{
	if (nullptr == CurTopic)
	{
		return;
	}

	bool IsEndPrintMessage = (false == UI_Conversation::MainConversationUI->IsConversation());

	bool isKeyDownSkip = (IsEndPrintMessage && true == GameEngineInput::IsDown('T', this));
	if (isKeyDownSkip)
	{
		EndConversation();
		return;
	}


	bool isKeyDownNextConversation = (IsEndPrintMessage && true == GameEngineInput::IsDown('Z', this));
	if (isKeyDownNextConversation)
	{
		NextConversationLine();
		return;
	}
}