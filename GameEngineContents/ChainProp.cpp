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
	EraseOverScreenProp();
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

void ChainProp::SetFirstLocation(const float4& _Position)
{
	m_FirstLocation = _Position;
}

// 리젠 위치는 화면 밖에서 이미지가 생성되는 위치입니다.
void ChainProp::SetRegenLocation(const float4& _Position)
{
	m_RegenLocation = _Position;
}

// 첫 위치를 넣으면 알아서 리젠 위치를 정해줍니다. 
void ChainProp::CalculateAndSetRegenLocationInputFirstLocation(const float4& _Position)
{
	if ("" == m_SpriteFileName)
	{
		MsgBoxAssert("스프라이트를 먼저 적용하지 않으면 사용할 수 없는 함수입니다.");
		return;
	}

	float4 WinScale = GlobalValue::GetWindowScale();
	float4 HTextureScale = m_TextureScale.Half();

	float4 RegenPos = float4::ZERO;

	if (m_TextureScale.X >= WinScale.X)
	{
		RegenPos = float4{ m_TextureScale.X + HTextureScale.X , _Position.Y };
	}
	else
	{
		RegenPos = float4{ WinScale.X + HTextureScale.X , _Position.Y };
	}

	m_FirstLocation = _Position;
	m_RegenLocation = RegenPos;
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
		RegenProp(m_FirstLocation);

		isFirstActor = false;
	}


	m_StateTime += _Delta;

	if (m_StateTime > m_RegenTime)
	{
		// 일정 간격이 지날때마다 손해본 거리가 생긴다.
		// 움직이는 체인의 소품의 위치에 그 거리를 뺴줘야한다.
		float DelayTime = m_StateTime - m_RegenTime;

		m_DelayDistance = m_Speed * DelayTime ;

		RegenProp(m_RegenLocation);

		m_StateTime -= m_RegenTime;
	}
}


void ChainProp::RegenProp(const float4& _Position /*= float4::ZERO*/)
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
		float DelayXDistance = _Position.X + m_DelayDistance;
		float4 RegenLocation = float4{ DelayXDistance , m_RegenLocation.Y };
		Object->SetLocalPosition(RegenLocation);
		
		m_DelayDistance = 0.0f;
	}
	else
	{
		Object->SetLocalPosition(_Position);
	}

	listProps.push_back(Object);
}


void ChainProp::EraseOverScreenProp()
{
	std::list<std::shared_ptr<SequentialProp>>::iterator StartIter = listProps.begin();
	std::list<std::shared_ptr<SequentialProp>>::iterator EndIter = listProps.end();

	for (;StartIter != EndIter;)
	{
		if (false == (*StartIter)->isOverScreen)
		{
			++StartIter;
			continue;
		}

		StartIter = listProps.erase(StartIter);
	}
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

