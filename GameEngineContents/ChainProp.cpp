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
// 기준은 텍스처 크기가 화면 크기보다 크면 빈틈없이 이어서 출력해줍니다.
void ChainProp::CalculateAndSetRegenLocation(const float4& _Position)
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

void ChainProp::SetDepth(const int _Depth)
{
	m_Depth = _Depth;
}

void ChainProp::SetSpeed(float _Speed)
{
	m_Speed = _Speed;
}






void ChainProp::UpdateSeries()
{
	// 첫번째일때 어쩃든 화면에 나와야하기 떄문에 하나를 먼저 띄워준다.
	if (false == isFirstActorCreate)
	{
		RegenProp(m_FirstLocation);

		isFirstActorCreate = true;
	}

	// (중요) 자료구조에 객체가 없으면 터지게 설정했다.
	// 주의할 점은 객체가 없어지는 기준선보다 리젠 기준선이 더 멀리 있을 경우 터진다.
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
	Object->SetPositionAndDepth(_Position, m_Depth);

	listProps.push_back(Object);
}


// 화면에 넘어간 소품은 더이상 필요가 없다.
// 넘어간 객체를 추적해서 list를 순회해 없애준다.
// 연산량이 많이 돌어가지만 타이틀에는 사용하는 메모리가 그닥 없기 때문에 순회로 돌려줬다.
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
	for (std::shared_ptr<SequentialProp> Object : listProps)
	{
		Object->ActorRelease();
	}

	listProps.clear();

	Death();
}

