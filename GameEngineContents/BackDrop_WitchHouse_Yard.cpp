#include "PreCompile.h"
#include "BackDrop_WitchHouse_Yard.h"

#include "PortalObject.h"
#include "Dian.h"
#include "WitchHouse.h"

#include "Prop_Tree.h"
#include "NormalProp.h"

BackDrop_WitchHouse_Yard::BackDrop_WitchHouse_Yard() 
{
}

BackDrop_WitchHouse_Yard::~BackDrop_WitchHouse_Yard() 
{
}


void BackDrop_WitchHouse_Yard::Start()
{
}

void BackDrop_WitchHouse_Yard::Update(float _Delta)
{

}

void BackDrop_WitchHouse_Yard::Release()
{

}

void BackDrop_WitchHouse_Yard::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainBackDrop = this;
}


void BackDrop_WitchHouse_Yard::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelEnd(_NextLevel);


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_Yard");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineSprite::Release(File.GetFileName());
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_WitchHouse_Yard::Init()
{
	MainBackDrop = this;


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_Yard");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	m_BackScale = GlobalValue::GetWindowScale();
	GameEngineLevel* CurLevel = GetLevel();

	CreateFlooring();
	CreateProp(CurLevel);
	CreateHouse(CurLevel);
	CreatePortalActor(CurLevel);
	CreateDian(CurLevel);
}

void BackDrop_WitchHouse_Yard::CreateFlooring()
{
	{
		float4 CenterPosition = GlobalValue::GetWindowScale().Half();
		CenterPosition.Y *= -1.0f;

		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>();
		if (nullptr == Renderer)
		{
			MsgBoxAssert("nullptr == Renderer");
			return;
		}

		CenterPosition.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::Back_Paint);
		Renderer->Transform.SetLocalPosition(CenterPosition);
		Renderer->SetSprite("GroundBase.png");
		Renderer->SetImageScale(GlobalValue::GetWindowScale());
	}
}

#pragma region CreateProp
void BackDrop_WitchHouse_Yard::CreateProp(GameEngineLevel* _Level)
{
	CreateTree(_Level);
	CreateNormalProp(_Level);
}

void BackDrop_WitchHouse_Yard::CreateTree(GameEngineLevel* _Level)
{
	PixelVec.reserve(50);

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 814.0f , -144.0f , ZSort(-200.0f) });
		Object->SelectTreeType(ETREETYPE::Tree2);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 700.0f , -62.0f , ZSort(-62.0f) });
		Object->SelectTreeType(ETREETYPE::Tree2);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 560.0f , -82.0f , ZSort(-82.0f) });
		Object->SelectTreeType(ETREETYPE::Tree2);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 100.0f , -466.0f , ZSort(-466.0f) });
		Object->SelectTreeType(ETREETYPE::Tree0);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 314.0f , -100.0f , ZSort(-100.0f) });
		Object->SelectTreeType(ETREETYPE::Tree2);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 186.0f , -100.0f , ZSort(-100.0f) });
		Object->SelectTreeType(ETREETYPE::Tree4);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 800.0f , -656.0f , ZSort(-656.0f) });
		Object->SelectTreeType(ETREETYPE::Tree2);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 844.0f , -550.0f , ZSort(-550.0f) });
		Object->SelectTreeType(ETREETYPE::Tree2);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 936.0f , -600.0f , ZSort(-600.0f) });
		Object->SelectTreeType(ETREETYPE::Tree4);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 930.0f , -780.0f , ZSort(-600.0f) });
		Object->SelectTreeType(ETREETYPE::Tree1);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 860.0f , -388.0f , ZSort(-388.0f) });
		Object->SelectTreeType(ETREETYPE::Tree4);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 936.0f , -340.0f , ZSort(-340.0f) });
		Object->SelectTreeType(ETREETYPE::Tree0);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 860.0f , -300.0f , ZSort(-300.0f) });
		Object->SelectTreeType(ETREETYPE::Tree4);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 952.0f , -200.0f , ZSort(-200.0f) });
		Object->SelectTreeType(ETREETYPE::Tree0);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 243.0f , -618.0f , ZSort(-618.0f) });
		Object->SelectTreeType(ETREETYPE::Tree2);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 58.0f , -616.0f , ZSort(-616.0f) });
		Object->SelectTreeType(ETREETYPE::Tree2);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 186.0f , -500.0f , ZSort(-500.0f) });
		Object->SelectTreeType(ETREETYPE::Tree0);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 186.0f , -500.0f , ZSort(-500.0f) });
		Object->SelectTreeType(ETREETYPE::Tree0);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 28.0f , -472.0f , ZSort(-472.0f) });
		Object->SelectTreeType(ETREETYPE::Tree0);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 28.0f , -472.0f , ZSort(-472.0f) });
		Object->SelectTreeType(ETREETYPE::Tree0);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 156.0f , -366.0f , ZSort(-366.0f) });
		Object->SelectTreeType(ETREETYPE::Tree4);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 45.0f , -318.0f , ZSort(-318.0f) });
		Object->SelectTreeType(ETREETYPE::Tree1);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 150.0f , -360.0f , ZSort(-360.0f) });
		Object->SelectTreeType(ETREETYPE::Tree1);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 100.0f , -235.0f , ZSort(-235.0f) });
		Object->SelectTreeType(ETREETYPE::Tree0);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 15.0f , -186.0f , ZSort(-186.0f) });
		Object->SelectTreeType(ETREETYPE::Tree3);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 100.0f , -86.0f , ZSort(-86.0f) });
		Object->SelectTreeType(ETREETYPE::Tree3);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 446.0f , -80.0f , ZSort(-80.0f) });
		Object->SelectTreeType(ETREETYPE::Tree1);
		Object->Init();
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<Prop_Tree> Object = _Level->CreateActor<Prop_Tree>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 945.0f , -460.0f , ZSort(-460.0f) });
		Object->SelectTreeType(ETREETYPE::Tree1);
		Object->Init();
		PixelVec.push_back(Object);
	}

}


void BackDrop_WitchHouse_Yard::CreateNormalProp(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 700.0f , -214.0f , ZSort(-234.0f) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("Yard_Pumpkins.png");
		Object->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 10.0f));
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 700.0f , -228.0f , ZSort(-228.0f) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("Yard_Stone_L_0.png");
		Object->SetPixelCollision("Yard_Stone_L_0_Pixel.png");
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ 438.0f , -330.0f , ZSort(-330.0f) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("Yard_MailBox.png");
		Object->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 34.0f));
	}
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

	{
		std::shared_ptr<NormalProp> PixelObject = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == PixelObject)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		PixelObject->Transform.SetLocalPosition(float4(m_BackScale.Half().X, -202.0f));
		PixelObject->SetPixelCollision("WitchHouse_Base_Pixel.png");
		PixelVec.push_back(PixelObject);
	}
}

#pragma region CreatePortal

void BackDrop_WitchHouse_Yard::CreatePortalActor(GameEngineLevel* _Level)
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