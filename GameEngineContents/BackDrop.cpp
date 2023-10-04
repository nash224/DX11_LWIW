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

void BackDrop::LevelStart(GameEngineLevel* _NextLevel)
{
}

void BackDrop::LevelEnd(GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const float4& BackDrop::GetBackGroundScale() const
{
	return m_BackScale;
}



void BackDrop::ActorRelease()
{
	for (size_t i = 0; i < vecProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecProps.clear();


	for (size_t i = 0; i < vecScenery.size(); i++)
	{
		std::shared_ptr<Scenery> Object = vecScenery[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecScenery.clear();
} 