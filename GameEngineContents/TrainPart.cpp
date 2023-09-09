#include "PreCompile.h"
#include "TrainPart.h"

TrainPart::TrainPart() 
	:
	m_TrainRenderer(nullptr),
	m_LightRenderer(nullptr)
{
}

TrainPart::~TrainPart() 
{
}


void TrainPart::Start()
{

}

void TrainPart::Update(float _Delta)
{

}

void TrainPart::Release()
{

}

void TrainPart::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void TrainPart::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void TrainPart::CreateLastTrainRenderer()
{
	m_TrainRenderer = CreateComponent<GameEngineSpriteRenderer>(ETITLERENDERORDER::Trains);
	if (nullptr == m_TrainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}
}


void TrainPart::CreateRenderer()
{
	m_TrainRenderer = CreateComponent<GameEngineSpriteRenderer>(ETITLERENDERORDER::Trains);
	if (nullptr == m_TrainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_LightRenderer = CreateComponent<GameEngineSpriteRenderer>(ETITLERENDERORDER::Trains_Light);
	if (nullptr == m_LightRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}
}

void TrainPart::SetSprite(std::string_view _TrainFileName, std::string_view _LightFileName /*= ""*/)
{
	if (nullptr == m_TrainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았습니다.");;
		return;
	}

	m_TrainRenderer->SetSprite(_TrainFileName);

	if (nullptr != m_LightRenderer)
	{
		m_LightRenderer->SetSprite(_LightFileName);
	}
}

void TrainPart::SetLocalPosition(const float4& _TrainPosition, const float4& _LightPosition /*= float4::ZERO*/, PivotType _Pivot /*= PivotType::LeftTop*/)
{
	if (nullptr == m_TrainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았습니다.");;
		return;
	}

	m_TrainRenderer->Transform.SetLocalPosition(_TrainPosition);
	m_TrainRenderer->SetPivotType(_Pivot);


	if (nullptr != m_LightRenderer)
	{
		m_LightRenderer->Transform.SetLocalPosition(_LightPosition);
		m_LightRenderer->SetPivotType(_Pivot);
	}
}

void TrainPart::AddLocalPosition(const float4 & _float4)
{
	Transform.AddLocalPosition(_float4);
}


void TrainPart::ActorRelease()
{
	m_TrainRenderer = nullptr;
	m_LightRenderer = nullptr;

	Death();
}