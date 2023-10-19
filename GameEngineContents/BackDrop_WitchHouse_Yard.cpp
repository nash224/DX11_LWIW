#include "PreCompile.h"
#include "BackDrop_WitchHouse_Yard.h"

#include "Prop.h"
#include "PortalObject.h"
#include "Dian.h"
#include "WitchHouse.h"

BackDrop_WitchHouse_Yard::BackDrop_WitchHouse_Yard() 
{
}

BackDrop_WitchHouse_Yard::~BackDrop_WitchHouse_Yard() 
{
}


void BackDrop_WitchHouse_Yard::Start()
{
	BackDrop_PlayLevel::Start();
}

void BackDrop_WitchHouse_Yard::Update(float _Delta)
{
	BackDrop_PlayLevel::Update(_Delta);
}

void BackDrop_WitchHouse_Yard::Release()
{
	BackDrop_PlayLevel::Release();
}

void BackDrop_WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelStart(_NextLevel);
}

void BackDrop_WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_WitchHouse_Yard::Init()
{
	MainBackDrop = this;

	m_BackScale = GlobalValue::GetWindowScale();

	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CreateFlooring();
	CreateProp(CurLevel);
	CreateHouse(CurLevel);
	/*CreatePixelMap(CurLevel);*/
	CreatePortalActor(CurLevel);
	CreateDian(CurLevel);
	
	m_BackScale = GlobalValue::GetWindowScale();
}

void BackDrop_WitchHouse_Yard::CreateFlooring()
{
	m_BackProp.reserve(100);

	{
		float4 CenterPosition = GlobalValue::GetWindowScale().Half();
		CenterPosition.Y *= -1.0f;

		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>();
		if (nullptr == Renderer)
		{
			MsgBoxAssert("nullptr == Renderer");
			return;
		}

		Renderer->SetSprite("Yard_Back.png");
		Renderer->SetImageScale(GlobalValue::GetWindowScale());

		CenterPosition.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::Back_Paint);
		Renderer->Transform.SetLocalPosition(CenterPosition);
	}
}

#pragma region CreateProp
void BackDrop_WitchHouse_Yard::CreateProp(GameEngineLevel* _Level)
{
	//vecProps.reserve(30);

	//std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	//if (nullptr == Object)
	//{
	//	MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
	//	return;
	//}

	//Object->SetSprite("TestYardMap.png");
	//Object->SetRendererPivotType(PivotType::LeftTop);
	//Object->SetPositionAndDepth(float4::ZERO, ERENDERDEPTH::Back_);
	//vecProps.push_back(Object);

	
}

#pragma endregion 

void BackDrop_WitchHouse_Yard::CreateHouse(GameEngineLevel* _Level)
{
	m_BackScale;

	std::shared_ptr<WitchHouse> Object = _Level->CreateActor<WitchHouse>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
		return;
	}

	float HouseYPosition = -350.0f;

	float HouseZ = ZSort(HouseYPosition);
	Object->Transform.SetLocalPosition({ m_BackScale.Half().X, HouseYPosition , HouseZ });
	Object->Init();
}

#pragma region CreatePortal

void BackDrop_WitchHouse_Yard::CreatePortalActor(GameEngineLevel* _Level)
{
	{
		float4 HWinScale = GlobalValue::GetWindowScale().Half();

		{
			std::shared_ptr<PortalObject> Object = _Level->CreateActor<PortalObject>(EUPDATEORDER::Portal);
			if (nullptr == Object)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			Object->CreatePortalCollision(ECOLLISION::Portal);
			Object->SetChangeLevelName("WitchHouse_UpFloor");
			Object->SetLocalPosition({ 478.0f , -323.0f });
			Object->SetCollisionRange({ 60.0f , 4.0f });
			Object->SetCollisionType(ColType::AABBBOX2D);
			vecPortalObject.push_back(Object);
		}


		{
			std::shared_ptr<PortalObject> Object = _Level->CreateActor<PortalObject>(EUPDATEORDER::Portal);
			if (nullptr == Object)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			Object->CreatePortalCollision(ECOLLISION::Portal);
			Object->SetChangeLevelName("Field_Center");
			Object->SetLocalPosition({ HWinScale.X , -GlobalValue::GetWindowScale().Y });
			Object->SetCollisionRange({ 200.0f , 100.0f });
			Object->SetCollisionType(ColType::AABBBOX2D);
			vecPortalObject.push_back(Object);
		}

	}
}

#pragma endregion 


void BackDrop_WitchHouse_Yard::CreateDian(GameEngineLevel* _Level)
{
	std::shared_ptr<Dian> Object = _Level->CreateActor<Dian>(EUPDATEORDER::Entity);
	if (nullptr == Object)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Object->Transform.SetLocalPosition({ 700.0f , -400.0f });
	Object->Init();
}


#pragma region Release

#pragma endregion 