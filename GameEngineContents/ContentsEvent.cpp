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
std::vector<bool> ContentsEvent::EventData;
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

	EventData.resize(static_cast<int>(EEVENTTYPE::Max));
	for (int i = 0; i < EventData.size(); i++)
	{
		EventData[i] = false;
	}


	CreateQuest<ContentsEvent::Aurea_Find>(EQUESTTYPE::Aurea_Find);
	CreateQuest<ContentsEvent::Aurea_UnCurse>(EQUESTTYPE::Aurea_UnCurse);
	CreateQuest<ContentsEvent::Aurea_Curse>(EQUESTTYPE::Aurea_Curse);

	CreateQuest<ContentsEvent::Crow_Meet>(EQUESTTYPE::Crow_Meet);
	CreateQuest<ContentsEvent::Dian_Quest_1>(EQUESTTYPE::Dian_Quest_1);
	CreateQuest<ContentsEvent::Dian_Quest_2>(EQUESTTYPE::Dian_Quest_2);
	CreateQuest<ContentsEvent::Dian_Quest_3>(EQUESTTYPE::Dian_Quest_3);
	CreateQuest<ContentsEvent::Dian_Cracker>(EQUESTTYPE::Dian_Cracker);
	
}

const std::shared_ptr<ContentsEvent::QuestUnitBase> ContentsEvent::FindQuest(int _Enum)
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = QuestData.find(static_cast<int>(EQUESTTYPE::Crow_Meet))->second;
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

