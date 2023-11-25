#include "PreCompile.h"
#include "TrainPart.h"

TrainPart::TrainPart() 
	:
	TrainRenderer(nullptr),
	LightRenderer(nullptr)
{
}

TrainPart::~TrainPart() 
{
}


void TrainPart::Release()
{
	TrainRenderer = nullptr;
	LightRenderer = nullptr;
}

void TrainPart::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void TrainPart::LastTrainInit()
{
	TrainRenderer = CreateComponent<GameEngineSpriteRenderer>();
}


void TrainPart::Init()
{
	TrainRenderer = CreateComponent<GameEngineSpriteRenderer>();
	LightRenderer = CreateComponent<GameEngineSpriteRenderer>();
}

void TrainPart::SetTrainSprite(std::string_view _TrainFileName, std::string_view _LightFileName /*= ""*/)
{
	if (nullptr == TrainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았습니다.");;
		return;
	}

	TrainRenderer->SetSprite(_TrainFileName);

	if (nullptr != LightRenderer)
	{
		LightRenderer->SetSprite(_LightFileName);
	}
}

void TrainPart::SetLocalPosition(const float4& _TrainPosition, const float4& _LightPosition /*= float4::ZERO*/, PivotType _Pivot /*= PivotType::LeftTop*/)
{
	if (nullptr == TrainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았습니다.");;
		return;
	}

	TrainRenderer->Transform.SetLocalPosition(_TrainPosition);
	TrainRenderer->SetPivotType(_Pivot);


	if (nullptr != LightRenderer)
	{
		LightRenderer->Transform.SetLocalPosition(_LightPosition);
		LightRenderer->SetPivotType(_Pivot);
	}
}

void TrainPart::AddLocalPosition(const float4& _float4)
{
	Transform.AddLocalPosition(_float4);
}