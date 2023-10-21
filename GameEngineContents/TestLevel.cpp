#include "PreCompile.h"
#include "TestLevel.h"


#include "CameraControler.h"

#include "Ellie.h"
#include "BushBug.h"
#include "Bush.h"
#include "NormalProp.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}


void TestLevel::Start()
{
	ContentsLevel::Start();
}

void TestLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta); 
}

void TestLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	GlobalValue::g_CameraControler->SetCameraMode(ECAMERAMODE::Fix);

	Player = CreateActor<Ellie>(EUPDATEORDER::Player);
	Player->Init();

	m_bush = CreateActor<Bush>(EUPDATEORDER::Player);
	m_bush->Init();

	m_BushBug = CreateActor<BushBug >(EUPDATEORDER::Player);
	m_BushBug->Init();
}

void TestLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);

	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	if (nullptr != m_bush)
	{
		m_bush->Death();
		m_bush = nullptr;
	}

	if (nullptr != m_BushBug)
	{
		m_BushBug->Death();
		m_BushBug = nullptr;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void TestMap::LevelStart(class GameEngineLevel* _NextLevel)
{
	std::shared_ptr<NormalProp> Map = GetLevel()->CreateActor<NormalProp>(EUPDATEORDER::Player);
	/*Map->m_Renderer->SetSprite();*/
}