#include "PreCompile.h"
#include "AlertManager.h"

AlertManager::AlertManager() 
{
}

AlertManager::~AlertManager() 
{
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void AlertManager::RegisterAlert(const AlertData& _Data)
{
	const std::shared_ptr<AlertData>& data = std::make_shared<AlertData>(_Data);
	Data.push_back(data);
}


void AlertManager::Update(float _Delta)
{
	if (false == Data.empty())
	{
		return;
	}

	AlertTime -= _Delta;
	if (AlertTime < 0.0f)
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
		break;
	case EALERTTYPE::QuestAccept:
		break;
	case EALERTTYPE::QuestClear:
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
}
