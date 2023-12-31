#include "PreCompile.h"
#include "UI_Drop.h"

#include "ItemData.h"
#include "UI_DropManager.h"

#include "ItemData.h"

#define SYSTEM_NOTICE_ITEM_FRIST_POSITION { -384.0f , -4.0f }
#define SYSTEM_NOTICE_ITEM_GAP 42.0f
#define SYSTEM_NOTICE_ITEM_MOVETIME 0.2f

#define SYSTEM_NOTICE_STAYTIME 2.4f



UI_Drop::UI_Drop() 
{
}

UI_Drop::~UI_Drop() 
{
}


void UI_Drop::Start()
{
	UILine = 0;
}

void UI_Drop::Update(float _Delta)
{
	PositionState.Update(_Delta);
	ColorState.Update(_Delta);
}

void UI_Drop::Release()
{
	ItemDrop.SystemNotice_Base = nullptr;
	ItemDrop.Item_Img = nullptr;
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
	std::weak_ptr<ItemData> itemData = ItemData::Find(_ItemName);
	if (true == itemData.expired())
	{
		MsgBoxAssert("아이템 데이터를 찾지 못했습니다.");
		return;
	}

	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Base);
	const float IconDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Img);
	const float NameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Alert_Font);

	ItemDrop.SystemNotice_Base = CreateComponent<GameEngineUIRenderer>();
	ItemDrop.SystemNotice_Base->Transform.SetLocalPosition(float4(0.0f, 0.0f, BaseDepth));
	ItemDrop.SystemNotice_Base->SetSprite("SystemNotice_Item.png");


	ItemDrop.Item_Img = CreateComponent<GameEngineUIRenderer>();
	ItemDrop.Item_Img->Transform.SetLocalPosition(float4(-52.0f, 0.0f, IconDepth));
	ItemDrop.Item_Img->SetSprite(itemData.lock()->Name + ".png");

	const float FontSize = 15.0f;

	ItemDrop.ItemName = CreateComponent<GameEngineUIRenderer>();
	ItemDrop.ItemName->SetText(GlobalValue::Font_Sandoll, itemData.lock()->KoreanName, FontSize, float4::WHITE);
	ItemDrop.ItemName->Transform.SetLocalPosition(float4(-30.0f, 7.0f, NameDepth));

	AddColorData(0.0f);
}

// 알파값 설정
void UI_Drop::AddColorData(float _AddValue)
{
	if (nullptr == ItemDrop.SystemNotice_Base)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}
	
	if (nullptr == ItemDrop.Item_Img)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	ItemDrop.SystemNotice_Base->GetColorData().MulColor.A = _AddValue;
	ItemDrop.Item_Img->GetColorData().MulColor.A = _AddValue;
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
	++UILine;
	PositionState.ChangeState(ENOTICEPOSITIONSTATE::Awake);
}


void UI_Drop::StartAwake(GameEngineState* _Parent)
{
	m_TargetPosition = float4(SYSTEM_NOTICE_ITEM_FRIST_POSITION).Y - UILine * SYSTEM_NOTICE_ITEM_GAP;
}

void UI_Drop::UpdateAwake(float _Delta, GameEngineState* _Parent)
{
	// 속도만큼 더해줍니다.
	float Speed = SYSTEM_NOTICE_ITEM_GAP * _Delta / SYSTEM_NOTICE_ITEM_MOVETIME;
	Transform.AddLocalPosition(float4(0.0f, -Speed));


	if (UILine >= 4 && false == isDisappear)
	{
		isDisappear = true;
		ColorState.ChangeState(ENOTICECOLORSTATE::Disappear);
	}

	if (Transform.GetLocalPosition().Y < m_TargetPosition)
	{
		float4 TargetPosition = SYSTEM_NOTICE_ITEM_FRIST_POSITION;
		TargetPosition.Y -= UILine * SYSTEM_NOTICE_ITEM_GAP;
		Transform.SetLocalPosition( TargetPosition );

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
			MsgBoxAssert("매니저를 모릅니다.");
			return;
		}

		ManagerPtr->GetSystemNoticeList().remove(GetDynamic_Cast_This<UI_Drop>());

		Death();
	}
}