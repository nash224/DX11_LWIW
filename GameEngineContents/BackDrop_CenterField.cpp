#include "PreCompile.h"
#include "BackDrop_CenterField.h"


#include "Prop.h"


BackDrop_CenterField::BackDrop_CenterField() 
{
}

BackDrop_CenterField::~BackDrop_CenterField() 
{
}


void BackDrop_CenterField::Start()
{
	BackDrop::Start();
}

void BackDrop_CenterField::Update(float _Delta)
{
	
}

void BackDrop_CenterField::LevelStart(class GameEngineLevel* _NextLevel)
{
	
}

void BackDrop_CenterField::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BackDrop_CenterField::Init()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CreateProp(CurLevel);
	CreatePixelMap(CurLevel);


	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("TestFieldMap.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�Դϴ�.");
		return;
	}

	m_BackScale = Texture->GetScale();
}

void BackDrop_CenterField::CreateProp(GameEngineLevel* _Level)
{
	vecProps.reserve(30);

	std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("������Ʈ�� �������� ���߽��ϴ�.");
		return;
	}

	Object->CreateRenderer(ERENDERORDER::Back_);
	Object->SetSprite("TestFieldMap.png");
	Object->SetRendererLocalPosition(float4::ZERO, PivotType::LeftTop);
	vecProps.push_back(Object);
}


void BackDrop_CenterField::CreatePixelMap(GameEngineLevel* _Level)
{
	vecPixelProps.reserve(30);

	std::shared_ptr<Prop> Object = _Level->CreateActor<Prop>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("������Ʈ�� �������� ���߽��ϴ�.");
		return;
	}

	Object->CreateRenderer(ERENDERORDER::Back_);
	Object->SetSprite("TestFieldMap.png");
	Object->CreatePixelCollisionRenderer();
	Object->SetPixelSprite("TestCenter_ColorMap.png");
	Object->Transform.SetLocalPosition({ 960.0f , -540.0f });

	vecPixelProps.push_back(Object);
}


void BackDrop_CenterField::ActorRelease()
{
	BackDrop::ActorRelease();

	Death();
}