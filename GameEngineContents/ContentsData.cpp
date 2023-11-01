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
		ContentsData::Release();
	}
};




std::vector<bool> ContentsData::ToolData;
std::map<int, std::shared_ptr<ContentsData::QuestUnitBase>> ContentsData::QuestData;

EventDataCreator EventDataInit;

ContentsData::ContentsData() 
{
}

ContentsData::~ContentsData() 
{
}

void ContentsData::Init()
{
	ToolData.resize(static_cast<int>(ETOOLTYPE::Nothing));
	ToolData[static_cast<int>(ETOOLTYPE::Gloves)] = true;
	ToolData[static_cast<int>(ETOOLTYPE::Dragonfly)] = false;
	ToolData[static_cast<int>(ETOOLTYPE::FeaturePan)] = true;


	CreateQuest<ContentsData::Crow_Meet>(EEVENTTYPE::Crow_Meet);
	CreateQuest<ContentsData::Dian_Quest_1>(EEVENTTYPE::Dian_Quest_1);
	CreateQuest<ContentsData::Dian_Quest_2>(EEVENTTYPE::Dian_Quest_2);
	CreateQuest<ContentsData::Dian_Quest_3>(EEVENTTYPE::Dian_Quest_3);
	CreateQuest<ContentsData::Dian_Quest_4>(EEVENTTYPE::Dian_Quest_4);
	CreateQuest<ContentsData::Dian_Quest_5>(EEVENTTYPE::Dian_Quest_5);
}

const std::shared_ptr<ContentsData::QuestUnitBase> ContentsData::FindQuest(int _Enum)
{
	const std::shared_ptr<ContentsData::QuestUnitBase>& Quest = QuestData.find(static_cast<int>(EEVENTTYPE::Crow_Meet))->second;
	if (nullptr == Quest)
	{
		return nullptr;
	}

	return Quest;
}



void ContentsData::Release()
{
	ToolData.clear();
	QuestData.clear();
}


bool ContentsData::Crow_Meet::CheckPrerequisiteQuest()
{
	return true;
}

bool ContentsData::Dian_Quest_1::CheckPrerequisiteQuest()
{
	return true;
}

bool ContentsData::Dian_Quest_2::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsData::QuestUnitBase>& Quest1 = ContentsData::FindQuest(EEVENTTYPE::Dian_Quest_1);
	if (nullptr == Quest1)
	{
		MsgBoxAssert("존재하지 않는 퀘스트입니다.");
		return;
	}

	if (true == Quest1->isQuestComplete())
	{
		return true;
	}

	return false;
}

bool ContentsData::Dian_Quest_3::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsData::QuestUnitBase>& Quest2 = ContentsData::FindQuest(EEVENTTYPE::Dian_Quest_1);
	if (nullptr == Quest2)
	{
		MsgBoxAssert("존재하지 않는 퀘스트입니다.");
		return;
	}

	if (true == Quest2->isQuestComplete())
	{
		return true;
	}

	return false;
}

bool ContentsData::Dian_Quest_4::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsData::QuestUnitBase>& Quest3 = ContentsData::FindQuest(EEVENTTYPE::Dian_Quest_1);
	if (nullptr == Quest3)
	{
		MsgBoxAssert("존재하지 않는 퀘스트입니다.");
		return;
	}

	if (true == Quest3->isQuestComplete())
	{
		return true;
	}

	return false;
}

bool ContentsData::Dian_Quest_5::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsData::QuestUnitBase>& Quest4 = ContentsData::FindQuest(EEVENTTYPE::Dian_Quest_1);
	if (nullptr == Quest4)
	{
		MsgBoxAssert("존재하지 않는 퀘스트입니다.");
		return;
	}

	if (true == Quest4->isQuestComplete())
	{
		return true;
	}

	return false;
}
