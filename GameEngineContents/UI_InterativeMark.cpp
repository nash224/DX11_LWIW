#include "PreCompile.h"
#include "UI_InterativeMark.h"

#include "OutLineEffect.h"


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
	//OutLine = GetLevel()->GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<OutLineEffect>();
	//OutLine->Off();
}

void UI_InterativeMark::Update(float _Delta)
{
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



void UI_InterativeMark::Init()
{
	if (nullptr == GameEngineSprite::Find("PointArrow.png"))
	{
		GameEngineSprite::CreateCut("PointArrow.png", 3, 2);
	}

	MarkRenderer = CreateComponent<GameEngineUIRenderer>();
	MarkRenderer->CreateAnimation("Mark", "PointArrow.png", 0.1f);
	MarkRenderer->ChangeAnimation("Mark");
	MarkRenderer->AutoSpriteSizeOn();

	ButtonRenderer = CreateComponent<GameEngineUIRenderer>();
	ButtonRenderer->SetSprite("ButtonSet_Keyboard_Z.png");

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

			UI_Mark->MarkRenderer->On();
			/*UI_Mark->OutLine->On();*/
		}
		else if (EINTERACTION_BUTTONTYPE::Gear == Pointer->GetInteractionButtonType())
		{
			UI_Mark->ButtonRenderer->On();
		}

		if (true == UI_Mark->MarkRenderer->IsUpdate() && true == UI_Mark->ButtonRenderer->IsUpdate())
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
	if (nullptr == MarkRenderer || nullptr == ButtonRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	MarkRenderer->ChangeAnimation("Mark", true, 0);
	MarkRenderer->Off();
	ButtonRenderer->Off();

	//if (nullptr == OutLine)
	//{
	//	MsgBoxAssert("Effect가 존재하지 않습니다.");
	//	return;
	//}

	//OutLine->Off();

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

		const float4& MarkPositionToActor = float4{ 0.0f , 48.0f };
		const float4& MainCameraPos = GlobalValue::g_CameraControler->GetCameraWorldPosition();
		const float4& ActorWorldPos = Pointer->Transform.GetWorldPosition();

		float4 Position = ActorWorldPos - MainCameraPos + MarkPositionToActor;
		Position.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Mark);
		Transform.SetLocalPosition(Position);
	}
	else
	{
		MsgBoxAssert("객체가 존재하지 않습니다.");
		return;
	}

	IsPointerInteracted = false;
}