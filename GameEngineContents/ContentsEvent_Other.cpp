#include "PreCompile.h"
#include "ContentsEvent.h"



bool ContentsEvent::Letter_Read::CheckPrerequisiteQuest()
{
	return !isQuestCompleted;
}