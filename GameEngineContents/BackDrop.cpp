#include "PreCompile.h"
#include "BackDrop.h"


#include "GlobalValue.h"
#include "Prop.h"
#include "Scenery.h"


BackDrop* BackDrop::MainBackDrop = nullptr;
BackDrop::BackDrop()
{
}

BackDrop::~BackDrop() 
{
}



void BackDrop::Start()
{
	MainBackDrop = this;
}

void BackDrop::Update(float _Delta)
{

}

void BackDrop::Release()
{
	MainBackDrop = nullptr;
}

void BackDrop::LevelStart(GameEngineLevel* _NextLevel)
{

}

void BackDrop::LevelEnd(GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const float4& BackDrop::GetBackGroundScale() const
{
	return m_BackScale;
}


// 이 픽셀충돌 텍스처의 특정 지점에서의 픽셀은 무슨 색상이니? 
// 만약 특정 색과 맞다면 true를 반환해줘
bool BackDrop::IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor, GameEngineColor _DefaultColor /*= { 255, 255, 255, 255 }*/)
{
	for (size_t i = 0; i < vecPixelProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecPixelProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
			return false;
		}

		if (false == Object->PixelRendererCheck)
		{
			continue;
		}

		if (_CheckColor == Object->GetColor(_Position, _DefaultColor))
		{
			return true;
		}
	}

	return false;
}

// 배경의 디버깅 모드로 일반 텍스처와 픽셀 충돌 텍스처를 전환시켜줍니다.
void BackDrop::EnableBackDropDebugMode(bool _Value)
{
	for (size_t i = 0; i < vecProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->EnableDebugMode(_Value);
	}


	for (size_t i = 0; i < vecPixelProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecPixelProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->EnableDebugMode(_Value);
	}

	EnableBackDropElemnetDebugMode(_Value);
}


void BackDrop::ActorRelease()
{
	for (size_t i = 0; i < vecProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecProps.clear();



	for (size_t i = 0; i < vecPixelProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecPixelProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecPixelProps.clear();


	for (size_t i = 0; i < vecScenery.size(); i++)
	{
		std::shared_ptr<Scenery> Object = vecScenery[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Object->ActorRelease();
	}

	vecScenery.clear();
}