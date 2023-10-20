#include "PreCompile.h"
#include "FadeObject.h"

#include "CameraControler.h"

FadeObject::FadeObject()
{
}

FadeObject::~FadeObject()
{
}


void FadeObject::Start()
{

}


void FadeObject::Update(float _Delta)
{
	UpdateFade(_Delta);
}

void FadeObject::Release()
{
	m_FadeRenderer = nullptr;
}

void FadeObject::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void FadeObject::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void FadeObject::CallFadeOut(std::string_view _NextLevelName, float _FadeOutDuration /*= 1.0f*/)
{
	m_FadeDuration = _FadeOutDuration;
	m_FadeType = CallFadeType::FadeOut;
	m_NextLevelName = _NextLevelName;
	Init();
}

void FadeObject::CallFadeIn(float _FadeOutDuration /*= 1.0f*/)
{
	m_FadeDuration = _FadeOutDuration;
	m_FadeType = CallFadeType::FadeIn;
	Init();
}



void FadeObject::Init()
{
	RendererSetting();
	PositionSetting();

	if (nullptr == m_FadeRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (CallFadeType::FadeOut == m_FadeType)
	{
		m_AlphaValue = 0.0f;
		m_FadeRenderer->GetColorData().MulColor.A = 0.0f;
	}
	else
	{
		m_AlphaValue = 1.0f;
	}
}

void FadeObject::RendererSetting()
{
	m_FadeRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::Fade);
	if (nullptr == m_FadeRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	float4 WinScale = GlobalValue::GetWindowScale();

	// ũ��
	m_FadeRenderer->SetSprite("Fade_Texture.png");
	m_FadeRenderer->GetImageTransform().SetLocalScale(WinScale);
}


void FadeObject::PositionSetting()
{
	float FadeDepth = GlobalUtils::CalculateDepth(ERENDERDEPTH::FadeObject);
	Transform.SetLocalPosition({ 0.0f, 0.0f, FadeDepth });
}

void FadeObject::UpdateFade(float _Delta)
{
	if (CallFadeType::FadeOut == m_FadeType)
	{
		m_AlphaValue += _Delta / m_FadeDuration;


		if (nullptr == m_FadeRenderer)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
			return;
		}

		bool IsOver = false;
		if (m_AlphaValue > 1.0f)
		{
			m_AlphaValue = 1.0f;
			IsOver = true;
		}

		m_FadeRenderer->GetColorData().MulColor.A = m_AlphaValue;

		if (true == IsOver)
		{
			m_FadeType = CallFadeType::None;
			GameEngineCore::ChangeLevel(m_NextLevelName);
		}

	}

	if (CallFadeType::FadeIn == m_FadeType)
	{
		m_AlphaValue -= _Delta / m_FadeDuration;


		if (nullptr == m_FadeRenderer)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
			return;
		}

		bool IsOver = false;
		if (m_AlphaValue <= 0.0f)
		{
			m_AlphaValue = 0.0f;
			Death();
			return;
		}

		m_FadeRenderer->GetColorData().MulColor.A = m_AlphaValue;

		Transform.GetLocalPosition();
	}
}