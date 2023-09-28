#include "PreCompile.h"
#include "EventData.h"


std::vector<bool> EventData::ToolData;

EventData::EventData() 
{
}

EventData::~EventData() 
{
}



void EventData::Init()
{
	ToolData.resize(static_cast<int>(ETOOLTYPE::None));

	ToolData[static_cast<int>(ETOOLTYPE::Gloves)] = true;
	ToolData[static_cast<int>(ETOOLTYPE::FeaturePan)] = true;
	ToolData[static_cast<int>(ETOOLTYPE::Dragonfly)] = false;
}