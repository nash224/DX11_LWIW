#include "PreCompile.h"
#include "BackDrop_WitchHouse_UpFloor.h"

#include "PortalObject.h"

#include "NormalProp.h"

BackDrop_WitchHouse_UpFloor::BackDrop_WitchHouse_UpFloor() 
{
}

BackDrop_WitchHouse_UpFloor::~BackDrop_WitchHouse_UpFloor() 
{
}


void BackDrop_WitchHouse_UpFloor::Start()
{

}

void BackDrop_WitchHouse_UpFloor::Update(float _Delta)
{

}

void BackDrop_WitchHouse_UpFloor::Release()
{

}

void BackDrop_WitchHouse_UpFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainBackDrop = this;
}

void BackDrop_WitchHouse_UpFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelEnd(_NextLevel);

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_UpFloor");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineSprite::Release(File.GetFileName());
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_WitchHouse_UpFloor::Init()
{
	MainBackDrop = this;


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_UpFloor");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineSprite::CreateSingle(File.GetFileName());
	}


	GameEngineLevel* CurLevel = GetLevel();

	m_BackScale = GlobalValue::GetWindowScale();
	CreateProp(CurLevel);
	CreatePixelMap(CurLevel);
	LoadPortalActor(CurLevel);

}


#pragma region Prop

void BackDrop_WitchHouse_UpFloor::CreateProp(GameEngineLevel* _Level)
{
	float4 RYWinScale = GlobalValue::GetWindowScale().Half();
	RYWinScale.Y *= -1.0f;

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition({ RYWinScale.X, RYWinScale.Y, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::BackPaint)});
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Back.png");
		Object->m_Renderer->GetImageTransform().SetLocalScale(float4(GlobalValue::GetWindowScale()));
	}


#pragma region HouseComposition

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}


		float4 Position = m_HouseLocation + float4{ 174.0f , -79.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::BackWindow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Circle.png");
		Object->m_Renderer->GetImageTransform().SetLocalScale(float4(64.0f, 64.0f));
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition(m_HouseLocation + float4{ 126.0f , -238.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Floor.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition(m_HouseLocation + float4{ 174.0f , -78.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_WallPaper_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition(m_HouseLocation + float4{ 126.0f , -110.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::HouseComposition) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_WallPaper.png");
	}


#pragma endregion 

#pragma region HouseShadow

	// HouseShadow
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		Object->Transform.SetLocalPosition(m_HouseLocation + float4{ 126.0f , -177.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Shadow )});
		Object->Init();
		Object->m_Renderer->SetSprite("UpFloor_Shadow.png");
	}

#pragma endregion 

#pragma region FirstObjects

	// FirstObjects
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		Object->Transform.SetLocalPosition(m_HouseLocation + float4{ 124.0f , -305.0f, GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug) });
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Carpet_0.png");

	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 228.0f , -163.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y - 70.0f );
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Cabinet.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 208.0f , -263.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y -20.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Plant_L.png");
	}


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 175.0f , -76.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_window.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 49.0f , -192.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_bed.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 104.0f , -106.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("book_shelf_empty.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 174.0f , -175.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Carpet_1.png");
	}

#pragma endregion 

#pragma region SecondObjects

	// SecondObjects
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 174.0f , -51.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_plants.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 33.0f , -285.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_drawer_under.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_HouseLocation + float4{ 175.0f , -145.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Chair);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Chair.png");
	}

#pragma endregion 

#pragma region ThirdObjects
	// ThirdObjects
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 174.0f , -149.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("Chair_Shadow.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 174.0f , -127.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_desk.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 101.0f , -151.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("hanger.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 14.0f , -259.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("PhotoFrame_0.png");
	}


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 27.0f , -275.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y - 14.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("SaveProp.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 117.0f , -84.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Flower_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 90.0f , -85.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Flower_1.png");
	}

#pragma endregion 

#pragma region ForthObjects


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 113.0f , -168.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_bag.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 175.0f , -127.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("book_open.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 32.0f , -116.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("DreamCapture.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 58.0f , -119.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_PhotoFrame_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 58.0f , -98.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_PhotoFrame_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 98.0f , -126.0f };
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BackScale.Y, Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("hanger_light.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 58.0f , -75.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("book_shelf.png");
	}


#pragma endregion 

#pragma region FifthObjects


#pragma endregion 

#pragma region HouseFrame

	// HouseFrame
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		float4 Position = m_HouseLocation + float4{ 126.0f , -171.0f };
		Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::FRAME);
		Object->Transform.SetLocalPosition(Position);
		Object->Init(ERENDERORDER::NonAlphaBlend);
		Object->m_Renderer->SetSprite("UpFloor_Frame.png");
	}

#pragma endregion 
}


#pragma endregion 

#pragma region PixelMap

void BackDrop_WitchHouse_UpFloor::CreatePixelMap(GameEngineLevel* _Level)
{
	PixelVec.reserve(3);

	std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
	float4 Position = m_HouseLocation + float4{ 128.0f , -242.0f };
	Position.Z = GlobalUtils::CalculateFixDepth(EHOUSEDEPTH::FRAME);
	Object->Transform.SetLocalPosition(Position);
	Object->SetPixelCollision("UpFloor_PixelMap.png");
	PixelVec.push_back(Object);
}


#pragma endregion 

#pragma region CreatePortal

void BackDrop_WitchHouse_UpFloor::LoadPortalActor(GameEngineLevel* _Level)
{
	float4 HWinScale = GlobalValue::GetWindowScale().Half();

	{
		std::shared_ptr<PortalObject> Object = _Level->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_DownFloor");
		Object->SetCollisionRange({ 44.0f , 20.0f });
		Object->SetLocalPosition(m_HouseLocation + float4{ 174.0f , -184.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}

	{
		std::shared_ptr<PortalObject> Object = _Level->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_Yard");
		Object->SetCollisionRange({ 60.0f , 10.0f });
		Object->SetLocalPosition(m_HouseLocation + float4{ 126.0f , -336.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}
}

#pragma endregion 

#pragma region Release

#pragma endregion 