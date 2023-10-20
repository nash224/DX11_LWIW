#include "PreCompile.h"
#include "Props.h"

Props::Props() 
{
}

Props::~Props() 
{
}


void Props::Start()
{
}

void Props::Update(float _Delta)
{
}

void Props::Release()
{
}

void Props::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void Props::LevelEnd(class GameEngineLevel* _NextLevel)
{
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void Props::UpdateDebug()
{
	if (true == IsRendererOn && true == PlayLevel::PixelDebugMode)
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->Off();
		}

		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->On();
		}

		IsRendererOn = false;
	}

	if (false == IsRendererOn && false == PlayLevel::PixelDebugMode)
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->On();
		}

		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->Off();
		}

		IsRendererOn = true;
	}
}



bool Props::GetPixelCheck()
{
	return PixelRendererCheck;
}

void Props::SetPixelCollision(std::string_view _FileName)
{
	m_DebugRenderer = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_DebugRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_DebugRenderer->Off();
	m_DebugRenderer->SetSprite(_FileName);
	m_PixelFileName = _FileName;

	PixelRendererCheck = true;
}


// ������* ��ġ�� �ȼ� �����͸� ��ȯ���ݴϴ�.
// * : GameEngineTexture::GetColor�� �ؽ�ó���� ���� ���ϴ� ��ġ�� �ȼ� �����͸� �޶�� �䱸�մϴ�.
//		�̷��� Ư�� ������ �ؽ�ó�� ����ϴ� ��ü�� ��ġ�� �̵��ص� GetColor���� �ִ� ������ ��ġ�� �׻� �����ϴ�.
//		���� ��ü�� �̵��� �Ÿ���ŭ ���� �ʿ䰡 �ֽ��ϴ�.
GameEngineColor Props::GetColor(const float4& _Position, GameEngineColor _DefaultColor /*= GameEngineColor::WHITE*/)
{
	GameEngineColor ReturnValue;

	if ("" == m_PixelFileName)
	{
		MsgBoxAssert("�����ص� ������ �����ϴ�.");
		return ReturnValue;
	}

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(m_PixelFileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return ReturnValue;
	}

	// �ؽ�ó�� �»�� ������ NDC��ǥ�� ������ �Ÿ��� ���ؾ��մϴ�.
	// �׸��� ���� �Ÿ��� ������ ���� ��ġ�� ���ݴϴ�.
	float4 HalfTexturePos = Texture->GetScale().Half();
	HalfTexturePos.X *= -1.0f;

	float4 MoveCheckPos = Transform.GetLocalPosition() + HalfTexturePos;


	float4 CheckPos = _Position - MoveCheckPos;
	CheckPos.Y *= -1.0f;

	return Texture->GetColor(CheckPos, _DefaultColor);
}