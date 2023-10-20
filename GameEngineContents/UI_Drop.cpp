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
}

void UI_Drop::Release()
{
}

void UI_Drop::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void UI_Drop::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
	m_ItemDropRenderer.SystemNotice_Base = nullptr;
	m_ItemDropRenderer.Item_Img = nullptr;
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
		MsgBoxAssert("아이템 데이터를 찾지 못했습니다.");
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

	/*AddColorData(-1.0f);*/
}

// 알파값 설정
void UI_Drop::AddColorData(float _AddValue)
{
	if (nullptr == m_ItemDropRenderer.SystemNotice_Base)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}
	
	if (nullptr == m_ItemDropRenderer.Item_Img)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	m_ItemDropRenderer.SystemNotice_Base->GetColorData().PlusColor.A = _AddValue;
	m_ItemDropRenderer.Item_Img->GetColorData().PlusColor.A = _AddValue;
}


void UI_Drop::StateSetting()
{
	CreateStateParameter Para;
	Para.Start = std::bind(&UI_Drop::StartAwake, this, std::placeholders::_1);
	Para.Stay = std::bind(&UI_Drop::UpdateAwake, this, std::placeholders::_1, std::placeholders::_2);
	PositionState.CreateState(ENOTICEPOSITIONSTATE::Awake, Para);
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
	// 속도만큼 더해줍니다.
	float Speed = SYSTEM_NOTICE_ITEM_GAP * _Delta / SYSTEM_NOTICE_ITEM_MOVETIME;
	Transform.AddLocalPosition(float4(0.0f, -Speed));

	// 특정 위치만큼 넘어가면 상태를 바꿔줍니다.
	if (Transform.GetLocalPosition().Y < m_TargetPosition)
	{
		float4 TargetPosition = SYSTEM_NOTICE_ITEM_FRIST_POSITION;
		TargetPosition.Y -= m_Line * SYSTEM_NOTICE_ITEM_GAP;
		Transform.SetLocalPosition( TargetPosition );
		PositionState.ChangeState(ENOTICEPOSITIONSTATE::Stay);
		return;
	}
}