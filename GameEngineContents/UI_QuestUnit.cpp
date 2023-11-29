#include "PreCompile.h"
#include "UI_QuestUnit.h"
#include "UI_Hub_MainBoard.h"

static constexpr float ContentFontSize = 15.0f;
static constexpr float SubjectBaseYRenderScale = 24.0f;


UI_QuestUnit::UI_QuestUnit() 
{
}

UI_QuestUnit::~UI_QuestUnit() 
{
}


void UI_QuestUnit::Release()
{
	QuestUnit.ContentBase = nullptr;
	QuestUnit.Dot = nullptr;
	QuestUnit.QuestContent = nullptr;
	QuestUnit.QuestName = nullptr;
	QuestUnit.Subject = nullptr;
	QuestUnit.SubjectBase = nullptr;
}

void UI_QuestUnit::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();

	if (nullptr != MaibBoardPointer)
	{
		std::list<std::shared_ptr<UI_QuestUnit>>::iterator StartIter = MaibBoardPointer->QuestList.begin();
		std::list<std::shared_ptr<UI_QuestUnit>>::iterator EndIter = MaibBoardPointer->QuestList.end();

		for (; StartIter != EndIter; )
		{
			if ((*StartIter).get() == this)
			{
				StartIter = MaibBoardPointer->QuestList.erase(StartIter);
				return;
			}

			++StartIter;
		}
	}
}

void UI_QuestUnit::Init(std::string_view _Data)
{
	std::shared_ptr<QuestData> FindData = QuestData::Find(_Data);
	if (nullptr == FindData)
	{
		MsgBoxAssert("존재하지 않는 데이터입니다.");
		return;
	}

	Data = FindData;


	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Font);

	const int ContentsNewLineCount = StringFunction::GetNewLineCount(Data.lock()->Contents);

	QuestUnit.SubjectBase = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.SubjectBase->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	QuestUnit.SubjectBase->SetSprite("HUD_Quest_Content_1.png");
	QuestUnit.SubjectBase->GetImageTransform().SetLocalScale(float4(196.0f, SubjectBaseYRenderScale));
	QuestUnit.SubjectBase->SetPivotType(PivotType::Top);

	static constexpr float QuestNameFontSize = 16.0f;

	QuestUnit.Subject = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.Subject->Transform.SetLocalPosition(float4(-90.0f, -6.0f, FontDepth));
	QuestUnit.Subject->SetText(GlobalValue::Font_Sandoll, GetSubjectTextToType(Data.lock()->QuestType), ContentFontSize, float4::WHITE);

	const float ContentBaseYScale = GetRenderYSize(ContentsNewLineCount + 1);
	RenderYScale = QuestUnit.SubjectBase->GetCurSprite().Texture->GetScale().Y + ContentBaseYScale;

	QuestUnit.ContentBase = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.ContentBase->Transform.SetLocalPosition(float4(0.0f, -SubjectBaseYRenderScale, FrameDepth));
	QuestUnit.ContentBase->SetSprite("HUD_Quest_Content_2.png");
	QuestUnit.ContentBase->GetImageTransform().SetLocalScale(float4(196.0f, ContentBaseYScale));
	QuestUnit.ContentBase->SetPivotType(PivotType::Top);

	QuestUnit.QuestName = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.QuestName->Transform.SetLocalPosition(float4(-88.0f, -32.0f, FontDepth));
	QuestUnit.QuestName->SetText(GlobalValue::Font_Sandoll, Data.lock()->QuestName, QuestNameFontSize, float4::ZERO);

	QuestUnit.QuestContent = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.QuestContent->Transform.SetLocalPosition(float4(-72.0f, -56.0f, FontDepth));
	QuestUnit.QuestContent->SetText(GlobalValue::Font_Sandoll, Data.lock()->Contents, ContentFontSize, float4::WHITE);

	QuestUnit.Dot = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.Dot->Transform.SetLocalPosition(float4(-86.0f, -60.0f, FontDepth));
	QuestUnit.Dot->SetText(GlobalValue::Font_Sandoll, std::string("●"), 5.0f, float4::WHITE);
}

void UI_QuestUnit::SetLocalPosition(const float4& _Position)
{
	const float4& MyPosition = Transform.GetLocalPosition();
	Transform.SetLocalPosition(float4(_Position.X + 106.0f, MyPosition.Y));
}

void UI_QuestUnit::AddLocalPosition(const float4& _Position)
{
	Transform.AddLocalPosition(float4(_Position.X));
}

std::string UI_QuestUnit::GetSubjectTextToType(EQUEST _Type)
{
	std::string ReturnValue;

	switch (_Type)
	{
	case EQUEST::Main:
		ReturnValue = "메인";
		break;
	case EQUEST::Side:
		ReturnValue = "사이드";
		break;
	case EQUEST::Repeat:
		ReturnValue = "반복";
		break;
	case EQUEST::None:
		break;
	default:
		break;
	}

	return ReturnValue;
}

float UI_QuestUnit::GetRenderYSize(int _ContentLineCount)
{
	static constexpr float ContentBasicYSize = 40.0f;

	std::weak_ptr<GameEngineTexture> SubjectBaseTexture = GameEngineTexture::Find("HUD_Quest_Content_1.png");
	if (true == SubjectBaseTexture.expired())
	{
		MsgBoxAssert("등록되지 않은 텍스처를 참조하려했습니다.");
		return 0.0f;
	}

	const float BaseYScale = ContentBasicYSize + ContentFontSize * static_cast<float>(_ContentLineCount);
	return BaseYScale;
}