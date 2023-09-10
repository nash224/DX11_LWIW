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


// ��ġ�� �ǰ�
// �ð��� �Ǹ� ��ǰ�� �����Ѵ�

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
		MsgBoxAssert(m_SpriteFileName + "�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_TextureScale = Texture->GetScale();
}

void ChainProp::SetFirstLocation(const float4& _Position)
{
	m_FirstLocation = _Position;
}

// ���� ��ġ�� ȭ�� �ۿ��� �̹����� �����Ǵ� ��ġ�Դϴ�.
void ChainProp::SetRegenLocation(const float4& _Position)
{
	m_RegenLocation = _Position;
}

// ù ��ġ�� ������ �˾Ƽ� ���� ��ġ�� �����ݴϴ�. 
void ChainProp::CalculateAndSetRegenLocationInputFirstLocation(const float4& _Position)
{
	if ("" == m_SpriteFileName)
	{
		MsgBoxAssert("��������Ʈ�� ���� �������� ������ ����� �� ���� �Լ��Դϴ�.");
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
	// ù��°�϶� ���� ����.
	if (true == isFirstActor)
	{
		RegenProp(m_FirstLocation);

		isFirstActor = false;
	}


	m_StateTime += _Delta;

	if (m_StateTime > m_RegenTime)
	{
		// ���� ������ ���������� ���غ� �Ÿ��� �����.
		// �����̴� ü���� ��ǰ�� ��ġ�� �� �Ÿ��� ������Ѵ�.
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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	std::shared_ptr<SequentialProp> Object = CurLevel->CreateActor<SequentialProp>(EUPDATEORDER::Objects);
	if (nullptr == Object)
	{
		MsgBoxAssert("���и� �������� ���߽��ϴ�.");
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

