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
	// UI_Mark가 현재 레벨에서 사용하고 있지 않다면 초기화
	if (this != UI_Mark)
	{
		Reset();
	}
	

	UpdateMark(_Delta);
}

void UI_InterativeMark::LevelStart(class GameEngineLevel* _NextLevel)
{
	Reset();
}

void UI_InterativeMark::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Reset();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_InterativeMark::Init()
{
	if (nullptr == GameEngineSprite::Find("PointArrow.png"))
	{
		GameEngineSprite::CreateCut("PointArrow.png", 3, 2);
	}


	m_MarkRenderer = CreateComponent<GameEngineUIRenderer>();
	if (nullptr == m_MarkRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_MarkRenderer->CreateAnimation("Mark", "PointArrow.png", 0.1f);
	m_MarkRenderer->ChangeAnimation("Mark");
	m_MarkRenderer->AutoSpriteSizeOn();


	m_ButtonRenderer = CreateComponent<GameEngineUIRenderer>();
	if (nullptr == m_MarkRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_ButtonRenderer->SetSprite("ButtonSet_Keyboard_Z.png");

	Reset();
}

void UI_InterativeMark::PointThis(InteractiveActor* _ActorPtr)
{
	if (nullptr == _ActorPtr)
	{
		MsgBoxAssert("존재하지 않는 액터를 참조하려고 했습니다.");
		return;
	}

	if (_ActorPtr != Pointer)
	{
		UI_Mark->Reset();

		UI_Mark->IsPointerInteracted = true;

		Pointer = _ActorPtr;

		if (EINTERACTION_BUTTONTYPE::Gathering == Pointer->GetInteractionButtonType())
		{
			if (nullptr != _ActorPtr->BodyRenderer)
			{
				_ActorPtr->BodyRenderer->RenderBaseInfoValue.Target1 = 1;
			}

			UI_Mark->m_MarkRenderer->On();
		}
		else if (EINTERACTION_BUTTONTYPE::Gear == Pointer->GetInteractionButtonType())
		{
			UI_Mark->m_ButtonRenderer->On();
		}

		if (true == UI_Mark->m_MarkRenderer->IsUpdate() && true == UI_Mark->m_ButtonRenderer->IsUpdate())
		{
			MsgBoxAssert("버튼이 2개들어올리가 없어..");
			return;
		}
	}
	else
	{
		UI_Mark->IsPointerInteracted = true;
	}
}


void UI_InterativeMark::Reset()
{
	if (nullptr == m_MarkRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_MarkRenderer->ChangeAnimation("Mark", true, 0);
	m_MarkRenderer->Off();

	if (nullptr == m_ButtonRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_ButtonRenderer->Off();


	if (nullptr != Pointer && nullptr != Pointer->BodyRenderer)
	{
		Pointer->BodyRenderer->RenderBaseInfoValue.Target1 = 0;
	}

	UI_Mark = this;
	Pointer = nullptr;
	IsPointerInteracted = false;
	IsLevelChange = false;
}


void UI_InterativeMark::CurLevelPointer()
{
	UI_Mark = this;
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
			MsgBoxAssert("카메라가 존재하지 않습니다");
			return;
		}

		float4 MainCameraPos = GlobalValue::g_CameraControler->GetCameraWorldPosition();
		
		float4 ActorWorldPos = Pointer->Transform.GetWorldPosition();
		float4 Position = ActorWorldPos - MainCameraPos + CONST_MarkPositionToActor;
		Position.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Mark);
		Transform.SetLocalPosition(Position);
	}
	else
	{
		MsgBoxAssert("객체가 존재하지 않습니다.");
		return;
	}

	IsPointerInteracted = false;
}