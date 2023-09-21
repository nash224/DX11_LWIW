#include "PreCompile.h"
#include "BackDrop_WitchHouse_DownFloor.h"


#include "Prop.h"


BackDrop_WitchHouse_DownFloor::BackDrop_WitchHouse_DownFloor() 
{
}

BackDrop_WitchHouse_DownFloor::~BackDrop_WitchHouse_DownFloor() 
{
}


void BackDrop_WitchHouse_DownFloor::Start()
{
	BackDrop::Start();
}

void BackDrop_WitchHouse_DownFloor::Update(float _Delta)
{

}

void BackDrop_WitchHouse_DownFloor::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void BackDrop_WitchHouse_DownFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BackDrop_WitchHouse_DownFloor::Init()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CreateProp(CurLevel);
	/*CreatePixelMap(CurLevel);*/

	m_BackScale = GlobalValue::GetWindowScale();
}


void BackDrop_WitchHouse_DownFloor::CreateProp(GameEngineLevel* _Level)
{
	vecProps.reserve(30);

	float4 RYWinScale = GlobalValue::GetWindowScale().Half();
	RYWinScale.Y *= -1.0f;

	{
		std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
		if (nullptr == Object)
		{
			MsgBoxAssert("������Ʈ�� �������� ���߽��ϴ�.");
			return;
		}

		Object->CreateRenderer(ERENDERORDER::Back_);
		Object->SetSprite("DownFloor_Floor.png");
		Object->SetRendererLocalPosition(RYWinScale);
		vecProps.push_back(Object);
	}
}



void BackDrop_WitchHouse_DownFloor::ActorRelease()
{
	BackDrop::ActorRelease();

	Death();
}