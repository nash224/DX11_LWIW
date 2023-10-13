#include "PreCompile.h"
#include "BackDrop_CenterField.h"


#include "Prop.h"
#include "PortalObject.h"

#include "MongSiri_Population.h"
#include "Bush.h"


BackDrop_CenterField::BackDrop_CenterField() 
{
}

BackDrop_CenterField::~BackDrop_CenterField() 
{
}


void BackDrop_CenterField::Start()
{
	BackDrop::Start();
}

void BackDrop_CenterField::Update(float _Delta)
{
	BackDrop::Update(_Delta);
}

void BackDrop_CenterField::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);
}

void BackDrop_CenterField::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_CenterField::Init()
{
	BackDrop_PlayLevel::Init();

	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CreateFlooring();
	CreateProp(CurLevel);
	CreatePixelMap(CurLevel);
	CreatePortalActor(CurLevel);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("TestFieldMap.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처입니다.");
		return;
	}

	m_BackScale = Texture->GetScale();


	static bool IsCreatedCreature = false;
	if (false == IsCreatedCreature)
	{
		CreateCreature(CurLevel);

		IsCreatedCreature = true;
	}
}


#pragma endregion 


void BackDrop_CenterField::CreateFlooring()
{
	FlooringVec.reserve(100);

	{
		float4 BaseScale = { 1920.0f, 1080.0f };
		float4 BasePosition = BaseScale.Half();
		BasePosition.Y *= -1.0f;
		BasePosition.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::Back_Paint);

		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		if (nullptr == Renderer)
		{
			MsgBoxAssert("렌더러를 생성하지 못했습니다.");
			return;
		}

		Renderer->SetSprite("GroundBase.png");
		Renderer->SetImageScale(BaseScale);
		Renderer->Transform.SetLocalPosition(BasePosition);
		FlooringVec.push_back(Renderer);
	}

}

#pragma region CreateProp

void BackDrop_CenterField::CreateProp(GameEngineLevel* _Level)
{
}

#pragma endregion 

#pragma region CreatePixelMap

void BackDrop_CenterField::CreatePixelMap(GameEngineLevel* _Level)
{
	//vecPixelProps.reserve(30);

	//std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("TestFieldMap.png");
	//if (nullptr == Texture)
	//{
	//	MsgBoxAssert("텍스처를 불러오지 못했습니다.");
	//	return;
	//}

	//float4 Position = Texture->GetScale().Half();
	//Position.Y *= -1.0f;

	//std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	//if (nullptr == Object)
	//{
	//	MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
	//	return;
	//}

	//Object->CreateRenderer();
	//Object->SetSprite("TestFieldMap.png");
	//Object->CreatePixelCollisionRenderer();
	//Object->SetPixelSprite("TestCenter_ColorMap.png");
	//Object->SetPositionAndDepth(Position, ERENDERDEPTH::Back_);

	//vecPixelProps.push_back(Object);
}


#pragma endregion 

#pragma region CreatePortal

void BackDrop_CenterField::CreatePortalActor(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<PortalObject> Object = _Level->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_Yard");
		Object->SetLevelChangeCallBack<BackDrop_CenterField>(this, &BackDrop_CenterField::ActorRelease);
		Object->SetCollisionRange({ 100.0f , 400.0f });
		Object->SetLocalPosition({ 1200.0f , -200.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);

		vecPortalObject.push_back(Object);
	}
}

#pragma endregion 

// 날이 바뀌면 생성됩니다.
void BackDrop_CenterField::CreateCreature(GameEngineLevel* _Level)
{
	CreateDayNightTimeCreature(_Level);
	CreateDayTimeCreature(_Level);
	CreateNightCreature(_Level);
}

void BackDrop_CenterField::CreateDayNightTimeCreature(GameEngineLevel* _Level)
{
	CreateBush(_Level);
}


void BackDrop_CenterField::CreateDayTimeCreature(GameEngineLevel* _Level)
{
	CreateMongSiriPopulation(_Level);
}



void BackDrop_CenterField::CreateBush(GameEngineLevel* _Level)
{
	vecStaticEntity.reserve(30);

	{
		std::shared_ptr<Bush> Bush1 = _Level->CreateActor<Bush>(EUPDATEORDER::Entity);
		if (nullptr == Bush1)
		{
			MsgBoxAssert("덤풀을 생성하지 못했습니다.");
			return;
		}

		Bush1->Transform.SetLocalPosition({ 300.0f , -150.0f});
		Bush1->SetBushType(EBUSHTYPE::BushApple);
		Bush1->Init();

		vecStaticEntity.push_back(Bush1);
	}
}

void BackDrop_CenterField::CreateMongSiriPopulation(GameEngineLevel* _Level)
{
	PopulationVec.reserve(3);

	{
		std::shared_ptr<MongSiri_Population> MongSiri1 = _Level->CreateActor<MongSiri_Population>(EUPDATEORDER::Objects);
		MongSiri1->Transform.SetLocalPosition({ 100.0f , -100.0f });
		MongSiri1->SetPopulationSpawnLocation({ 150.0f , -150.0f });
		MongSiri1->Init(3);
		PopulationVec.push_back(MongSiri1);
	}
}


void BackDrop_CenterField::CreateNightCreature(GameEngineLevel* _Level)
{

}


#pragma region Release

void BackDrop_CenterField::ActorRelease()
{
	BackDrop_PlayLevel::ActorRelease();
}

void BackDrop_CenterField::PopulationRelease()
{
	for (size_t i = 0; i < PopulationVec.size(); i++)
	{
		std::shared_ptr<MongSiri_Population> Population = PopulationVec[i];
		if (nullptr == Population)
		{
			MsgBoxAssert("생성되지 않은 객체를 지우려고 했습니다.");
			return;
		}

		Population->ActorRelaese();
	}
}

#pragma endregion 