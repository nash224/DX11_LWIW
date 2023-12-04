#include "PreCompile.h"
#include "TestPlayer.h"

#include "TestLevel.h"
#include "PixelManager.h"

TestPlayer::TestPlayer() 
{
}

TestPlayer::~TestPlayer() 
{
}


void TestPlayer::Start()
{
	Ellie::Start();
}

void TestPlayer::Update(float _Delta)
{
	Ellie::Update(_Delta);
}

void TestPlayer::Release()
{
	Ellie::Release();
}

void TestPlayer::LevelStart(class GameEngineLevel* _NextLevel)
{
	Ellie::LevelStart(_NextLevel);
}

void TestPlayer::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


EDIRECTION TestPlayer::ReturnDirectionCheckBothSide(EDIRECTION _Direction, const float4& _LeftCheckPoint, const float4& _RightCheckPoint)
{
	std::shared_ptr<TestLevel> CurLevel = GetLevel()->GetDynamic_Cast_This<TestLevel>();

	int DirNum = static_cast<int>(_Direction);

	GameEngineColor LeftColor = CurLevel->PixelManagerPtr->GetColor(_LeftCheckPoint);
	GameEngineColor RightColor = CurLevel->PixelManagerPtr->GetColor(_RightCheckPoint);

	bool isLeftWall = (GameEngineColor::RED == LeftColor && GameEngineColor::RED != RightColor);
	if (isLeftWall)
	{
		if (8 == DirNum)
		{
			DirNum = 1;
		}
		else
		{
			++DirNum;
		}
	}

	bool isRightWall = (GameEngineColor::RED != LeftColor && GameEngineColor::RED == RightColor);
	if (isRightWall)
	{
		if (1 == DirNum)
		{
			DirNum = 8;
		}
		else
		{
			--DirNum;
		}
	}

	bool isFrontWall = (GameEngineColor::RED == LeftColor && GameEngineColor::RED == RightColor);
	if (isFrontWall)
	{
		DirNum = 0;
	}

	return static_cast<EDIRECTION>(DirNum);
}