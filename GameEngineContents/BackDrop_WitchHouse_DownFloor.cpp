#include "PreCompile.h"
#include "BackDrop_WitchHouse_DownFloor.h"


#include "Prop.h"
#include "NormalProp.h"
#include "PortalObject.h"

#include "AlchemyPot.h"
#include "Extractor.h"
#include "Roaster.h"


BackDrop_WitchHouse_DownFloor::BackDrop_WitchHouse_DownFloor() 
{
}

BackDrop_WitchHouse_DownFloor::~BackDrop_WitchHouse_DownFloor() 
{
}


void BackDrop_WitchHouse_DownFloor::Start()
{
}

void BackDrop_WitchHouse_DownFloor::Update(float _Delta)
{
}

void BackDrop_WitchHouse_DownFloor::Release()
{
	
}

void BackDrop_WitchHouse_DownFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainBackDrop = this;
}

void BackDrop_WitchHouse_DownFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelEnd(_NextLevel);


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile pFile = Files[i];
		GameEngineSprite::Release(pFile.GetFileName());
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BackDrop_WitchHouse_DownFloor::Init()
{
	MainBackDrop = this;


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
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
	CreateStaticActor(CurLevel);
	CreatePortalActor(CurLevel);
}


#pragma endregion 

#pragma region CreateProp

void BackDrop_WitchHouse_DownFloor::CreateProp(GameEngineLevel* _Level)
{
#pragma region BackPaint

	float4 HWinScale = GlobalValue::GetWindowScale().Half();
	HWinScale.Y *= -1.0f;


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = HWinScale;
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::BackPaint);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Back.png");
		Object->m_Renderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale());
	}

#pragma endregion

#pragma region HouseComposition

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 349.0f , -315.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::HouseComposition);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Floor.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 350.0f , -191.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Wall);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Wall.png");
	}

#pragma endregion 


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 617.0f , -349.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Desk.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 254.0f , -469.0f };
		Position.Z = ZSort(Position.Y - 15.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Candle.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 45.0f , -134.0f };
		Position.Z = ZSort(Position.Y - 20.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Candle.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 198.0f , -63.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_PhotoFrame_5.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 177.0f , -37.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_PhotoFrame_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 157.0f , -65.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Paper_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 221.0f , -38.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Paper_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 120.0f , -52.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Paper_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 73.0f , -41.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Paper_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 616.0f , -272.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Paper_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 201.0f , -167.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Chair_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 48.0f , -147.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Chair_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 205.0f , -197.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Chair_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 168.0f , -268.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("Prop_DownFloor_Potion_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 92.0f , -247.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("ToolBox.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 143.0f , -260.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("Prop_DownFloor_Potion_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 408.0f , -394.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("PotBook.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 223.0f , -474.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Books_0.png");
	}


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 451.0f , -186.0f };
		Position.Z = ZSort(Position.Y - 12.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Books_6.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 229.0f , -141.0f };
		Position.Z = ZSort(Position.Y + 30.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Handrail_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 215.0f , -331.0f };
		Position.Z = ZSort(Position.Y + 30.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Handrail_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 75.0f , -269.0f };
		Position.Z = ZSort(Position.Y - 20.0f );
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Handrail_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 455.0f , -195.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Chair_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 26.0f , -203.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Cabinet.png");
	}


	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 521.0f , -132.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Cabinet_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 189.0f , -119.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Locker_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 254.0f , -481.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Books_3.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 191.0f , -476.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Books_7.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 67.0f , -197.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::UnderBook);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Books_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 641.0f , -485.0f };
		Position.Z = ZSort(Position.Y - 20.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Drawer_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 544.0f , -476.0f };
		Position.Z = ZSort(Position.Y - 20.0f);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Drawer_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 130.0f , -179.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Carpet.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 580.0f , -184.0f };
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Books_5.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 409.0f , -325.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Sign);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("WitchHouse_PotBase_MagicCircle_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 409.0f , -325.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Sign);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("WitchHouse_PotBase_MagicCircle_1.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 409.0f , -325.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Sign);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("PotBase_MagicCircle_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 68.0f , -205.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Books_Shadow_2.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 205.0f , -211.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Chair_Shadow.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 455.0f , -209.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Chair_Shadow.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 130.0f , -181.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Chair_Shadow.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 617.0f , -397.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Desk_Shadow.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 48.0f , -161.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Chair_Shadow.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 224.0f , -490.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Shadow);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Books_Shadow_0.png");
	}

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 409.0f , -325.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::Rug);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("PotBase.png");
	}


#pragma region Frame

	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 350.0f , -255.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::FRAME);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();
		Object->m_Renderer->SetSprite("DownFloor_Frame.png");
	}

#pragma endregion 
}


#pragma endregion 

#pragma region CreatePixelMap


void BackDrop_WitchHouse_DownFloor::CreatePixelMap(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = m_DownFloorWholePosition + float4{ 350.0f , -306.0f };
		Position.Z = GlobalUtils::CalculateDepth(EHOUSEDEPTH::FRAME);
		Object->Transform.SetLocalPosition(Position);
		Object->SetPixelCollision("DownFloor_PixelMap.png");
		PixelVec.push_back(Object);
	}
}


#pragma endregion 

#pragma region CreateStaticActor

void BackDrop_WitchHouse_DownFloor::CreateStaticActor(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<AlchemyPot> Object = _Level->CreateActor<AlchemyPot>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = float4(m_DownFloorWholePosition + float4(409.0f, -299.0f));
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);
		Object->Init();

		PixelStaticEntityVec.push_back(Object);
	}

	{
		std::shared_ptr<Roaster> Object = _Level->CreateActor<Roaster>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = float4(m_DownFloorWholePosition + float4(230.0f, -394.0f));
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);

		PixelStaticEntityVec.push_back(Object);
	}

	{
		std::shared_ptr<Extractor> Object = _Level->CreateActor<Extractor>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
			return;
		}

		float4 Position = float4(m_DownFloorWholePosition + float4(296.0f, -186.0f));
		Position.Z = ZSort(Position.Y);
		Object->Transform.SetLocalPosition(Position);

		PixelStaticEntityVec.push_back(Object);
	}
}


#pragma endregion 

#pragma region CreatePortal

void BackDrop_WitchHouse_DownFloor::CreatePortalActor(GameEngineLevel* _Level)
{
	{
		std::shared_ptr<PortalObject> Object = _Level->CreateActor<PortalObject>(EUPDATEORDER::Portal);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		float4 HWinScale = GlobalValue::GetWindowScale().Half();

		Object->CreatePortalCollision(ECOLLISION::Portal);
		Object->SetChangeLevelName("WitchHouse_UpFloor");
		Object->SetCollisionRange({ 64.0f , 22.0f });
		Object->SetLocalPosition({ 548.0f , -172.0f });
		Object->SetCollisionType(ColType::AABBBOX2D);
	}
}



#pragma endregion 

#pragma region Release

#pragma endregion 