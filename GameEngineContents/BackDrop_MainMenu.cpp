#include "PreCompile.h"
#include "BackDrop_MainMenu.h"

#include "GlobalUtils.h"

#include "Scenery.h"
#include "Prop.h"

BackDrop_MainMenu::BackDrop_MainMenu() 
{
}

BackDrop_MainMenu::~BackDrop_MainMenu() 
{
}


void BackDrop_MainMenu::Start()
{

}

void BackDrop_MainMenu::Update(float _Delta)
{
	
}

void BackDrop_MainMenu::LevelStart(class GameEngineLevel* _NextLevel)
{
	CreateBackDrop();
}

void BackDrop_MainMenu::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////




void BackDrop_MainMenu::CreateBackDrop()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CreateScenery(CurLevel);
	CreateProp(CurLevel);
}

void BackDrop_MainMenu::CreateScenery(class GameEngineLevel* _CurLevel)
{

}

void BackDrop_MainMenu::CreateProp(class GameEngineLevel* _CurLevel)
{
	vecProps.reserve(15);

	std::shared_ptr<Prop> Prop0 = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Prop0)
	{
		MsgBoxAssert("액터 생성을 실패하였습니다.");
		return;
	}

	Prop0->CreateRenderer(ETITLERENDERORDER::Back_);
	Prop0->SetSprite("Title_Train_Sky.png");
	Prop0->SetLocalPosition(float4::ZERO, EDIRECTION::LEFTTOP);


	std::shared_ptr<Prop> StarLight = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Prop0)
	{
		MsgBoxAssert("액터 생성을 실패하였습니다.");
		return;
	}

	StarLight->CreateRenderer(ETITLERENDERORDER::Star);
	StarLight->SetSprite("Title_train_star0.png");
	StarLight->SetLocalPosition(float4::ZERO, EDIRECTION::LEFTTOP);


	std::shared_ptr<Prop> StarLight = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Prop0)
	{
		MsgBoxAssert("액터 생성을 실패하였습니다.");
		return;
	}

	StarLight->CreateRenderer(ETITLERENDERORDER::Star);
	StarLight->CreateAutomatedAnimation("StarAni", "Title_train_star");
	StarLight->SetLocalPosition(float4::ZERO, EDIRECTION::LEFTTOP);




	//Prop0->ChangeAnimation();
	//Prop0->AutoSpriteSize(true, ratio);
	//Prop0->setlocation(pivotPos, LocalPosition);
	//
	//Prop0->createAutomatedAnimation();
	//Prop0->setlocation(pivotPos, LocalPosition);


}



void BackDrop_MainMenu::ReleaseCurrentLevelChildActor()
{
	for (size_t i = 0; i < vecScenery.size(); i++)
	{
		vecScenery[i]->ActorRelease();
	}

	vecScenery.clear();
}