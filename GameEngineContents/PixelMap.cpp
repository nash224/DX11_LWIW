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
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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

// �������� �����ŵ�ϴ�. ����׿����� Ȯ���� �� �ֽ��ϴ�.
void PixelMap::SetPixelSprite(std::string_view _FileName)
{
	if (nullptr == m_PixelRenderer)
	{
		MsgBoxAssert("�������� �������� �ʾҴµ� ����Ϸ� �߽��ϴ�.");
		return;
	}

	m_PixelRenderer->SetSprite(_FileName);

	_PixelFileName = _FileName.data();
}


// �ؽ�ó �ڷḦ ã�� ������ġ�� �ȼ� �����͸� ���ɴϴ�.
GameEngineColor PixelMap::GetColor(const float4& _Position, GameEngineColor _DefaultColor = { 255, 255, 255, 255 })
{
	if ("" == _PixelFileName)
	{
		MsgBoxAssert("�ȼ� ���� ���������� �ʾҽ��ϴ�.");
		return;
	}

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_PixelFileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	return Texture->GetColor(_Position, _DefaultColor);
}


// �������� �Ѱ� �� �� �ִ� ����Դϴ�.
void PixelMap::EnableRenderer(bool _Value)
{
	if (nullptr == m_PixelRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	_Value ? m_PixelRenderer->On() : m_PixelRenderer->Off();
}



// �ʿ����� �ʴ� ��ü�� �����մϴ�.
void PixelMap::ActorRelease()
{
	m_PixelRenderer = nullptr;
	Death();
}