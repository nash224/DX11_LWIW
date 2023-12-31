#include "PreCompile.h"
#include "AlertManager.h"

#include "UI_Alert_Enter.h"
#include "UI_Alert_Quest.h"

#include "PlayLevel.h"

bool AlertManager::isAlerting = false;
AlertManager::AlertManager() 
{
}

AlertManager::~AlertManager() 
{
}


void AlertManager::RegisterAlert(const AlertData& _Data)
{
	const std::shared_ptr<AlertData>& data = std::make_shared<AlertData>(_Data);

	if (EALERTTYPE::Enter == data->Type)
	{
		Data.push_front(data);
	}
	else
	{
		Data.push_back(data);
	}
}


void AlertManager::Update(float _Delta)
{
	if (true == Data.empty())
	{
		return;
	}

	if (false == isAlerting)
	{
		const std::shared_ptr<AlertData>& data = Data.front();
		AlertCall(data);
		Data.pop_front();
	}
}

void AlertManager::AlertCall(const std::shared_ptr<AlertData>& _Data)
{
	switch (_Data->Type)
	{
	case EALERTTYPE::Enter:
		UI_Alert_Enter::AlertLevelEnter(PlayLevel::GetCurLevel(), _Data->AlertName);
		break;
	case EALERTTYPE::QuestAccept:
		UI_Alert_Quest::CallAlertQuest(PlayLevel::GetCurLevel(), _Data->AlertName, EALERTTYPE::QuestAccept);
		break;
	case EALERTTYPE::QuestClear:
		UI_Alert_Quest::CallAlertQuest(PlayLevel::GetCurLevel(), _Data->AlertName, EALERTTYPE::QuestClear);
		break;
	case EALERTTYPE::Tutorial:
		break;
	case EALERTTYPE::None:
	{
		MsgBoxAssert("해당옵션은 존재하지 않습니다.");
		return;
	}
		break;
	default:
		break;
	}

	isAlerting = true;
}
