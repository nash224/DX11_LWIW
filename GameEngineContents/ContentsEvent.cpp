#include "PreCompile.h"
#include "ContentsEvent.h"

class EventDataCreator
{
public:
	EventDataCreator()
	{
		ContentsEvent::Init();
	}

	~EventDataCreator()
	{
		ContentsEvent::Release();
	}
};


std::vector<bool> ContentsEvent::ToolData;
std::map<int, std::shared_ptr<ContentsEvent::QuestUnitBase>> ContentsEvent::QuestData;

EventDataCreator EventDataInit;

ContentsEvent::ContentsEvent() 
{
}

ContentsEvent::~ContentsEvent() 
{
}

void ContentsEvent::Init()
{
	ToolData.resize(static_cast<int>(ETOOLTYPE::Nothing));
	ToolData[static_cast<int>(ETOOLTYPE::Gloves)] = true;
	ToolData[static_cast<int>(ETOOLTYPE::Dragonfly)] = true;
	ToolData[static_cast<int>(ETOOLTYPE::FeaturePan)] = true;


	CreateQuest<ContentsEvent::Crow_Meet>(EEVENTTYPE::Crow_Meet);
	CreateQuest<ContentsEvent::Dian_Quest_1>(EEVENTTYPE::Dian_Quest_1);
	CreateQuest<ContentsEvent::Dian_Quest_2>(EEVENTTYPE::Dian_Quest_2);
	CreateQuest<ContentsEvent::Dian_Quest_3>(EEVENTTYPE::Dian_Quest_3);
	CreateQuest<ContentsEvent::Dian_Cracker>(EEVENTTYPE::Dian_Cracker);
	CreateQuest<ContentsEvent::Dian_Quest_5>(EEVENTTYPE::Dian_Quest_5);
}

const std::shared_ptr<ContentsEvent::QuestUnitBase> ContentsEvent::FindQuest(int _Enum)
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = QuestData.find(static_cast<int>(EEVENTTYPE::Crow_Meet))->second;
	if (nullptr == Quest)
	{
		return nullptr;
	}

	return Quest;
}



void ContentsEvent::Release()
{
	ToolData.clear();
	QuestData.clear();
}

