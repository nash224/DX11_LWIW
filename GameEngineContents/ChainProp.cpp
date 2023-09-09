#include "PreCompile.h"
#include "ChainProp.h"


#include "SequentialProp.h"

ChainProp::ChainProp()
	:
	m_RegenTime(1.0f),
	m_Speed(0.0f),
	m_StateTime(0.0f)
{
}

ChainProp::~ChainProp() 
{
}


void ChainProp::Start()
{

}

void ChainProp::Update(float _Delta)
{
	UpdateSeries(_Delta);
}

void ChainProp::Release()
{

}

void ChainProp::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void ChainProp::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


// 배치가 되고
// 시간이 되면 소품을 생성한다

void ChainProp::SetRenderOrder(int _Order)
{
	_Order = m_Order;
}

void ChainProp::SetSprite(std::string_view _FileName)
{
	m_SpriteFileName = _FileName.data();

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_FileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert(m_SpriteFileName + "텍스처를 불러오지 못했습니다.");
		return;
	}

	m_TextureScale = Texture->GetScale();
}

void ChainProp::SetRegenLocation(const float4& _Position)
{
	m_RegenLocation = _Position;
}

void ChainProp::SetRegenTime(float _Time)
{
	m_RegenTime = _Time;
}

void ChainProp::SetSpeed(float _Speed)
{
	m_Speed = _Speed;
}






void ChainProp::UpdateSeries(float _Delta)
{
	// 첫번째일때 먼저 띄운다.
	if (true == isFirstActor)
	{
		RegenProp();

		isFirstActor = false;
	}


	m_StateTime += _Delta;

	if (m_StateTime > m_RegenTime)
	{
		// 일정 간격이 지날때마다 손해본 거리가 생긴다.
		// 움직이는 체인의 소품의 위치에 그 거리를 뺴줘야한다.
		float DelayTime = m_StateTime - m_RegenTime;

		m_DelayDistance = m_Speed * DelayTime ;

		RegenProp();

		m_StateTime -= m_RegenTime;
	}
}


void ChainProp::RegenProp()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	std::shared_ptr<SequentialProp> Object = CurLevel->CreateActor<SequentialProp>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("액털를 생성하지 못했습니다.");
		return;
	}

	Object->CreateRenderer(m_Order);
	Object->SetSprite(m_SpriteFileName);
	Object->SetTextureScale(m_TextureScale);
	Object->SetSpeed(m_Speed);

	if (m_DelayDistance != 0.0f)
	{
		float DelayXDistance = m_RegenLocation.X + m_DelayDistance;
		float4 RegenLocation = float4{ DelayXDistance , m_RegenLocation.Y };
		Object->SetLocalPosition(RegenLocation);
		
		m_DelayDistance = 0.0f;
	}
	else
	{
		Object->SetLocalPosition(m_RegenLocation);
	}

	listProps.push_back(Object);
}


void ChainProp::ActorRelease()
{
	if (true == listProps.empty())
	{
		return;
	}

	for (std::shared_ptr<SequentialProp> Object : listProps)
	{
		Object->ActorRelease();
	}

	listProps.clear();

	Death();
}