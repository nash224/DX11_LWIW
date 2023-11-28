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

	QuestContainer.push_back(_QuestName.data());
}

void QuestManager::PopData(std::string_view _QuestName)
{
	ClearContainer.push_back(_QuestName.data());
	QuestContainer.remove(_QuestName.data());
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
UI_Hub_MainBoard::UI_Hub_MainBoard() 
{
}

UI_Hub_MainBoard::~UI_Hub_MainBoard() 
{
}


void UI_Hub_MainBoard::Start()
{
	GameEngineInput::AddInputObject(this);
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

void UI_Hub_MainBoard::LevelStart(GameEngineLevel* _NextLevel)
{
	RenewUnitList();
}

void UI_Hub_MainBoard::LevelEnd(GameEngineLevel* _NextLevel)
{
	RemoveAllQuestList();
}


void UI_Hub_MainBoard::Init()
{
	if (nullptr == s_QuestManager)
	{
		InitQuestManager();
	}
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
	Unit->ChangeParent(this, static_cast<int>(EUPDATEORDER::UIComponent));
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
	for (std::shared_ptr<UI_QuestUnit> Unit : QuestList)
	{
		if (false == Unit->Data.expired() && _QuestName == Unit->Data.lock()->QuestName)
		{
			QuestList.remove(Unit);
			return;
		}
	}

	MsgBoxAssert("����Ʈ�� �������� ���߽��ϴ�.");
	return;
}


void UI_Hub_MainBoard::Open()
{
	OpenFrom(0);
}

void UI_Hub_MainBoard::OpenFrom(int _StartSlot)
{
	int SlotNum = 0;
	int OpenSlot = 0;
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

		const float YPos = QuestUnit->RenderYScale + 10.0f * static_cast<float>(OpenSlot);
		QuestUnit->Transform.SetLocalPosition(float4(0.0f, YPos));
		++OpenSlot;
	}
}

void UI_Hub_MainBoard::Close()
{

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
	for (std::shared_ptr<UI_QuestUnit> Unit : QuestList)
	{
		if (true == Unit->Data.expired())
		{
			MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
			return false;
		}

		bool isQuestReamin = false;

		for (std::string_view QuestName : s_QuestManager->QuestContainer)
		{
			if (QuestName == Unit->Data.lock()->QuestName)
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

// GameEngineInput::IsOnlyInputObject(this);