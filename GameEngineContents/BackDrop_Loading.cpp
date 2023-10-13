#include "PreCompile.h"
#include "BackDrop_Loading.h"


#include "Prop.h"

BackDrop_Loading::BackDrop_Loading() 
{
}

BackDrop_Loading::~BackDrop_Loading() 
{
}


void BackDrop_Loading::Start()
{

}

void BackDrop_Loading::Update(float _Delta)
{

}

void BackDrop_Loading::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void BackDrop_Loading::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_Loading::Init()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CreateProp(CurLevel);

	std::shared_ptr<GameEngineTexture> Texture  = GameEngineTexture::Find("Loading_Back.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처가 로드되어 있지 않습니다.");
		return;
	}

	m_BackScale = Texture->GetScale();
}

void BackDrop_Loading::CreateProp(GameEngineLevel * _Level)
{
	std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("오브젝트를 생성하지 못했습니다.");
		return;
	}

	Object->CreateRenderer();
	Object->SetSprite("Loading_Back.png");
	Object->SetRendererPivotType(PivotType::LeftTop);
	Object->SetPositionAndDepth(float4::ZERO, ERENDERDEPTH::Back_);
	vecProps.push_back(Object);
}



void BackDrop_Loading::ActorRelease()
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

	Death();
}