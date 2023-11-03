#include "PreCompile.h"
#include "UI_Alert_Base.h"


const float4 UI_Alert_Base::InitialFontColor = float4(0.85f, 0.85f, 0.85f, 1.0f);
UI_Alert_Base::UI_Alert_Base() 
{
}

UI_Alert_Base::~UI_Alert_Base() 
{
}


void UI_Alert_Base::Update(float _Delta)
{
	State.Update(_Delta);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////





void UI_Alert_Base::FSMSetting()
{
	CreateStateParameter FadeInState;
	FadeInState.Start = std::bind(&UI_Alert_Base::StartFadeIn, this, std::placeholders::_1);
	FadeInState.Stay = std::bind(&UI_Alert_Base::UpdateFadeIn, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EENTERSTATE::FadeIn, FadeInState);

	CreateStateParameter StayState;
	StayState.Stay = std::bind(&UI_Alert_Base::UpdateStay, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EENTERSTATE::Stay, StayState);

	CreateStateParameter FadeOutState;
	FadeOutState.Stay = std::bind(&UI_Alert_Base::UpdateFadeOut, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EENTERSTATE::FadeOut, FadeOutState);

	State.ChangeState(EENTERSTATE::FadeIn);
}


void UI_Alert_Base::ChangeState(EENTERSTATE _State)
{
	State.ChangeState(_State);
}


void UI_Alert_Base::ChangeMulColor(std::weak_ptr<GameEngineUIRenderer> _Member, float _ColorRatio)
{
	if (true == _Member.expired())
	{
		MsgBoxAssert("존재하지 않는 포인터를 참조했습니다.");
		return;
	}

	_Member.lock()->GetColorData().MulColor.A = _ColorRatio;
}

void UI_Alert_Base::ChangeFontAlpha(std::weak_ptr<GameEngineUIRenderer> _Font, float _ColorRatio)
{
	if (true == _Font.expired())
	{
		MsgBoxAssert("포인터가 없습니다.");
		return;
	}

	_Font.lock()->SetTextAlpha(_ColorRatio);
}

void UI_Alert_Base::ChangeAutoScaleRatio(std::weak_ptr<GameEngineUIRenderer> _Member, const float4& _ScaleRatio)
{
	if (true == _Member.expired())
	{
		return;
	}

	_Member.lock()->SetAutoScaleRatio(_ScaleRatio);
}