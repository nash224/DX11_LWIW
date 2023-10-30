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

	m_ConversationInfo.UpdateConversation(_Delta);
}

void NPCEntity::Release()
{
	InteractiveActor::Release();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void NPCEntity::InteractWithEllie(int _Topic)
{
	m_ConversationInfo.StartConversation(_Topic);
}