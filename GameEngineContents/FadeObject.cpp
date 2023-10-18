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



void FadeObject::CallFadeOut(GameEngineLevel* _Level, std::string_view _NextLevelName ,float _FadeOutDuration /*= 1.0f*/)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("Level�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	std::shared_ptr<FadeObject> FadeOutObject = _Level->CreateActor<FadeObject>(EUPDATEORDER::Fade);
	if (nullptr == FadeOutObject)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	FadeOutObject->m_FadeDuration = _FadeOutDuration;
	FadeOutObject->m_FadeType = CallFadeType::FadeOut;
	FadeOutObject->m_NextLevelName = _NextLevelName;
	FadeOutObject->Init();
}

void FadeObject::CallFadeIn(GameEngineLevel* _Level, float _FadeOutDuration /*= 1.0f*/)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("Level�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	std::shared_ptr<FadeObject> FadeInObject = _Level->CreateActor<FadeObject>(EUPDATEORDER::Fade);
	if (nullptr == FadeInObject)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	FadeInObject->m_FadeDuration = _FadeOutDuration;
	FadeInObject->m_FadeType = CallFadeType::FadeIn;
	FadeInObject->Init();
}



void FadeObject::Init()
{
	RendererSetting();

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
	m_FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Fade);
	if (nullptr == m_FadeRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	float4 WinScale = GlobalValue::GetWindowScale();

	// ũ��
	m_FadeRenderer->SetSprite("Fade_Texture.png");
	m_FadeRenderer->Transform.SetLocalScale(WinScale);
}


void FadeObject::UpdateFade(float _Delta) 
{
	PositionSetting();

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
	}
}


void FadeObject::PositionSetting()
{
	if (nullptr == GlobalValue::g_CameraControler)
	{
		MsgBoxAssert("���� ī�޶� �������� �ʽ��ϴ�.");
		return;
	}

	float4 CameraPos = GlobalValue::g_CameraControler->GetCameraCurrentPostion();
	CameraPos.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::FadeObject);
	m_FadeRenderer->Transform.SetLocalPosition(CameraPos);
}