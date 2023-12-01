#include "PreCompile.h"
#include "ChainProp.h"


#include "SequentialProp.h"

ChainProp::ChainProp()
{
}

ChainProp::~ChainProp() 
{
}


void ChainProp::Update(float _Delta)
{
	UpdateSeries();
	EraseOverScreenProp();
}

void ChainProp::Release()
{
	listProps.clear();
}

void ChainProp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void ChainProp::SetSprite(std::string_view _FileName)
{
	m_SpriteFileName = _FileName.data();

	const std::shared_ptr<GameEngineTexture>& Texture = GameEngineTexture::Find(_FileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert(m_SpriteFileName + "�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_TextureScale = Texture->GetScale();
}

void ChainProp::SetMaterial(std::string_view _MaterialName)
{
	MaterialName = _MaterialName;
}

void ChainProp::SetColor(const float4& _Color)
{
	Color = _Color;
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

void ChainProp::SetSpawnPoint(float _Value)
{
	m_RegenPoint = _Value;
}

// ������ �ڱ� �ؽ�ó �������� ���� X��ǥ �Դϴ�.
void ChainProp::SetAutoSpawnPoint()
{
	m_RegenPoint = m_TextureScale.Half().X;
}

// ù ��ġ�� ������ �˾Ƽ� ���� ��ġ�� �����ݴϴ�. 
// ������ �ؽ�ó ũ�Ⱑ ȭ�� ũ�⺸�� ũ�� ��ƴ���� �̾ ������ݴϴ�.
void ChainProp::CalculateAndSetRegenLocation(const float4& _Position)
{
	if ("" == m_SpriteFileName)
	{
		MsgBoxAssert("��������Ʈ�� ���� �������� ������ ����� �� ���� �Լ��Դϴ�.");
		return;
	}

	float4 HTextureScale = m_TextureScale.Half();
	float4 RegenPos;
	if (m_TextureScale.X >= GlobalValue::GetWindowScale().X)
	{
		RegenPos = float4{ m_TextureScale.X + HTextureScale.X , _Position.Y };
	}
	else
	{
		RegenPos = float4{ GlobalValue::GetWindowScale().X + HTextureScale.X , _Position.Y };
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
	// ù��°�϶� ��� ȭ�鿡 ���;��ϱ� ������ �ϳ��� ���� ����ش�.
	if (false == isFirstActorCreate)
	{
		RegenProp(m_FirstLocation);

		isFirstActorCreate = true;
	}

	// (�߿�) �ڷᱸ���� ��ü�� ������ ������ �����ߴ�.
	// ������ ���� ��ü�� �������� ���ؼ����� ���� ���ؼ��� �� �ָ� ���� ��� ������.
	if (true == listProps.empty())
	{
		MsgBoxAssert("List�� ��ü�� ��� ������Ʈ�� �� ���� �����ϴ�. ");
		return;
	}

	std::shared_ptr<SequentialProp> LastObject = listProps.back();
	if (nullptr == LastObject)
	{
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	// ����Ʈ�� ������ ��ü�� ��ġ�� ������ ������ �˻��ؾ��Ѵ�.
	// �����̴� ���⿡ ���� ���� ������ �ٸ��� �ߴ�.
	float LastObjectPosition = LastObject->Transform.GetWorldPosition().X;
	if (m_Speed < 0.0f)
	{
		// ���� ���� ���ؼ��� �Ѿ����, �Ѿ �Ÿ��� ����� �Ÿ��� �Ҿ������ �ʰԵȴ�.
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
	float4 Position = _Position;
	Position.Z = DepthFunction::CalculateFixDepth(m_Depth);

	std::shared_ptr<SequentialProp> Object = GetLevel()->CreateActor<SequentialProp>(EUPDATEORDER::Objects);
	Object->Transform.SetLocalPosition(Position);
	Object->Init();

	if (false == MaterialName.empty())
	{
		Object->Renderer->SetMaterial(MaterialName);
	}

	Object->Renderer->SetSprite(m_SpriteFileName); 
	Object->Renderer->GetColorData().MulColor = Color;

	Object->SetTextureScale(m_TextureScale);
	Object->SetSpeed(m_Speed);

	listProps.push_back(Object);
}


// ȭ�鿡 �Ѿ ��ǰ�� ���̻� �ʿ䰡 ����.
// �Ѿ ��ü�� �����ؼ� list�� ��ȸ�� �����ش�.
// ���귮�� ���� ������� Ÿ��Ʋ���� ����ϴ� �޸𸮰� �״� ���� ������ ��ȸ�� �������.
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

		(*StartIter)->Death();
		StartIter = listProps.erase(StartIter);
	}
}