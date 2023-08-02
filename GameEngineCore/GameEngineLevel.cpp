#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineCore.h"
#include "GameEngineActor.h"

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
}

void GameEngineLevel::AllUpdate(float _Delta)
{
	Update(_Delta);

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		float TimeScale = GameEngineCore::MainTime.GetTimeScale(_Pair.first);
		for (std::shared_ptr<GameEngineObject>& _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}

			_Actor->AddLiveTime(_Delta);
			_Actor->AllUpdate(_Delta);
		}
	}
}


void GameEngineLevel::ActorRelease()
{
	
}
