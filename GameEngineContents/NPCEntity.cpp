#include "PreCompile.h"
#include "NPCEntity.h"


NPCEntity::NPCEntity() 
{
}

NPCEntity::~NPCEntity() 
{
}


void NPCEntity::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
	NPCConversation.UpdateConversation(_Delta);
}

void NPCEntity::Release()
{
	InteractiveActor::Release();
	NPCConversation.Release();
}


void NPCEntity::ConverseWithEllie(int _Topic)
{ 
	NPCConversation.StartConversation(_Topic);
}