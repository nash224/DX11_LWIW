#include "PreCompile.h"
#include "UI_Drop.h"

#include "ItemData.h"
#include "UI_DropManager.h"


UI_Drop::UI_Drop() 
{
}

UI_Drop::~UI_Drop() 
{
}


void UI_Drop::Start()
{
	m_Line = 0;
}

void UI_Drop::Update(float _Delta)
{
	PositionState.Update(_Delta);
	ColorState.Update(_Delta);
}

void UI_Drop::Release()
{
	m_ItemDropRenderer.SystemNotice_Base = nullptr;
	m_ItemDropRenderer.Item_Img = nullptr;
	ManagerPtr = nullptr;
}

void UI_Drop::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void UI_Drop::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Drop::Init(std::string_view _ItemName)
{
	RendererSetting(_ItemName);
	StateSetting();
	Transform.SetLocalPosition(SYSTEM_NOTICE_ITEM_FRIST_POSITION);
}

void UI_Drop::RendererSetting(std::string_view _ItemName)
{
	std::shared_ptr<ItemData> ItemData = ItemData::Find(_ItemName);
	if (nullptr == ItemData)
	{
		MsgBoxAssert("������ �����͸� ã�� ���߽��ϴ�.");
		return;
	}


	float4 Position = float4(0.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Base));
	m_ItemDropRenderer.SystemNotice_Base = CreateComponent<GameEngineUIRenderer>();
	m_ItemDropRenderer.SystemNotice_Base->Transform.SetLocalPosition(Position);
	m_ItemDropRenderer.SystemNotice_Base->SetSprite("SystemNotice_Item.png");


	Position = float4(-52.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Icon));
	m_ItemDropRenderer.Item_Img = CreateComponent<GameEngineUIRenderer>();
	m_ItemDropRenderer.Item_Img->Transform.SetLocalPosition(Position);
	m_ItemDropRenderer.Item_Img->SetSprite(ItemData->Name + ".png");

	AddColorData(0.0f);
}

// ���İ� ����
void UI_Drop::AddColorData(float _AddValue)
{
	if (nullptr == m_ItemDropRenderer.SystemNotice_Base)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}
	
	if (nullptr == m_ItemDropRenderer.Item_Img)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_ItemDropRenderer.SystemNotice_Base->GetColorData().MulColor.A = _AddValue;
	m_ItemDropRenderer.Item_Img->GetColorData().MulColor.A = _AddValue;
}


void UI_Drop::StateSetting()
{
	CreateStateParameter PositionPara;
	PositionPara.Start = std::bind(&UI_Drop::StartAwake, this, std::placeholders::_1);
	PositionPara.Stay = std::bind(&UI_Drop::UpdateAwake, this, std::placeholders::_1, std::placeholders::_2);
	PositionState.CreateState(ENOTICEPOSITIONSTATE::Awake, PositionPara);

	CreateStateParameter ColorAppearPara;
	ColorAppearPara.Start = std::bind(&UI_Drop::StartAppear, this, std::placeholders::_1);
	ColorAppearPara.Stay = std::bind(&UI_Drop::UpdateAppear, this, std::placeholders::_1, std::placeholders::_2);
	ColorState.CreateState(ENOTICECOLORSTATE::Appear, ColorAppearPara);

	CreateStateParameter ColorStayPara;
	ColorStayPara.Start = std::bind(&UI_Drop::StartStay, this, std::placeholders::_1);
	ColorStayPara.Stay = std::bind(&UI_Drop::UpdateStay, this, std::placeholders::_1, std::placeholders::_2);
	ColorState.CreateState(ENOTICECOLORSTATE::Stay, ColorStayPara);

	CreateStateParameter ColorDisappearPara;
	ColorDisappearPara.Start = std::bind(&UI_Drop::StartDisappear, this, std::placeholders::_1);
	ColorDisappearPara.Stay = std::bind(&UI_Drop::UpdateDisappear, this, std::placeholders::_1, std::placeholders::_2);
	ColorState.CreateState(ENOTICECOLORSTATE::Disappear, ColorDisappearPara);
	ColorState.ChangeState(ENOTICECOLORSTATE::Appear);
}


void UI_Drop::MoveUnderLine()
{
	++m_Line;
	PositionState.ChangeState(ENOTICEPOSITIONSTATE::Awake);
}


void UI_Drop::StartAwake(GameEngineState* _Parent)
{
	m_TargetPosition = float4(SYSTEM_NOTICE_ITEM_FRIST_POSITION).Y - m_Line * SYSTEM_NOTICE_ITEM_GAP;
}

void UI_Drop::UpdateAwake(float _Delta, GameEngineState* _Parent)
{
	// �ӵ���ŭ �����ݴϴ�.
	float Speed = SYSTEM_NOTICE_ITEM_GAP * _Delta / SYSTEM_NOTICE_ITEM_MOVETIME;
	Transform.AddLocalPosition(float4(0.0f, -Speed));

	// Ư�� ��ġ��ŭ �Ѿ�� ���¸� �ٲ��ݴϴ�.
	if (Transform.GetLocalPosition().Y < m_TargetPosition)
	{
		float4 TargetPosition = SYSTEM_NOTICE_ITEM_FRIST_POSITION;
		TargetPosition.Y -= m_Line * SYSTEM_NOTICE_ITEM_GAP;
		Transform.SetLocalPosition( TargetPosition );

		// 4��° �����̸� �����˴ϴ�
		if (m_Line == 4)
		{
			if (nullptr == ManagerPtr)
			{
				MsgBoxAssert("�Ŵ����� �𸨴ϴ�.");
				return;
			}

			ManagerPtr->GetSystemNoticeList().remove(GetDynamic_Cast_This<UI_Drop>());

			Death();
		}

		PositionState.ChangeState(ENOTICEPOSITIONSTATE::Stay);
		return;
	}
}



void UI_Drop::StartAppear(GameEngineState* _Parent)
{

}

void UI_Drop::UpdateAppear(float _Delta, GameEngineState* _Parent)
{
	if (true == IsFirst)
	{
		IsFirst = false;
		return;
	}

	m_MulColor += _Delta / SYSTEM_NOTICE_ITEM_MOVETIME;
	AddColorData(m_MulColor);

	if (_Parent->GetStateTime() > SYSTEM_NOTICE_ITEM_MOVETIME)
	{
		_Parent->ChangeState(ENOTICECOLORSTATE::Stay);
	}
}

void UI_Drop::StartStay(GameEngineState* _Parent)
{
	AddColorData(1.0f);
}

void UI_Drop::UpdateStay(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > SYSTEM_NOTICE_STAYTIME)
	{
		_Parent->ChangeState(ENOTICECOLORSTATE::Disappear);
	}
}

void UI_Drop::StartDisappear(GameEngineState* _Parent)
{

}

void UI_Drop::UpdateDisappear(float _Delta, GameEngineState* _Parent)
{
	m_MulColor -= _Delta / SYSTEM_NOTICE_ITEM_MOVETIME;
	AddColorData(m_MulColor);

	if (_Parent->GetStateTime() > SYSTEM_NOTICE_ITEM_MOVETIME)
	{
		if (nullptr == ManagerPtr)
		{
			MsgBoxAssert("�Ŵ����� �𸨴ϴ�.");
			return;
		}

		ManagerPtr->GetSystemNoticeList().remove(GetDynamic_Cast_This<UI_Drop>());

		Death();
	}
}