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
std::map<std::string, std::shared_ptr<ContentsEvent::QuestUnitBase>> ContentsEvent::QuestData;

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


	CreateQuest<ContentsEvent::Aurea_Find>("Aurea_Find");
	CreateQuest<ContentsEvent::Aurea_UnCurse>("Aurea_UnCurse");
	CreateQuest<ContentsEvent::Aurea_Curse>("Aurea_Curse");

	CreateQuest<ContentsEvent::Crow_Meet>("Crow_Meet");
	CreateQuest<ContentsEvent::Dian_Quest_1>("Dian_Quest_1");
	CreateQuest<ContentsEvent::Dian_Quest_2>("Dian_Quest_2");
	CreateQuest<ContentsEvent::Dian_Quest_3>("Dian_Quest_3");
	CreateQuest<ContentsEvent::Dian_Cracker>("Dian_Cracker");
	
}

const std::shared_ptr<ContentsEvent::QuestUnitBase> ContentsEvent::FindQuest(std::string_view _QuestName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_QuestName);

	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = QuestData.find(UpperName)->second;
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

