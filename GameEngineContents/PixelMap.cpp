#include "PreCompile.h"
#include "PixelMap.h"



PixelMap* PixelMap::MainMap = nullptr;
PixelMap::PixelMap() 
{
}

PixelMap::~PixelMap() 
{
}


void PixelMap::Start()
{
	m_PixelRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Back_);
	if (nullptr == m_PixelRenderer)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_PixelRenderer->Off();
}

void PixelMap::Update(float _Delta)
{

}

void PixelMap::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void PixelMap::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// 렌더러를 적용시킵니다. 디버그용으로 확인할 수 있습니다.
void PixelMap::SetPixelSprite(std::string_view _FileName)
{
	if (nullptr == m_PixelRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았는데 사용하려 했습니다.");
		return;
	}

	m_PixelRenderer->SetSprite(_FileName);

	_PixelFileName = _FileName.data();
}


// 텍스처 자료를 찾아 지정위치의 픽셀 데이터를 얻어옵니다.
GameEngineColor PixelMap::GetColor(const float4& _Position, GameEngineColor _DefaultColor = { 255, 255, 255, 255 })
{
	if ("" == _PixelFileName)
	{
		MsgBoxAssert("픽셀 맵을 지정해주지 않았습니다.");
		return;
	}

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_PixelFileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	return Texture->GetColor(_Position, _DefaultColor);
}


// 렌더러를 켜고 끌 수 있는 기능입니다.
void PixelMap::EnableRenderer(bool _Value)
{
	if (nullptr == m_PixelRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	_Value ? m_PixelRenderer->On() : m_PixelRenderer->Off();
}



// 필요하지 않는 객체는 정리합니다.
void PixelMap::ActorRelease()
{
	m_PixelRenderer = nullptr;
	Death();
}