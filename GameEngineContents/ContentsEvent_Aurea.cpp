#include "PreCompile.h"
#include "ContentsEvent.h"

#include "Ellie.h"
#include "UI_Inventory.h"



bool ContentsEvent::Aurea_Find::CheckPrerequisiteQuest()
{
	return true;
}

bool ContentsEvent::Aurea_UnCurse::CheckPrerequisiteQuest()
{
	return true;
}


bool ContentsEvent::Aurea_Curse::CheckPrerequisiteQuest()
{
	if (nullptr != UI_Inventory::MainInventory)
	{
		if (true == UI_Inventory::MainInventory->IsItem("UncurseCandy"))
		{
			return true;
		}
	}

	return false;
}
