#include "PreCompile.h"
#include "UI_InterativeMark.h"


#include "CameraControler.h"
#include "InteractiveActor.h"


UI_InterativeMark* UI_InterativeMark::UI_Mark = nullptr;
InteractiveActor* UI_InterativeMark::Pointer = nullptr;
UI_InterativeMark::UI_InterativeMark() 
{
}

UI_InterativeMark::~UI_InterativeMark() 
{
}


void UI_InterativeMark::Start()
{

}

void UI_InterativeMark::Update(float _Delta)
{
	UpdateMark(_Delta);
}

void UI_InterativeMark::LevelStart(class GameEngineLevel* _NextLevel)
{
	Reset();
}

void UI_InterativeMark::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_InterativeMark::Init()
{
	m_MarkRenderer = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Mark);
	if (nullptr == m_MarkRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_MarkRenderer->CreateAnimation("Mark", "Interaction_Arrow.png", 0.1f);
	m_MarkRenderer->ChangeAnimation("Mark");
	m_MarkRenderer->AutoSpriteSizeOn();


	m_ButtonRenderer = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Mark);
	if (nullptr == m_MarkRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_ButtonRenderer->SetSprite("ButtonSet_Keyboard_Z.png");

	Reset();
}

void UI_InterativeMark::PointThis(InteractiveActor* _ActorPtr)
{
	if (nullptr == _ActorPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���͸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	UI_Mark->IsPointerInteracted = true;

	if (_ActorPtr != Pointer)
	{
		UI_Mark->On();
		Pointer = _ActorPtr;

		if (EINTERACTIONTYPE::Gathering == Pointer->GetInteractionType())
		{
			UI_Mark->m_MarkRenderer->On();
		}
		else if (EINTERACTIONTYPE::Gear == Pointer->GetInteractionType())
		{
			UI_Mark->m_ButtonRenderer->On();
		}
	}
}


void UI_InterativeMark::Reset()
{
	if (nullptr == m_MarkRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	m_MarkRenderer->ChangeAnimation("Mark", true, 0);
	m_MarkRenderer->Off();

	if (nullptr == m_ButtonRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	m_ButtonRenderer->Off();


	UI_Mark = this;
	Pointer = nullptr;
	IsPointerInteracted = false;

	Off();
}


void UI_InterativeMark::UpdateMark(float _Delta)
{
	if (false == IsPointerInteracted)
	{
		Reset();
		return;
	}

	if (nullptr != Pointer)
	{
		if (nullptr == GlobalValue::g_CameraControler)
		{
			MsgBoxAssert("ī�޶� �������� �ʽ��ϴ�");
			return;
		}

		float4 MainCameraPos = GlobalValue::g_CameraControler->GetCameraWorldPosition();
		
		float4 ActorWorldPos = Pointer->Transform.GetWorldPosition();
		float4 Position = ActorWorldPos - MainCameraPos + CONST_MarkPositionToActor;
		Transform.SetLocalPosition(Position);
	}
	else
	{
		MsgBoxAssert("��ü�� �������� �ʽ��ϴ�.");
		return;
	}

	IsPointerInteracted = false;
}