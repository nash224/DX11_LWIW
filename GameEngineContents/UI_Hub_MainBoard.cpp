#include "PreCompile.h"
#include "UI_Hub_MainBoard.h"

#include "UI_QuestUnit.h"

// 현재 진행중인 퀘스트를 보여주는 UI
//
// 조작키
//  == 비활성화 상태 == 
//  - Tab : 메인보드 열기
// 
//  == 활성화 상태 == 
//  - Tab : 메인보드 닫기
//  - 위, 아래 화살 버튼 : 퀘스트 컨텐츠 슬롯 이동
//
//  == 메인보드 특징 == 
//  - 메인보드를 열거나 닫을 때, 한 퀘스트의 컨텐츠 슬롯도 같이 움직임 => State 사용
//  - 퀘스트 컨텐츠 슬롯이 보이는 영역은 최대 3개까지
//  - 슬롯이 3개가 넘어가면 슬롯 이동으로 아랫부분까지 볼 수 있음
//  - 현재 슬롯을 가리키는 영역은 커서를 사용
// 
//  == 메인보드 State == 
//  - 접힘 상태 
//  - 펼침 상태
//  - 접히는중인 상태 => QuestUnit도 같이 움직임
//  - 펼치는중인 상태 => QuestUnit도 같이 움직임
//  - 펼침 상태일때, Input처리 => State상태 추가
// 
//  
//  == 컨텐츠 슬롯 특징 == 
//  - 퀘스트 타입 (메인/사이드/반복) << 여기서는 메인만 사용
//  - 퀘스트 내용, 주제, 컨텐츠 크기, 컨텐츠 줄 내용이 있음
//  - 컨텐츠 크기는 가변적으로 줄 개행의 수에 따라 크기가 달라짐
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
		MsgBoxAssert("매니저가 존재하지 않습니다.");
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
		MsgBoxAssert("매니저가 존재하지 않습니다.");
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

	MsgBoxAssert("퀘스트를 제거하지 못했습니다.");
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
			MsgBoxAssert(QuestName + "존재하지 않는 퀘스트가 있습니다.");
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
			MsgBoxAssert("데이터가 존재하지 않습니다.");
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