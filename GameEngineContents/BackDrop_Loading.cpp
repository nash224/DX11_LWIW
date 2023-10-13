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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CreateProp(CurLevel);

	std::shared_ptr<GameEngineTexture> Texture  = GameEngineTexture::Find("Loading_Back.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ε�Ǿ� ���� �ʽ��ϴ�.");
		return;
	}

	m_BackScale = Texture->GetScale();
}

void BackDrop_Loading::CreateProp(GameEngineLevel * _Level)
{
	std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("������Ʈ�� �������� ���߽��ϴ�.");
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
			MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
			return;
		}

		Object->ActorRelease();
	}

	Death();
}