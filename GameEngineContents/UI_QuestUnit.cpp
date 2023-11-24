#include "PreCompile.h"
#include "UI_QuestUnit.h"

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
}

static constexpr float ContentFontSize = 12.0f;

void UI_QuestUnit::Init(std::string_view _Data)
{
	std::shared_ptr<QuestData> FindData = QuestData::Find(_Data);
	if (nullptr == FindData)
	{
		MsgBoxAssert("�������� �ʴ� �������Դϴ�.");
		return;
	}

	Data = FindData;


	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Font);

	const int ContentsNewLineCount = StringFunction::GetNewLineCount(Data.lock()->Contents);
	RenderYScale = GetRenderYSize(ContentsNewLineCount + 1);

	QuestUnit.SubjectBase = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.SubjectBase->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	QuestUnit.SubjectBase->SetSprite("HUD_Quest_Content_1.png");
	QuestUnit.SubjectBase->GetImageTransform().SetLocalScale(float4(196.0f, 18.0f));
	QuestUnit.SubjectBase->SetPivotType(PivotType::Bottom);

	static constexpr float QuestNameFontSize = 15.0f;

	QuestUnit.Subject = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.Subject->Transform.SetLocalPosition(float4(0.0f, -9.0f, FontDepth));
	QuestUnit.Subject->SetText(GlobalValue::Font_Sandoll, GetSubjectTextToType(Data.lock()->QuestType), ContentFontSize, float4::WHITE);

	QuestUnit.ContentBase = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.ContentBase->Transform.SetLocalPosition(float4(0.0f, -18.0f, FrameDepth));
	QuestUnit.ContentBase->SetSprite("HUD_Quest_Content_2.png");
	QuestUnit.ContentBase->GetImageTransform().SetLocalScale(float4(196.0f, RenderYScale));
	QuestUnit.ContentBase->SetPivotType(PivotType::Bottom);

	QuestUnit.QuestName = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.QuestName->Transform.SetLocalPosition(float4(0.0f, -32.0f, FontDepth));
	QuestUnit.QuestName->SetText(GlobalValue::Font_Sandoll, Data.lock()->QuestName, QuestNameFontSize, float4::ZERO);

	QuestUnit.QuestContent = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.QuestContent->Transform.SetLocalPosition(float4(0.0f, -52.0f, FontDepth));
	QuestUnit.QuestContent->SetText(GlobalValue::Font_Sandoll, Data.lock()->Contents, ContentFontSize, float4::WHITE);

	QuestUnit.Dot = CreateComponent<GameEngineUIRenderer>();
	QuestUnit.Dot->Transform.SetLocalPosition(float4(0.0f, -52.0f, FontDepth));
	QuestUnit.Dot->SetText(GlobalValue::Font_Sandoll, std::string("��"), ContentFontSize, float4::WHITE);
}

std::string UI_QuestUnit::GetSubjectTextToType(EQUEST _Type)
{
	std::string ReturnValue;

	switch (_Type)
	{
	case EQUEST::Main:
		ReturnValue = "����";
		break;
	case EQUEST::Side:
		ReturnValue = "���̵�";
		break;
	case EQUEST::Repeat:
		ReturnValue = "�ݺ�";
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
	static constexpr float ContentBasicYSize = 100.0f;

	std::weak_ptr<GameEngineTexture> SubjectBaseTexture = GameEngineTexture::Find("HUD_Quest_Content_1.png");
	if (true == SubjectBaseTexture.expired())
	{
		MsgBoxAssert("��ϵ��� ���� �ؽ�ó�� �����Ϸ��߽��ϴ�.");
		return 0.0f;
	}

	const float4& SubjectBaseTextureScale = SubjectBaseTexture.lock()->GetScale();
	const float BaseYScale = SubjectBaseTextureScale.Y + ContentBasicYSize + ContentFontSize * static_cast<float>(_ContentLineCount);
	return BaseYScale;
}