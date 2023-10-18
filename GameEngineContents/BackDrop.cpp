#include "PreCompile.h"
#include "BackDrop.h"


#include "GlobalValue.h"


#include "Scenery.h"
#include "Prop.h"


BackDrop::BackDrop()
{
}

BackDrop::~BackDrop() 
{
}



void BackDrop::Start()
{
	
}

void BackDrop::Update(float _Delta)
{

}

void BackDrop::Release()
{
	
}

void BackDrop::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void BackDrop::LevelEnd(class GameEngineLevel* _NextLevel)
{
	vecProps.clear();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const float4& BackDrop::GetBackGroundScale() const
{
	return m_BackScale;
}