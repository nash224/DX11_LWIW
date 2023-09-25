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
	m_FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::FadeObject);
	if (nullptr == m_FadeRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	float4 WinScale = GlobalValue::GetWindowScale();

	m_FadeRenderer->SetSprite("Fade_Texture.png");
	m_FadeRenderer->Transform.SetLocalScale(WinScale);


	float4 CameraPos = GlobalValue::g_CameraControler->GetCameraCurrentPostion();
	m_FadeRenderer->Transform.SetLocalPosition(CameraPos);
}

void FadeObject::Update(float _Delta)
{

}

void FadeObject::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void FadeObject::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void FadeObject::CallFadeOut(std::shared_ptr<GameEngineLevel> _Level, std::function<void()> _Func, float _FadeOutDuration /*= 1.0f*/)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("Level을 불러오지 못했습니다.");
		return;
	}

	std::shared_ptr<FadeObject> FadeOutObject = _Level->CreateActor<FadeObject>(EUPDATEORDER::Fade);
	if (nullptr == FadeOutObject)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}


	FadeOutObject->m_FadeType = CallFadeType::FadeOut;
	FadeOutObject->m_Func = _Func;

	FadeOutObject->m_FadeDuration = _FadeOutDuration;


	//if (nullptr != FadeOutObject->m_FadeRenderer)
	//{
	//	FadeOutObject->m_FadeRenderer->;
	//}
}

void FadeObject::CallFadeIn(std::shared_ptr<GameEngineLevel> _Level, float _FadeOutDuration /*= 1.0f*/)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("Level을 불러오지 못했습니다.");
		return;
	}

	/*FadeObject* FadeIn = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == FadeIn)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	FadeIn->m_Alpha = _Alpha;

	FadeIn->m_FadeDuration = _FadeOutDuration;
	FadeIn->m_RequestAlphaValue = _Alpha;

	FadeIn->m_FadeType = CallFadeType::FadeIn;

	if (FadeIn->Renderer)
	{
		FadeIn->Renderer->SetAlpha(_Alpha);
	}*/
}
