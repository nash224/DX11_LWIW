#include "PreCompile.h"
#include "BackDrop_CenterField.h"


#include "Prop.h"
#include "PortalObject.h"


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


}


#pragma endregion 

#pragma region CreateProp

void BackDrop_CenterField::CreateProp(GameEngineLevel* _Level)
{

}

#pragma endregion 

#pragma region CreatePixelMap

void BackDrop_CenterField::CreatePixelMap(GameEngineLevel* _Level)
{
	vecPixelProps.reserve(30);

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("TestFieldMap.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	float4 Position = Texture->GetScale().Half();
	Position.Y *= -1.0f;

	std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
		return;
	}

	Object->CreateRenderer();
	Object->SetSprite("TestFieldMap.png");
	Object->CreatePixelCollisionRenderer();
	Object->SetPixelSprite("TestCenter_ColorMap.png");
	Object->SetPositionAndDepth(Position, ERENDERDEPTH::Back_);

	vecPixelProps.push_back(Object);
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

#pragma region Release

void BackDrop_CenterField::ActorRelease()
{
	BackDrop_PlayLevel::ActorRelease();
}

#pragma endregion 