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
bool ContentsEvent::HasWitchBroom = false;
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
	ToolData[static_cast<int>(ETOOLTYPE::Dragonfly)] = false;
	ToolData[static_cast<int>(ETOOLTYPE::FeaturePan)] = true;

	HasWitchBroom = true;

	CreateQuest<ContentsEvent::Letter_Read>("Letter_Read");
	CreateQuest<ContentsEvent::House_Dust>("House_Dust");
	CreateQuest<ContentsEvent::Craft_Potion>("Craft_Potion");
	CreateQuest<ContentsEvent::Repair_Extractor>("Repair_Extractor");

	CreateQuest<ContentsEvent::Aurea_Find>("Aurea_Find");
	CreateQuest<ContentsEvent::Aurea_Cure>("Aurea_Cure");

	CreateQuest<ContentsEvent::Crow_Meet>("Crow_Meet");
	CreateQuest<ContentsEvent::Dian_Catalogue>("Dian_Catalogue");
	CreateQuest<ContentsEvent::Dian_BadWeedPotion>("Dian_BadWeedPotion");
	CreateQuest<ContentsEvent::Dian_Cracker>("Dian_Cracker");
	CreateQuest<ContentsEvent::Craft_Cracker_Potion>("Craft_Cracker_Potion");
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