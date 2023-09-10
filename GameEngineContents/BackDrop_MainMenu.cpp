#include "PreCompile.h"
#include "BackDrop_MainMenu.h"

#include "GlobalUtils.h"

#include "Scenery.h"
#include "Prop.h"
#include "ChainProp.h"
#include "MainMenu_Trains.h"

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

void BackDrop_MainMenu::Release()
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


void BackDrop_MainMenu::ActorRelease()
{
	for (size_t i = 0; i < vecProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("존재하지 않는 액터를 차조하려고 했습니다.");
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
			MsgBoxAssert("존재하지 않는 액터를 차조하려고 했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecScenery.clear();


	if (nullptr != m_MainMenu_Train)
	{
		m_MainMenu_Train->ActorRelease();
		m_MainMenu_Train = nullptr;
	}

	Death();
}

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


	{
		m_MainMenu_Train = CurLevel->CreateActor<MainMenu_Trains>(EUPDATEORDER::Objects);
		if (nullptr == m_MainMenu_Train)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		m_MainMenu_Train->Init();
	}
}

void BackDrop_MainMenu::CreateScenery(class GameEngineLevel* _CurLevel)
{

}

#pragma region Prop 생성

void BackDrop_MainMenu::CreateProp(class GameEngineLevel* _CurLevel)
{
	vecProps.reserve(15);

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Back_);
		Object->SetSprite("Title_Train_Sky.png");
		Object->SetLocalPosition(float4::ZERO, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Star);
		Object->CreateAutomatedAnimation("StarAni", "Title_train_star");
		Object->SetLocalPosition(CONST_TwinkleStarPosition, PivotType::Left);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Water);
		Object->SetSprite("Title_Train_Water.png");
		Object->SetLocalPosition(CONST_WaterPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Mountain_blur);
		Object->SetSprite("Title_Train_MountainWater_blur.png");
		Object->SetLocalPosition(CONST_MountainblurPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Bridge_Down);
		Object->SetSprite("Title_Train_Bridge_Down.png");
		Object->SetLocalPosition(CONST_BridgeDownPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Bridge_blur);
		Object->SetSprite("Title_Train_Bridge_Shadow.png");
		Object->SetLocalPosition(CONST_BridgeblurPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Train_blur);
		Object->SetSprite("Title_Train_TrainWater_blur.png");
		Object->SetLocalPosition(CONST_TranblurPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Train_Light_blur);
		Object->SetSprite("Title_Train_Light_Blur.png");
		Object->SetLocalPosition(CONST_LastTranLightblurPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Train_Light_blur);
		Object->SetSprite("Title_Train_WindowWater_blur.png");
		Object->SetLocalPosition(CONST_TranLightblurPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Water_blur);
		Object->SetSprite("Title_Train_WaterShine_blur.png");
		Object->SetLocalPosition(CONST_WaterblurPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 구름


	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Props_0);
		Object->SetSprite("Title_Train_Moon.png");
		Object->SetLocalPosition(CONST_MoonPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Props_0);
		Object->SetSprite("Title_Train_Mountain.png");
		Object->SetLocalPosition(CONST_MountainPosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Props_0);
		Object->SetSprite("Title_Train_WaterShine.png");
		Object->SetLocalPosition(CONST_WaterShinePosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->CreateRenderer(ETITLERENDERORDER::Trains_Light);
		Object->SetSprite("Title_Train_Bridge.png");
		Object->SetLocalPosition(CONST_BridgePosition, PivotType::LeftTop);
		vecProps.push_back(Object);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//std::shared_ptr<Prop> Object = _CurLevel->CreateActor<Prop>(EUPDATEORDER::Objects);
		//if (nullptr == Object)
		//{
		//	MsgBoxAssert("액터 생성을 실패하였습니다.");
		//	return;
		//}

		//Object->CreateRenderer(ETITLERENDERORDER::Shadow);
		//Object->SetSprite("Background_Shadow-Title.png");
		//Object->SetLocalPosition(float4::ZERO, PivotType::LeftTop);
		//Object->SetAutoSpriteSize(0.5f);
		//vecProps.push_back(Object);
	}



	{
		std::shared_ptr<ChainProp> Object = _CurLevel->CreateActor<ChainProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터 생성을 실패하였습니다.");
			return;
		}

		Object->SetRenderOrder(ETITLERENDERORDER::Cloud_0);
		Object->SetSprite("Title_Train_Cloud_0.png");
		Object->SetRegenTime(4.0f);
		Object->SetSpeed(-50.0f);

		Object->CalculateAndSetRegenLocationInputFirstLocation(CONST_Cloud1_Position);

		vecMainMenu_Chain.push_back(Object);
	}
}

#pragma endregion 
