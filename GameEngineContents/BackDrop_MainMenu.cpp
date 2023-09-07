#include "PreCompile.h"
#include "BackDrop_MainMenu.h"

#include "GlobalUtils.h"

#include "Scenery.h"
#include "Props.h"

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
	CreateProps(CurLevel);
}

void BackDrop_MainMenu::CreateScenery(class GameEngineLevel* _CurLevel)
{
	vecScenery.reserve(10);

	std::shared_ptr<Scenery> Layor1 = _CurLevel->CreateActor<Scenery>(EUPDATEORDER::Objects);
	Layor1->SetSprite("Parallax_Layer1.png");
	Layor1->SetRenderOrder(ERENDERORDER::Scenery_0);
	Layor1->SetWorldPosition(Layer1LeftTopPosition, ERENDER_PIVOT_LOCATION::LeftTop);
	Layor1->SetMoveDirection(0.0f);
	Layor1->SetMoveRatio(0.0f);
	vecScenery.push_back(Layor1);

	std::shared_ptr<Scenery> Layor2 = _CurLevel->CreateActor<Scenery>(EUPDATEORDER::Objects);
	Layor2->SetSprite("Parallax_Layer3.png");
	Layor2->SetRenderOrder(ERENDERORDER::Scenery_1);
	Layor2->SetWorldPosition(Layer3LeftTopPosition, ERENDER_PIVOT_LOCATION::LeftTop);
	Layor2->SetMoveDirection(float4::LEFT);
	Layor2->SetMoveRatio(1.2f);
	vecScenery.push_back(Layor2);

	std::shared_ptr<Scenery> Layor3 = _CurLevel->CreateActor<Scenery>(EUPDATEORDER::Objects);
	Layor3->SetSprite("Parallax_Layer5.png");
	Layor3->SetRenderOrder(ERENDERORDER::Scenery_2);
	Layor3->SetWorldPosition(Layer5LeftTopPosition, ERENDER_PIVOT_LOCATION::LeftTop);
	Layor3->SetMoveDirection(float4::LEFT);
	Layor3->SetMoveRatio(0.8f);
	vecScenery.push_back(Layor3);

	std::shared_ptr<Scenery> Layor4 = _CurLevel->CreateActor<Scenery>(EUPDATEORDER::Objects);
	Layor4->SetSprite("Parallax_Layer6.png");
	Layor4->SetRenderOrder(ERENDERORDER::Scenery_3);
	Layor4->SetWorldPosition(Layer6LeftTopPosition, ERENDER_PIVOT_LOCATION::LeftTop);
	Layor4->SetMoveDirection(float4::LEFT);
	Layor4->SetMoveRatio(0.5f);
	vecScenery.push_back(Layor4);

	std::shared_ptr<Scenery> Layor5 = _CurLevel->CreateActor<Scenery>(EUPDATEORDER::Objects);
	Layor5->SetSprite("Parallax_Layer8.png");
	Layor5->SetRenderOrder(ERENDERORDER::Scenery_4);
	Layor5->SetWorldPosition(Layer8LeftTopPosition, ERENDER_PIVOT_LOCATION::LeftTop);
	Layor5->SetMoveDirection(float4::RIGHT);
	Layor5->SetMoveRatio(0.2f);
	vecScenery.push_back(Layor5);

	std::shared_ptr<Scenery> Layor10 = _CurLevel->CreateActor<Scenery>(EUPDATEORDER::Objects);
	Layor10->SetSprite("Parallax_Layer10_2.png");
	Layor10->SetRenderOrder(ERENDERORDER::Scenery_6);
	Layor10->SetWorldPosition(Layer10LeftTopPosition, ERENDER_PIVOT_LOCATION::LeftTop);
	Layor10->SetMoveDirection(0.0f);
	Layor10->SetMoveRatio(0.0f);
	vecScenery.push_back(Layor10);
}

void BackDrop_MainMenu::CreateProps(class GameEngineLevel* _CurLevel)
{
	vecProps.reserve(5);

	std::shared_ptr<Props> Props0 = _CurLevel->CreateActor<Props>(EUPDATEORDER::Objects);
	Props0->CreateRenderer(ERENDERORDER::Prop_1);
	Props0->CreateAnimation("Hair","MainMenuHair", 0.1f);
	Props0->ChangeAnimation("Hair");

	float4 HairMovePoint = MainMenuHairSize.Half();
	HairMovePoint.Y *= -1.0f;
	Props0->SetWorldPosition(MainMenuHairLeftTopPosition + HairMovePoint);
	vecProps.push_back(Props0);


	std::shared_ptr<Props> Props1 = _CurLevel->CreateActor<Props>(EUPDATEORDER::Objects);
	Props1->CreateRenderer(ERENDERORDER::Prop_1);
	Props1->CreateAnimation("Clothes", "MainMenuClothes", 0.1f);
	Props1->ChangeAnimation("Clothes");

	std::shared_ptr<GameEngineTexture> ClothesTexture = GameEngineTexture::Find("MainMenuClothes_Idle_Body_Down_01.Png");
	if (nullptr == ClothesTexture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	float4 ClothScale = ClothesTexture->GetScale();
	ClothScale.Y *= -1.0f;
	Props1->SetWorldPosition(MainMenuClothLeftTopPosition + ClothScale.Half());
	vecProps.push_back(Props1);



	std::shared_ptr<Props> Props2 = _CurLevel->CreateActor<Props>(EUPDATEORDER::Objects);
	Props2->CreateRenderer(ERENDERORDER::Scenery_5);
	Props2->CreateAnimation("Flags", "MainMenuFlag", 0.1f);
	Props2->ChangeAnimation("Flags");

	std::shared_ptr<GameEngineTexture> FlagsTexture = GameEngineTexture::Find("MainMenuFlag_Idle_Body_Down_01.Png");
	if (nullptr == FlagsTexture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	float4 FlagScale = FlagsTexture->GetScale();
	FlagScale.Y *= -1.0f;
	Props2->SetWorldPosition(MainMenuFlagLeftTopPosition + FlagScale.Half());
	vecProps.push_back(Props2);
	

	std::shared_ptr<Props> Props3 = _CurLevel->CreateActor<Props>(EUPDATEORDER::Objects);
	Props3->CreateRenderer(ERENDERORDER::Scenery_5);
	Props3->CreateAnimation("MagicBack", "MainMenuMagicBack", 0.1f);
	Props3->ChangeAnimation("MagicBack");
	Props3->SetWorldPosition(MainMenuMagicOraCenterPosition);
	vecProps.push_back(Props3);


	std::shared_ptr<Props> Props4 = _CurLevel->CreateActor<Props>(EUPDATEORDER::Objects);
	Props4->CreateRenderer(ERENDERORDER::Prop_1);
	Props4->CreateAnimation("MagicFront2", "MainMenuMagicFront2", 0.1f);
	Props4->ChangeAnimation("MagicFront2");
	Props4->SetWorldPosition(MainMenuMagicFront2CenterPosition);
	vecProps.push_back(Props4);
}



void BackDrop_MainMenu::ReleaseCurrentLevelChildActor()
{
	for (size_t i = 0; i < vecScenery.size(); i++)
	{
		vecScenery[i]->ActorRelease();
	}

	vecScenery.clear();
}