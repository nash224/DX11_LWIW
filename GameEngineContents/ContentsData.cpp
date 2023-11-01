#include "PreCompile.h"
#include "ContentsData.h"
#include "UIEnum.h"

#include<vector>


class EventDataCreator
{
public:
	EventDataCreator()
	{
		ContentsData::Init();
	}

	~EventDataCreator()
	{

	}
};


EventDataCreator EventDataInit;



std::vector<bool> ContentsData::ToolData;
std::map<int, std::shared_ptr<ContentsData::QuestUnitBase>> ContentsData::QuestData;
ContentsData::ContentsData() 
{
}

ContentsData::~ContentsData() 
{
}

void ContentsData::Init()
{
	ToolData.resize(3);
	ToolData[static_cast<int>(ETOOLTYPE::Gloves)] = true;
	ToolData[static_cast<int>(ETOOLTYPE::Dragonfly)] = false;
	ToolData[static_cast<int>(ETOOLTYPE::FeaturePan)] = true;

	CreateQuest(EEVENTTYPE::Crow_Meet);

	QuestData.find(static_cast<int>(EEVENTTYPE::Crow_Meet))->second->CheckPrerequisiteQuest();
	
}

void ContentsData::CreateQuest(int _Enum)
{
	std::shared_ptr<ContentsData::QuestUnitBase> questUnit = std::make_shared<ContentsData::QuestUnitBase>();
	QuestData.insert(std::make_pair(_Enum, questUnit));
}

bool ContentsData::QuestUnitBase::isQuestComplete() const
{
	return isQuestCompleted;
}


bool ContentsData::Dian_Quest_1::CheckPrerequisiteQuest()
{
	return true;
}