#include "PreCompile.h"
#include "MonSiri_Population.h"

#include "MongSiri.h"
#include "ChubHole.h"

MonSiri_Population::MonSiri_Population() 
{
}

MonSiri_Population::~MonSiri_Population() 
{
}



void MonSiri_Population::Start()
{

}

void MonSiri_Population::Update(float _Delta)
{
	
}

void MonSiri_Population::Release()
{
	
}

void MonSiri_Population::LevelStart(class GameEngineLevel* _NextLevel)
{
	
}

void MonSiri_Population::LevelEnd(class GameEngineLevel* _NextLevel)
{
	
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void MonSiri_Population::Init(unsigned int _Population)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	SetUpChubHole(CurLevel);
	CreateMongSiri(CurLevel, _Population);
}

void MonSiri_Population::SetUpChubHole(GameEngineLevel* _CurLevel)
{
	m_ChubHole = _CurLevel->CreateActor<ChubHole>(EUPDATEORDER::Objects);
	if (nullptr == m_ChubHole)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_ChubHole->Transform.SetLocalPosition(Transform.GetLocalPosition());
}

void MonSiri_Population::CreateMongSiri(GameEngineLevel* _CurLevel, unsigned int _Population)
{
	for (size_t i = 0; i < _Population; i++)
	{
		std::shared_ptr<MongSiri> Object = _CurLevel->CreateActor<MongSiri>(EUPDATEORDER::Entity);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		Object->Init();
		MongSiriEntityList.push_back(Object);
	}
}