#include "PreCompile.h"
#include "ContentsEvent.h"



bool ContentsEvent::Letter_Read::CheckPrerequisiteQuest()
{
	return !isQuestCompleted;
}

bool ContentsEvent::House_Dust::CheckPrerequisiteQuest()
{
	return !isQuestCompleted;
}