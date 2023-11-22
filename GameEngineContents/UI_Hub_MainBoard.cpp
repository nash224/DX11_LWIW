#include "PreCompile.h"
#include "UI_Hub_MainBoard.h"


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

std::unique_ptr<QuestManager> UI_Hub_MainBoard::s_QuestManager;
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

void UI_Hub_MainBoard::Update(float _Delta)
{
}

void UI_Hub_MainBoard::Release()
{
	s_QuestManager = nullptr;
}

void UI_Hub_MainBoard::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void UI_Hub_MainBoard::LevelEnd(class GameEngineLevel* _NextLevel)
{
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

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
	const std::shared_ptr<QuestData>& Data = QuestData::Find(_QuestName);
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
		return;
	}

	std::shared_ptr<UI_Hub_MainBoard::QuestUnitInfo> Unit = std::make_shared<UI_Hub_MainBoard::QuestUnitInfo>();
	Unit->Parent = this;
	Unit->Data = Data;
	Unit->Init();

	UnitList.push_back(Unit);
}

static constexpr float ContentFontSize = 12.0f;

void UI_Hub_MainBoard::QuestUnitInfo::Init()
{
	if (true == Data.expired())
	{
		MsgBoxAssert("등록되지 않은 퀘스트를 참조하려 했습니다.");
		return;
	}

	SubjectBase = Parent->CreateComponent<GameEngineUIRenderer>();
	SubjectBase->SetSprite("HUD_Quest_Content_1.png");

	static constexpr float QuestNameFontSize = 15.0f;

	Subject = Parent->CreateComponent<GameEngineUIRenderer>();
	Subject->SetText(GlobalValue::Font_Sandoll, GetSubjectTextToType(Data.lock()->QuestType), ContentFontSize, float4::WHITE);

	ContentBase = Parent->CreateComponent<GameEngineUIRenderer>();
	ContentBase->SetSprite("HUD_Quest_Content_1.png");

	QuestName = Parent->CreateComponent<GameEngineUIRenderer>();
	QuestName->SetText(GlobalValue::Font_Sandoll, Data.lock()->QuestName, QuestNameFontSize, float4::ZERO);

	QuestContent = Parent->CreateComponent<GameEngineUIRenderer>();
	QuestContent->SetText(GlobalValue::Font_Sandoll, Data.lock()->Contents, ContentFontSize, float4::WHITE);

	Dot = Parent->CreateComponent<GameEngineUIRenderer>();
	Dot->SetText(GlobalValue::Font_Sandoll, std::string("●"), ContentFontSize, float4::WHITE);
}

std::string UI_Hub_MainBoard::QuestUnitInfo::GetSubjectTextToType(EQUESTTYPE _Type)
{
	std::string ReturnValue;

	switch (_Type)
	{
	case EQUESTTYPE::Main:
		ReturnValue = "메인";
		break;
	case EQUESTTYPE::Side:
		ReturnValue = "사이드";
		break;
	case EQUESTTYPE::Repeat:
		ReturnValue = "반복";
		break;
	case EQUESTTYPE::None:
		break;
	default:
		break;
	}

	return ReturnValue;
}

float UI_Hub_MainBoard::QuestUnitInfo::GetRenderYSize(int _ContentLineCount)
{
	static constexpr float ContentBasicYSize = 100.0f;

	std::weak_ptr<GameEngineTexture> SubjectBaseTexture = GameEngineTexture::Find("HUD_Quest_Content_1.png");
	if (true == SubjectBaseTexture.expired())
	{
		MsgBoxAssert("등록되지 않은 텍스처를 참조하려했습니다.");
		return 0.0f;
	}

	const float4& TextureScale = SubjectBaseTexture.lock()->GetScale();
	const float SubjectBaseYSize = TextureScale.Y + ContentBasicYSize + ContentFontSize * static_cast<float>(_ContentLineCount);
	return SubjectBaseYSize;
}


void UI_Hub_MainBoard::PopQuest(std::string_view _QuestName)
{
	if (nullptr == s_QuestManager)
	{
		MsgBoxAssert("매니저가 존재하지 않습니다.");
		return;
	}

	s_QuestManager->PopData(_QuestName);
}

void UI_Hub_MainBoard::FindQuest(std::string_view _QuestName)
{

}