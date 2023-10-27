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



	CreateBase();
	LoadSerBin();
	CreateHouse();
	CreateNormalProp();
	CreatePortalActor();
	CreateDian();
}


void BackDrop_WitchHouse_Yard::LoadSerBin()
{
	{
		GameEngineSerializer LoadBin;

		GameEngineFile File;
		File.MoveParentToExistsChild("Resources");
		File.MoveChild("Resources\\Data\\SaveThis.map");

		File.Open(FileOpenType::Read, FileDataType::Binary);
		File.DataAllRead(LoadBin);

		// °´Ã¼ ¼ö ÀÐ¾î¿È
		unsigned int ActorCount = 0;
		LoadBin >> ActorCount;

		for (size_t i = 0; i < ActorCount; i++)
		{
			std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>();
			Object->DeSerializer(LoadBin);
			PixelVec.push_back(Object);
		}
	}
}

void BackDrop_WitchHouse_Yard::CreateBase()
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

		CenterPosition.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Back_Paint);
		Renderer->Transform.SetLocalPosition(CenterPosition);
		Renderer->SetSprite("GroundBase.png");
		Renderer->SetImageScale(GlobalValue::GetWindowScale());
	}
}

#pragma region CreateProp


void BackDrop_WitchHouse_Yard::CreateNormalProp()
{
	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition({ 700.0f , -214.0f , ZSort(-234.0f) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("Yard_Pumpkins.png");
		Object->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 10.0f));
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition({ 700.0f , -228.0f , ZSort(-228.0f) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("Yard_Stone_L_0.png");
		Object->SetPixelCollision("Yard_Stone_L_0_Pixel.png");
		PixelVec.push_back(Object);
	}

	{
		std::shared_ptr<NormalProp> Object = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition({ 438.0f , -330.0f , ZSort(-330.0f) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("Yard_MailBox.png");
		Object->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 34.0f));
	}
}

#pragma endregion 




void BackDrop_WitchHouse_Yard::CreateHouse()
{
	std::shared_ptr<WitchHouse> Object = GetLevel()->CreateActor<WitchHouse>(EUPDATEORDER::Objects);
	float HouseYPosition = -350.0f;
	float HouseZ = ZSort(HouseYPosition);
	Object->Transform.SetLocalPosition({ m_BackScale.Half().X, HouseYPosition , HouseZ });
	Object->Init();

	{
		std::shared_ptr<NormalProp> PixelObject = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		PixelObject->Transform.SetLocalPosition(float4(m_BackScale.Half().X, -202.0f));
		PixelObject->SetPixelCollision("WitchHouse_Base_Pixel.png");
		PixelVec.push_back(PixelObject);
	}
}

#pragma region CreatePortal

void BackDrop_WitchHouse_Yard::CreatePortalActor()
{
	float4 HWinScale = GlobalValue::GetWindowScale().Half();

	{
		std::shared_ptr<PortalObject> Object = GetLevel()->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_UpFloor");
		Object->SetLocalPosition({ 478.0f , -323.0f });
		Object->SetCollisionRange({ 60.0f , 4.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}


	{
		std::shared_ptr<PortalObject> Object = GetLevel()->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("Field_Center");
		Object->SetLocalPosition({ HWinScale.X , -GlobalValue::GetWindowScale().Y });
		Object->SetCollisionRange({ 200.0f , 100.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}
}

#pragma endregion 


void BackDrop_WitchHouse_Yard::CreateDian()
{
	std::shared_ptr<Dian> Object = GetLevel()->CreateActor<Dian>(EUPDATEORDER::Entity);
	Object->Transform.SetLocalPosition({ 700.0f , -400.0f });
	Object->Init();
}


#pragma region Release

#pragma endregion 