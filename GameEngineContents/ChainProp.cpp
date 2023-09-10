#include "PreCompile.h"
#include "ChainProp.h"


#include "SequentialProp.h"

ChainProp::ChainProp()
	:
	m_Speed(0.0f)
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
	UpdateSeries();
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
	m_Order = _Order;
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

void ChainProp::SetSpawnPoint(float _Value)
{
	m_RegenPoint = _Value;
}

// 기준은 자기 텍스처 스케일의 반의 X좌표 입니다.
void ChainProp::SetAutoSpawnPoint()
{
	m_RegenPoint = m_TextureScale.Half().X;
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

void ChainProp::SetSpeed(float _Speed)
{
	m_Speed = _Speed;
}






void ChainProp::UpdateSeries()
{
	// 첫번째일때 먼저 띄운다.
	if (false == isFirstActorCreate)
	{
		RegenProp(m_FirstLocation);

		isFirstActorCreate = true;
	}

	if (true == listProps.empty())
	{
		MsgBoxAssert("List에 객체가 없어서 업데이트를 할 수가 없습니다. ");
		return;
	}

	std::shared_ptr<SequentialProp> LastObject = listProps.back();
	if (nullptr == LastObject)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	// 리스트의 마지막 객체의 위치를 참조해 조건을 검사해야한다.
	// 움직이는 방향에 따라 리젠 조건을 다르게 했다.
	float LastObjectPosition = LastObject->Transform.GetWorldPosition().X;
	if (m_Speed < 0.0f)
	{
		// 만약 리젠 기준선을 넘어갔으면, 넘어간 거리는 빼줘야 거리를 잃어버리지 않게된다.
		if (LastObjectPosition < m_RegenPoint)
		{
			float DelayXDistance = LastObjectPosition - m_RegenPoint;
			float4 RegenLocation = float4{ DelayXDistance + m_RegenLocation.X , m_RegenLocation.Y };
			RegenProp(RegenLocation);
		}
	}
	else
	{
		if (LastObjectPosition > m_RegenPoint)
		{
			float DelayXDistance = LastObjectPosition - m_RegenPoint;
			float4 RegenLocation = float4{ DelayXDistance + m_RegenLocation.X , m_RegenLocation.Y };
			RegenProp(RegenLocation);

		}
	}
	



	//if (m_StateTime > m_RegenTime)
	//{
	//	// 일정 간격이 지날때마다 손해본 거리가 생긴다.
	//	// 움직이는 체인의 소품의 위치에 그 거리를 빼줘야한다.
	//	float DelayTime = m_StateTime - m_RegenTime;
	//	m_DelayDistance = m_Speed * DelayTime ;
	//	float DelayXDistance = m_RegenLocation.X + m_DelayDistance;
	//	float4 RegenLocation = float4{ DelayXDistance , m_RegenLocation.Y };

	//	RegenProp(RegenLocation);


	//	m_DelayDistance = 0.0f;
	//	m_StateTime -= m_RegenTime;
	//}
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
	Object->SetLocalPosition(_Position);

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

		(*StartIter)->ActorRelease();
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

