#include "PreCompile.h"
#include "BackDrop_CenterField.h"


#include "Prop.h"
#include "PortalObject.h"

#include "MongSiri_Population.h"
#include "Bush.h"
#include "WitchFlower.h"
#include "FlowerBird.h"
#include "BranchTree.h"


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

void BackDrop_CenterField::Release()
{
	BackDrop::Release();
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
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CreateFlooring();
	CreateProp(CurLevel);
	CreatePixelMap(CurLevel);
	CreatePortalActor(CurLevel);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("TestFieldMap.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�Դϴ�.");
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


void BackDrop_CenterField::TestPorp()
{
	// std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	// Position, Rotation
	// Depth => (RenderDepth, ZOrder)
	// Renderer->SetSprite
	/*Renderer->Transform.SetLocalPosition();*/
	// pushback
}


void BackDrop_CenterField::CreateFlooring()
{
	m_BackProp.reserve(100);

	{
		float4 BaseScale = { 1920.0f, 1080.0f };
		float4 BasePosition = BaseScale.Half();
		BasePosition.Y *= -1.0f;
		BasePosition.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::Back_Paint);

		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
		if (nullptr == Renderer)
		{
			MsgBoxAssert("�������� �������� ���߽��ϴ�.");
			return;
		}

		Renderer->SetSprite("GroundBase.png");
		Renderer->SetImageScale(BaseScale);
		Renderer->Transform.SetLocalPosition(BasePosition);
		m_BackProp.push_back(Renderer);
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
	//	MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
	//	return;
	//}

	//float4 Position = Texture->GetScale().Half();
	//Position.Y *= -1.0f;

	//std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	//if (nullptr == Object)
	//{
	//	MsgBoxAssert("������Ʈ�� �������� ���߽��ϴ�.");
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
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_Yard");
		Object->SetCollisionRange({ 100.0f , 400.0f });
		Object->SetLocalPosition({ 1200.0f , -200.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);

		vecPortalObject.push_back(Object);
	}
}

#pragma endregion 

// ���� �ٲ�� �����˴ϴ�.
void BackDrop_CenterField::CreateCreature(GameEngineLevel* _Level)
{
	CreateDayNightTimeCreature(_Level);
	CreateDayTimeCreature(_Level);
	CreateNightCreature(_Level);
}

void BackDrop_CenterField::CreateDayNightTimeCreature(GameEngineLevel* _Level)
{
	CreateBush(_Level);
	CreateWitchFlower(_Level);
	CreateBranchTree(_Level);
	CreateFlowerBird(_Level);
}


void BackDrop_CenterField::CreateDayTimeCreature(GameEngineLevel* _Level)
{
	CreateMongSiriPopulation(_Level);
}



void BackDrop_CenterField::CreateBush(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<Bush> BushObject = _Level->CreateActor<Bush>(EUPDATEORDER::Entity);
		if (nullptr == BushObject)
		{
			MsgBoxAssert("��Ǯ�� �������� ���߽��ϴ�.");
			return;
		}

		BushObject->Transform.SetLocalPosition({ 300.0f , -150.0f });
		BushObject->SetBushType(EBUSHTYPE::Bush);
		BushObject->Init();

		StaticEntityList.push_back(BushObject);
	}

	{
		std::shared_ptr<Bush> BushObject = _Level->CreateActor<Bush>(EUPDATEORDER::Entity);
		if (nullptr == BushObject)
		{
			MsgBoxAssert("��Ǯ�� �������� ���߽��ϴ�.");
			return;
		}

		BushObject->Transform.SetLocalPosition({ 400.0f , -150.0f });
		BushObject->SetBushType(EBUSHTYPE::BushApple);
		BushObject->Init();

		StaticEntityList.push_back(BushObject);
	}

	{
		std::shared_ptr<Bush> BushObject = _Level->CreateActor<Bush>(EUPDATEORDER::Entity);
		if (nullptr == BushObject)
		{
			MsgBoxAssert("��Ǯ�� �������� ���߽��ϴ�.");
			return;
		}

		BushObject->Transform.SetLocalPosition({ 500.0f , -150.0f });
		BushObject->SetBushType(EBUSHTYPE::BushBug);
		BushObject->Init();

		StaticEntityList.push_back(BushObject);
	}
}

void BackDrop_CenterField::CreateWitchFlower(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<WitchFlower> Object = _Level->CreateActor<WitchFlower>(EUPDATEORDER::Entity);
		if (nullptr == Object)
		{
			MsgBoxAssert("��Ǯ�� �������� ���߽��ϴ�.");
			return;
		}

		Object->Transform.SetLocalPosition({ 300.0f , -350.0f });
		Object->Init();

		StaticEntityList.push_back(Object);
	}
}

void BackDrop_CenterField::CreateBranchTree(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<BranchTree> Object = _Level->CreateActor<BranchTree>(EUPDATEORDER::Entity);
		if (nullptr == Object)
		{
			MsgBoxAssert("���� ������ �������� ���߽��ϴ�.");
			return;
		}

		Object->Transform.SetLocalPosition({ 500.0f , -550.0f });
		Object->Init();

		StaticEntityList.push_back(Object);
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

void BackDrop_CenterField::CreateFlowerBird(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<FlowerBird> Object = _Level->CreateActor<FlowerBird>(EUPDATEORDER::Entity);
		if (nullptr == Object)
		{
			MsgBoxAssert("���� ������ �������� ���߽��ϴ�.");
			return;
		}

		Object->Transform.SetLocalPosition({ 400.0f , -200.0f });
		Object->Init();

	}

}


void BackDrop_CenterField::CreateNightCreature(GameEngineLevel* _Level)
{

}


#pragma region Release


void BackDrop_CenterField::PopulationRelease()
{
	for (size_t i = 0; i < PopulationVec.size(); i++)
	{
		std::shared_ptr<MongSiri_Population> Population = PopulationVec[i];
		if (nullptr == Population)
		{
			MsgBoxAssert("�������� ���� ��ü�� ������� �߽��ϴ�.");
			return;
		}

		Population->ActorRelaese();
	}
}

#pragma endregion 