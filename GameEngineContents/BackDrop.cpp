#include "PreCompile.h"
#include "BackDrop.h"



#include "GlobalValue.h"


#include "Scenery.h"
#include "TestActor2.h"


BackDrop::BackDrop() 
	: LevelCount(0)
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

void BackDrop::LevelStart(GameEngineLevel* _NextLevel)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CreateBackDropPerLevel(CurLevel);
}

void BackDrop::LevelEnd(GameEngineLevel* _NextLevel)
{

}



void BackDrop::SetLevelType(int _LevelType)
{
	if (_LevelType <= static_cast<int>(ELEVELTYPE::None) || _LevelType >= static_cast<int>(ELEVELTYPE::Max))
	{
		MsgBoxAssert("레벨 타입을 지정해주지 않았습니다.");
	}

	LevelCount = _LevelType;
}




void BackDrop::CreateBackDropPerLevel(GameEngineLevel* _CurLevel)
{
	switch (static_cast<ELEVELTYPE>(LevelCount))
	{
	case ELEVELTYPE::None:
		break;
	case ELEVELTYPE::MainMenu:
		CreateMainMenuBackDrop(_CurLevel);
		break;
	case ELEVELTYPE::Misson0_Part1:
		break;
	case ELEVELTYPE::Max:
		break;
	default:
		break;
	}
}

void BackDrop::CreateMainMenuBackDrop(GameEngineLevel* _CurLevel)
{
	std::shared_ptr<Scenery> Layor10 = _CurLevel->CreateActor<Scenery>(EUPDATEORDER::Objects);
	Layor10->SetSprite("Parallax_Layer10_2.png");
	Layor10->SetRenderOrder(ERENDERORDER::Scenery_0);
	Layor10->SetWorldPosition(Layer10LeftTopPosition, ERENDER_PIVOT_LOCATION::LeftTop);
	Layor10->SetMoveDirection(0.0f);
	Layor10->SetMoveRatio(0.0f);
	
	/*vecMainMenuScenery*/

	/*Senery = Create();*/

}