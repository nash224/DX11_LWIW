#include "PreCompile.h"
#include "Conversation.h"

#include "Ellie.h"
#include "UIManager.h"
#include "UI_Conversation.h"


const float4 ConversationFont::Color_RED = float4(0.6f, 0.1f, 0.1f, 1.0f);
const float4 ConversationFont::Color_BLACK = float4(0.0f, 0.0f, 0.0f, 1.0f);
const ConversationFont ConversationFont::VigilDefaultFont = ConversationFont(ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan);
Conversation::Conversation()
{
	
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

void Conversation::SetStartConversationEvent(int _Topic, std::function<void()> _Function)
{
	const std::shared_ptr<Topic>& CurTopic = Topics[_Topic];
	if (nullptr == CurTopic)
	{
		MsgBoxAssert("존재하지 않는 주제에 이벤트를 설정하려 했습니다.");
		return;
	}

	CurTopic->Data[0].Event = _Function;
}

void Conversation::SetConversationEvent(int _Topic, int _index, std::function<void()> _Function)
{
	const std::shared_ptr<Topic>& CurTopic = Topics[_Topic];
	if (nullptr == CurTopic)
	{
		MsgBoxAssert("존재하지 않는 주제에 이벤트를 설정하려 했습니다.");
		return;
	}

	CurTopic->Data[_index].Event = _Function;
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


#pragma region StartConverse

void Conversation::StartConversation(int _ConversationType)
{
	CurTopic = FindTopic(_ConversationType);
	CurLine = 0;

	const std::shared_ptr<UIManager>& ManagerPtr = PlayLevel::GetPlayLevelPtr()->GetUIManagerPtr();
	ManagerPtr->UseUIComponent();
	ManagerPtr->GetConversationPtr()->StartConversation(CurTopic->EntitySpriteName, CurTopic->Default_Npc_Sprite_Index, CurTopic->Elli_First_Sprite_Index);

	ConverseLine();
}
#pragma endregion


#pragma region ConversationUpdate

void Conversation::UpdateConversation(float _Delta)
{
	if (nullptr == CurTopic)
	{
		return;
	}

	if (nullptr == PlayLevel::s_MainPlayLevel)
	{
		MsgBoxAssert("참조하지 못했습니다.");
		return;
	}

	const std::shared_ptr<UI_Conversation>& UIConversationPtr = PlayLevel::s_MainPlayLevel->UIManagerPtr->GetConversationPtr();

	bool isDoneConverse = (false == UIConversationPtr->IsConversation());

	bool isKeyDownSkip = (isDoneConverse && true == GameEngineInput::IsDown('T', UIConversationPtr.get()));
	if (isKeyDownSkip)
	{
		EndConversation();
		return;
	}

	bool isKeyDownNextConversation = (isDoneConverse && true == GameEngineInput::IsDown('Z', UIConversationPtr.get()));
	if (isKeyDownNextConversation)
	{
		NextConversationLine();
		return;
	}
}

#pragma endregion


void Conversation::NextConversationLine()
{
	const std::vector<ConversationData>& Data = CurTopic->Data;
	if (Data.empty())
	{
		EndConversation();
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

void Conversation::ConverseLine()
{
	if (nullptr == CurTopic)
	{
		MsgBoxAssert("주제를 정하지 않고 대화를 시도하려 했습니다.");
		return;
	}

	const std::shared_ptr<UIManager>& UIManagerPtr = PlayLevel::GetPlayLevelPtr()->GetUIManagerPtr();
	UIManagerPtr->GetConversationPtr()->ShowConversation(CurTopic->Data[CurLine]);

	CallLineEvent();
}

void Conversation::EndConversation()
{
	if (nullptr == PlayLevel::s_MainPlayLevel)
	{
		MsgBoxAssert("참조하지 못했습니다.");
		return;
	}

 	const std::shared_ptr<UIManager>& UIManagerPtr = PlayLevel::s_MainPlayLevel->GetUIManagerPtr();

	UIManagerPtr->GetConversationPtr()->EndConversation();
	UIManagerPtr->DoneUIComponent();

	std::shared_ptr<Topic> TempTopic = CurTopic;
	CallEndConversationEvent();

	if (TempTopic == CurTopic)
	{
		CurTopic = nullptr;
	}
}

void Conversation::CallLineEvent()
{
	const ConversationData& LineData = CurTopic->Data[CurLine];
	if (nullptr != LineData.Event)
	{
		LineData.Event();
	}
}

void Conversation::CallEndConversationEvent()
{
	if (nullptr != CurTopic->EndEvent)
	{
		CurTopic->EndEvent();
	}
}

void Conversation::Release()
{
	Topics.clear();
	CurTopic = nullptr;
}