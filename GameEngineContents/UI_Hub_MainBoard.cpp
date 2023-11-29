#include "PreCompile.h"
#include "UI_Hub_MainBoard.h"

#include "UI_QuestUnit.h"

// ���� �������� ����Ʈ�� �����ִ� UI
//
// ����Ű
//  == ��Ȱ��ȭ ���� == 
//  - Tab : ���κ��� ����
// 
//  == Ȱ��ȭ ���� == 
//  - Tab : ���κ��� �ݱ�
//  - ��, �Ʒ� ȭ�� ��ư : ����Ʈ ������ ���� �̵�
//
//  == ���κ��� Ư¡ == 
//  - ���κ��带 ���ų� ���� ��, �� ����Ʈ�� ������ ���Ե� ���� ������ => State ���
//  - ����Ʈ ������ ������ ���̴� ������ �ִ� 3������
//  - ������ 3���� �Ѿ�� ���� �̵����� �Ʒ��κб��� �� �� ����
//  - ���� ������ ����Ű�� ������ Ŀ���� ���
// 
//  == ���κ��� State == 
//  - ���� ���� 
//  - ��ħ ����
//  - ���������� ���� => QuestUnit�� ���� ������
//  - ��ġ������ ���� => QuestUnit�� ���� ������
//  - ��ħ �����϶�, Inputó�� => State���� �߰�
// 
//  
//  == ������ ���� Ư¡ == 
//  - ����Ʈ Ÿ�� (����/���̵�/�ݺ�) << ���⼭�� ���θ� ���
//  - ����Ʈ ����, ����, ������ ũ��, ������ �� ������ ����
//  - ������ ũ��� ���������� �� ������ ���� ���� ũ�Ⱑ �޶���
//  
//

static constexpr int MaxQuestSlot = 3;

QuestManager::QuestManager() 
{
}

QuestManager::~QuestManager() 
{
}

void QuestManager::RegisterData(std::string_view _QuestName)
{
	if (true == IsQuestRegister(_QuestName))
	{
		return;
	}

	UI_Hub_MainBoard::isShowAlertMark = false;

	QuestContainer.push_back(_QuestName.data());
}

void QuestManager::PopData(std::string_view _QuestName)
{
	bool IsPopQuest = false;
	for (std::string_view QuestName : QuestContainer)
	{
		if (QuestName == _QuestName.data())
		{
			QuestContainer.remove(QuestName.data());
			IsPopQuest = true;
			break;
		}
	}

	if (false == IsPopQuest)
	{
		MsgBoxAssert("������ �����Ͱ� �������� �ʽ��ϴ�.");
		return;
	}


	ClearContainer.push_back(_QuestName.data());
}

bool QuestManager::IsQuestRegister(std::string_view _QuestName)
{
	bool ReturnValue = false;

	for (std::string QuestName : ClearContainer)
	{
		if (QuestName == _QuestName)
		{
			ReturnValue = true;
			return false;
		}
	}

	for (std::string QuestName : QuestContainer)
	{
		if (QuestName == _QuestName)
		{
			ReturnValue = true;
			return false;
		}
	}

	return ReturnValue;
}



std::unique_ptr<QuestManager> UI_Hub_MainBoard::s_QuestManager = nullptr;
bool UI_Hub_MainBoard::isShowAlertMark = true;
UI_Hub_MainBoard::UI_Hub_MainBoard() 
{
	if (nullptr == GameEngineSprite::Find("Quest_Notice_Notification.png"))
	{
		GameEngineSprite::CreateCut("Quest_Notice_Notification.png", 3, 3);
	}
}

UI_Hub_MainBoard::~UI_Hub_MainBoard() 
{
}


void UI_Hub_MainBoard::Start()
{
	GameEngineInput::AddInputObject(this);
}

void UI_Hub_MainBoard::Update(float _Delta)
{
	if (false == isShowAlertMark)
	{
		if (nullptr != MainBoard.Alert && false == MainBoard.Alert->IsUpdate())
		{
			MainBoard.Alert->On();
		}
	}

	State.Update(_Delta);
}

void UI_Hub_MainBoard::Release()
{
	s_QuestManager = nullptr;
	for (std::shared_ptr<UI_QuestUnit> QuestUnit : QuestList)
	{
		QuestUnit->Death();
	}
	QuestList.clear();
}

void UI_Hub_MainBoard::LevelEnd(GameEngineLevel* _NextLevel)
{
	State.ChangeState(EMAINBOARDSTATE::None);
}


void UI_Hub_MainBoard::Init()
{
	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Base);
	const float ToggleDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float IndicatorDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Indicator);

	MainBoard.Base = CreateComponent<GameEngineUIRenderer>();
	MainBoard.Base->SetPivotType(PivotType::Left);
	MainBoard.Base->Transform.SetLocalPosition(float4(0.0f, 0.0f, BaseDepth));
	MainBoard.Base->SetSprite("HUD_Quest_Base.png");

	MainBoard.Toggle = CreateComponent<GameEngineUIRenderer>();
	MainBoard.Toggle->SetPivotType(PivotType::Left);
	MainBoard.Toggle->Transform.SetLocalPosition(float4(-44.0f, 110.0f, ToggleDepth));
	MainBoard.Toggle->SetSprite("HUD_Quest_Toggle.png");

	MainBoard.TabButton = CreateComponent<GameEngineUIRenderer>();
	MainBoard.TabButton->Transform.SetLocalPosition(float4(-16.0f, 144.0f, BaseDepth));
	MainBoard.TabButton->SetSprite("ButtonSet_Keyboard_Tab.png");

	MainBoard.Alert = CreateComponent<GameEngineUIRenderer>();
	MainBoard.Alert->Transform.SetLocalPosition(float4(-40.0f, 132.0f, IndicatorDepth));
	MainBoard.Alert->AutoSpriteSizeOn();
	MainBoard.Alert->SetAutoScaleRatio(2.0f);
	MainBoard.Alert->CreateAnimation("Notice", "Quest_Notice_Notification.png", 0.1f, 1);
	MainBoard.Alert->ChangeAnimation("Notice");
	MainBoard.Alert->FindAnimation("Notice")->Inter[0] = 1.0f;
	MainBoard.Alert->Off();


	if (nullptr == s_QuestManager)
	{
		InitQuestManager();
	}

	StateSetting();
	State.ChangeState(EMAINBOARDSTATE::None);
}


void UI_Hub_MainBoard::InitQuestManager()
{
	s_QuestManager = std::make_unique<QuestManager>();
	RegisterQuest("FindLetter");
}

void UI_Hub_MainBoard::RegisterQuest(std::string_view _QuestName)
{
	if (nullptr == s_QuestManager)
	{
		MsgBoxAssert("�Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	s_QuestManager->RegisterData(_QuestName);
	CreateQuestUnit(_QuestName);
}

void UI_Hub_MainBoard::CreateQuestUnit(std::string_view _QuestName)
{
	std::shared_ptr<UI_QuestUnit> Unit = GetLevel()->CreateActor<UI_QuestUnit>(EUPDATEORDER::UIComponent);
	Unit->SetLocalPosition(Transform.GetLocalPosition());
	Unit->MaibBoardPointer = this;
	Unit->Init(_QuestName);

	QuestList.push_back(Unit);
}

void UI_Hub_MainBoard::PopQuest(std::string_view _QuestName)
{
	if (nullptr == s_QuestManager)
	{
		MsgBoxAssert("�Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	s_QuestManager->PopData(_QuestName);
}


void UI_Hub_MainBoard::Open()
{
	if (false == IsSameList())
	{
		RenewUnitList();
	}

	OpenFrom(0);
	GameEngineInput::IsOnlyInputObject(this);
	State.ChangeState(EMAINBOARDSTATE::Open);
}

void UI_Hub_MainBoard::OpenFrom(int _StartSlot)
{
	if (true == QuestList.empty())
	{
		return;
	}

	int SlotNum = 0;
	int OpenSlot = 0;

	float YPos = 150.0f;

	for (std::shared_ptr<UI_QuestUnit>& QuestUnit : QuestList)
	{
		if (SlotNum < _StartSlot)
		{
			++SlotNum;
			continue;
		}
		++SlotNum;
		if (OpenSlot >= MaxQuestSlot)
		{
			break;
		}

		if (nullptr == QuestUnit)
		{
			std::string QuestName = QuestUnit->Data.lock()->QuestName;
			MsgBoxAssert(QuestName + "�������� �ʴ� ����Ʈ�� �ֽ��ϴ�.");
			return;
		}

		QuestUnit->Transform.SetLocalPosition(float4(0.0f, YPos));
		YPos -= QuestUnit->RenderYScale + 10.0f;

		++OpenSlot;
	}
}

void UI_Hub_MainBoard::Close()
{
	GameEngineInput::IsObjectAllInputOn();
}

void UI_Hub_MainBoard::RemoveAllQuestList()
{
	if (true == QuestList.empty())
	{
		return;
	}
	
	for (const std::shared_ptr<UI_QuestUnit>& Quest : QuestList)
	{
		Quest->Death();
	}

	QuestList.clear();
}

void UI_Hub_MainBoard::RenewUnitList()
{
	RemoveAllQuestList();

	for (std::string_view QuestName : s_QuestManager->QuestContainer)
	{
		CreateQuestUnit(QuestName);
	}
}

bool UI_Hub_MainBoard::IsSameList()
{
	if (s_QuestManager->QuestContainer.size() != QuestList.size())
	{
		return false;
	}


	for (std::string_view QuestName : s_QuestManager->QuestContainer)
	{
		bool isQuestReamin = false;

		for (std::shared_ptr<UI_QuestUnit> Unit : QuestList)
		{
			if (true == Unit->Data.expired())
			{
				MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
				return false;
			}

			if (QuestName == Unit->Data.lock()->Name)
			{
				isQuestReamin = true;
				break;
			}
		}

		if (false == isQuestReamin)
		{
			return false;
		}
	}

	return true;
}



void UI_Hub_MainBoard::StateSetting()
{
	CreateStateParameter OpenState;
	OpenState.Start = std::bind(&UI_Hub_MainBoard::StartOpen, this, std::placeholders::_1);
	OpenState.Stay = std::bind(&UI_Hub_MainBoard::UpdateOpen, this, std::placeholders::_1, std::placeholders::_2);
	OpenState.End = std::bind(&UI_Hub_MainBoard::EndOpen, this, std::placeholders::_1);
	State.CreateState(EMAINBOARDSTATE::Open, OpenState);

	CreateStateParameter CloseState;
	CloseState.Start = std::bind(&UI_Hub_MainBoard::StartClose, this, std::placeholders::_1);
	CloseState.Stay = std::bind(&UI_Hub_MainBoard::UpdateClose, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EMAINBOARDSTATE::Close, CloseState);

	CreateStateParameter StayState;
	StayState.Start = std::bind(&UI_Hub_MainBoard::StartStay, this, std::placeholders::_1);
	StayState.Stay = std::bind(&UI_Hub_MainBoard::UpdateStay, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EMAINBOARDSTATE::Stay, StayState);

	CreateStateParameter NoneState;
	NoneState.Start = std::bind(&UI_Hub_MainBoard::StartNone, this, std::placeholders::_1);
	State.CreateState(EMAINBOARDSTATE::None, NoneState);
}

void UI_Hub_MainBoard::StartOpen(GameEngineState* _Parent)
{
	if (false == isShowAlertMark)
	{
		if (nullptr != MainBoard.Alert)
		{
			MainBoard.Alert->Off();
		}

		isShowAlertMark = true;
	}

	const float4& Posision = float4(GlobalValue::GetWindowScale().hX(), 0.0f);
	SetPosAllQuestUnit(Posision);
	Transform.SetLocalPosition(Posision);
}

void UI_Hub_MainBoard::StartStay(GameEngineState* _Parent)
{

}

void UI_Hub_MainBoard::StartClose(GameEngineState* _Parent)
{
	const float4& TexScale = MainBoard.Base->GetSprite()->GetSpriteData(0).Texture->GetScale();
	const float4& Posision = float4(GlobalValue::GetWindowScale().hX() - TexScale.X, 0.0f);
	SetPosAllQuestUnit(Posision);
	Transform.SetLocalPosition(Posision);
}


void UI_Hub_MainBoard::UpdateOpen(float _Delta, GameEngineState* _Parent)
{
	const float4& MovePos = float4(-MoveSpeed * _Delta);
	Transform.AddLocalPosition(MovePos);
	AddPosAllQuestUnit(MovePos);

	const float4& MyPosition = Transform.GetLocalPosition();
	const float4& TexScale = MainBoard.Base->GetSprite()->GetSpriteData(0).Texture->GetScale();
	const float4& CheckPosition = GlobalValue::GetWindowScale().hX() - TexScale.X;
	if (MyPosition.X < CheckPosition.X)
	{
		State.ChangeState(EMAINBOARDSTATE::Stay);
		return;
	}
}

void UI_Hub_MainBoard::UpdateStay(float _Delta, GameEngineState* _Parent)
{
	if (true == GameEngineInput::IsDown(VK_TAB, this))
	{
		State.ChangeState(EMAINBOARDSTATE::Close);
		return;
	}
}

void UI_Hub_MainBoard::UpdateClose(float _Delta, GameEngineState* _Parent)
{
	const float4& MovePos = float4(MoveSpeed * _Delta);
	Transform.AddLocalPosition(MovePos);
	AddPosAllQuestUnit(MovePos);

	const float4& MyPosition = Transform.GetLocalPosition();
	if (MyPosition.X > GlobalValue::GetWindowScale().hX())
	{
		State.ChangeState(EMAINBOARDSTATE::None);
		return;
	}
}


void UI_Hub_MainBoard::EndOpen(GameEngineState* _Parent)
{
	const float4& MyPosition = Transform.GetLocalPosition();
	const float4& TexScale = MainBoard.Base->GetSprite()->GetSpriteData(0).Texture->GetScale();
	const float4& Posision = float4(GlobalValue::GetWindowScale().hX() - TexScale.X + 2.0f , MyPosition.Y);
	SetPosAllQuestUnit(Posision);
	Transform.SetLocalPosition(Posision);
}

void UI_Hub_MainBoard::StartNone(GameEngineState* _Parent)
{
	const float4& MyPosition = Transform.GetLocalPosition();
	const float4& Posision = float4(GlobalValue::GetWindowScale().hX(), MyPosition.Y);
	SetPosAllQuestUnit(Posision);
	Transform.SetLocalPosition(Posision);
	Close();
}

void UI_Hub_MainBoard::AddPosAllQuestUnit(const float4& _Pos)
{
	if (true == QuestList.empty())
	{
		return;
	}

	for (std::weak_ptr<UI_QuestUnit> Unit : QuestList)
	{
		if (true == Unit.expired())
		{
			MsgBoxAssert("����Ʈ �ȿ� �߸��� ���� ����ֽ��ϴ�.");
			return;
		}

		Unit.lock()->AddLocalPosition(_Pos);
	}
}

void UI_Hub_MainBoard::SetPosAllQuestUnit(const float4& _Pos)
{
	if (true == QuestList.empty())
	{
		return;
	}

	for (std::weak_ptr<UI_QuestUnit> Unit : QuestList)
	{
		if (true == Unit.expired())
		{
			MsgBoxAssert("����Ʈ �ȿ� �߸��� ���� ����ֽ��ϴ�.");
			return;
		}

		Unit.lock()->SetLocalPosition(_Pos);
	}
}