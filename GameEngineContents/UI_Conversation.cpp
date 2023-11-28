#include "PreCompile.h"
#include "UI_Conversation.h"



UI_Conversation* UI_Conversation::MainConversationUI = nullptr;
UI_Conversation::UI_Conversation()
{
	if (nullptr == GameEngineSound::FindSound("SFX_Voice_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\UI\\Conversation");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

UI_Conversation::~UI_Conversation()
{
}


void UI_Conversation::Start()
{
	GameEngineInput::AddInputObject(this);
}

void UI_Conversation::Update(float _Delta)
{
	State.Update(_Delta);
}

void UI_Conversation::Release()
{
	Portrait.Ellie = nullptr;
	Portrait.Other = nullptr;
	Portrait.Virgil = nullptr;

	Dialogue.Left_Tail = nullptr;
	Dialogue.Right_Tail = nullptr;
	Dialogue.Main_Dialogue = nullptr;
	Dialogue.Main_Cursor = nullptr;
	Dialogue.Main_Font = nullptr;

	Dialogue.Virgil_Cursor = nullptr;
	Dialogue.Virgil_Dialogue = nullptr;
	Dialogue.Virgil_Font = nullptr;
}

void UI_Conversation::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainConversationUI = this;
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Conversation::Init()
{
	MainConversationUI = this;

	RendererSetting();
	StateSetting();
}


void UI_Conversation::StateSetting()
{
	CreateStateParameter DoneState;
	DoneState.Start = std::bind(&UI_Conversation::StartDoneState, this, std::placeholders::_1);
	State.CreateState(EUICONERSATIONSTATE::Done, DoneState);

	CreateStateParameter OutputState;
	OutputState.Start = std::bind(&UI_Conversation::StartOutputState, this, std::placeholders::_1);
	OutputState.Stay = std::bind(&UI_Conversation::UpdateOutputState, this, std::placeholders::_1, std::placeholders::_2);
	OutputState.End = std::bind(&UI_Conversation::EndOutputState, this, std::placeholders::_1);
	State.CreateState(EUICONERSATIONSTATE::Output, OutputState);

	CreateStateParameter VirgilOutputState;
	VirgilOutputState.Start = std::bind(&UI_Conversation::StartVirgilOutputState, this, std::placeholders::_1);
	VirgilOutputState.Stay = std::bind(&UI_Conversation::UpdateVirgilOutputtState, this, std::placeholders::_1, std::placeholders::_2);
	VirgilOutputState.End = std::bind(&UI_Conversation::EndVirgilOutputState, this, std::placeholders::_1);
	State.CreateState(EUICONERSATIONSTATE::VirgilOutput, VirgilOutputState);
}

void UI_Conversation::StartDoneState(GameEngineState* _Parent)
{
	Dialogue.OutputCount = 0;

	Dialogue.isOutPutMessage = false;
}

void UI_Conversation::StartOutputState(GameEngineState* _Parent)
{
	if (nullptr == Dialogue.Main_Cursor)
	{
		MsgBoxAssert("생성되지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Dialogue.Main_Font)
	{
		MsgBoxAssert("존재하지 않는 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Dialogue.Main_Cursor->Off();

	Dialogue.Main_Font->SetText(Dialogue.FontName, std::string(), Dialogue.FontSize, Dialogue.FontColor);

	Dialogue.isOutPutMessage = true;
}

void UI_Conversation::StartVirgilOutputState(GameEngineState* _Parent)
{
	if (nullptr == Dialogue.Virgil_Cursor)
	{
		MsgBoxAssert("생성되지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Dialogue.Virgil_Font)
	{
		MsgBoxAssert("존재하지 않는 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Dialogue.Virgil_Cursor->Off();

	Dialogue.Virgil_Font->SetText(Dialogue.FontName, std::string(), Dialogue.FontSize, Dialogue.FontColor);

	Dialogue.isOutPutMessage = true;
}

void UI_Conversation::UpdateOutputState(float _Delta, GameEngineState* _Parent)
{
	bool isSkip = (Dialogue.OutputCount > Dialogue.Skip_Able_Count && true == GameEngineInput::IsDown('Z', this));
	if (isSkip)
	{
		const std::string OutPutMessage = GameEngineString::UnicodeToAnsi(Dialogue.Main_Message);
		Dialogue.Main_Font->SetText(Dialogue.FontName, OutPutMessage, Dialogue.FontSize, Dialogue.FontColor);

		State.ChangeState(EUICONERSATIONSTATE::Done);

		PlayPageSound();

		return;
	}

	StateTime += _Delta;
	if (StateTime > Dialogue.Message_Output_Once_Inter)
	{
		StateTime -= Dialogue.Message_Output_Once_Inter;

		const int MessageSize = static_cast<int>(Dialogue.Main_Message.size() + 1);
		bool isDoneOutput = (Dialogue.OutputCount >= MessageSize);
		if (isDoneOutput)
		{
			State.ChangeState(EUICONERSATIONSTATE::Done);
			return;
		}
		

		while (true)
		{
			if (Dialogue.Main_Message[Dialogue.OutputCount] != L' ')
			{
				break;
			}

			++Dialogue.OutputCount;
		}

		const std::wstring PrintMessage = Dialogue.Main_Message.substr(0, Dialogue.OutputCount);
		const std::string OutPutMessage = GameEngineString::UnicodeToAnsi(PrintMessage);
		Dialogue.Main_Font->SetText(Dialogue.FontName, OutPutMessage, Dialogue.FontSize, Dialogue.FontColor);

		PlayConversationSound("SFX_Voice_01.wav");

		++Dialogue.OutputCount;
	}
}

void UI_Conversation::UpdateVirgilOutputtState(float _Delta, GameEngineState* _Parent)
{
	bool isSkip = (Dialogue.OutputCount > Dialogue.Skip_Able_Count && true == GameEngineInput::IsDown('Z', this));
	if (isSkip)
	{
		const std::string OutPutMessage = GameEngineString::UnicodeToAnsi(Dialogue.Virgil_Message);
		Dialogue.Virgil_Font->SetText(Dialogue.FontName, OutPutMessage, Dialogue.FontSize, Dialogue.FontColor);

		State.ChangeState(EUICONERSATIONSTATE::Done);

		PlayPageSound();

		return;
	}

	StateTime += _Delta;
	if (StateTime > Dialogue.Message_Output_Once_Inter)
	{
		StateTime -= Dialogue.Message_Output_Once_Inter;

		const int MessageSize = static_cast<int>(Dialogue.Virgil_Message.size() + 1);
		bool isDoneOutput = (Dialogue.OutputCount >= MessageSize);
		if (isDoneOutput)
		{
			State.ChangeState(EUICONERSATIONSTATE::Done);
			return;
		}

		while (true)
		{
			if (Dialogue.Virgil_Message[Dialogue.OutputCount] != L' ')
			{
				break;
			}

			++Dialogue.OutputCount;
		}

		const std::wstring PrintMessage = Dialogue.Virgil_Message.substr(0, Dialogue.OutputCount);
		const std::string OutPutMessage = GameEngineString::UnicodeToAnsi(PrintMessage);
		Dialogue.Virgil_Font->SetText(Dialogue.FontName, OutPutMessage, 16.0f, Dialogue.FontColor);

		PlayConversationSound("SFX_Voice_02.wav");

		++Dialogue.OutputCount;
	}
}

void UI_Conversation::PlayPageSound()
{
	GameEngineSoundPlayer PageSound = GameEngineSound::SoundPlay("SFX_InventoryMove_01.wav");
	PageSound.SetVolume(GlobalValue::GetSFXVolume());
}

void UI_Conversation::PlayConversationSound(std::string_view _FileName)
{
	GameEngineSoundPlayer ConversationSound = GameEngineSound::SoundPlay(_FileName);
	ConversationSound.SetVolume(GlobalValue::GetSFXVolume());
}


void UI_Conversation::EndOutputState(GameEngineState* _Parent)
{
	if (nullptr == Dialogue.Main_Cursor)
	{
		MsgBoxAssert("생성되지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Dialogue.Main_Cursor->On();
}

void UI_Conversation::EndVirgilOutputState(GameEngineState* _Parent)
{
	if (nullptr == Dialogue.Virgil_Cursor)
	{
		MsgBoxAssert("생성되지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Dialogue.Virgil_Cursor->On();
}

void UI_Conversation::EndConversation()
{
	Reset();
}

bool UI_Conversation::IsConversation()
{
	return Dialogue.isOutPutMessage;
}


void UI_Conversation::Reset()
{
	Portrait.Ellie->Off();
	Portrait.Other->Off();
	Portrait.Virgil->Off();

	Portrait.Default_Index = 0;
	Portrait.isNoNpc = false;

	const int Virgil_Default_Index = ReturnVirgilIndexToElliePortrait(Portrait.Ellie_Portrait_Default_Index);

	Portrait.Ellie->ChangeCurSprite(Portrait.Ellie_Portrait_Default_Index);
	Portrait.Virgil->ChangeCurSprite(Virgil_Default_Index);

	Dialogue.Left_Tail->Off();
	Dialogue.Right_Tail->Off();
	Dialogue.Main_Dialogue->Off();
	Dialogue.Main_Cursor->Off();
	Dialogue.Main_Font->Off();

	ResetVirgil();

	Dialogue.Main_Message.clear();
	Dialogue.Virgil_Message.clear();
}

void UI_Conversation::ResetVirgil()
{
	Dialogue.Virgil_Dialogue->Off();
	Dialogue.Virgil_Cursor->Off();
	Dialogue.Virgil_Font->Off();
}


void UI_Conversation::StartConversation(std::string_view _NPCSpriteName, int _NPC_Default_Sprite_Index, int _Ellie_First_Sprite_Index /*= 1*/)
{
	if (nullptr == Portrait.Other)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Portrait.Ellie)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Portrait.Virgil)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Dialogue.Main_Dialogue)
	{
		MsgBoxAssert("생성하지 않은 컨포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Other->On();
	Portrait.Ellie->On();
	Portrait.Virgil->On();


	const int Virgil_Default_Index = ReturnVirgilIndexToElliePortrait(_Ellie_First_Sprite_Index);
	Portrait.VirgilIndex = Virgil_Default_Index;

	Portrait.Ellie->ChangeCurSprite(_Ellie_First_Sprite_Index);
	Portrait.Virgil->ChangeCurSprite(Virgil_Default_Index);

	if (true == _NPCSpriteName.empty())
	{
		Portrait.isNoNpc = true;
		Portrait.Other->Off();
	}
	else
	{
		Portrait.Other->SetSprite(_NPCSpriteName);

		bool isDeaultIndexSetting = (-1 != Portrait.Default_Index);
		if (isDeaultIndexSetting)
		{
			Portrait.Default_Index = _NPC_Default_Sprite_Index;
		}
		else
		{
			Portrait.Default_Index = -1;
		}
	}
	

	Dialogue.Main_Dialogue->On();
}

void UI_Conversation::ShowConversation(const ConversationData& _Data)
{
	Dialogue.FontName = _Data.Font.FontName;
	Dialogue.FontColor = _Data.Font.Color;

	bool VirgilNotConverse = (ECONVERSATIONENTITY::Virgil != _Data.ConversationEntity);
	if (true == isJustVirgilTalked && VirgilNotConverse)
	{
		LoseSpeechControlVirgil();
		isJustVirgilTalked = false;
	}

	NPCDefaultIndexSetting();

	switch (_Data.ConversationEntity)
	{
	case ECONVERSATIONENTITY::NPC:
		SetNPCExpression(_Data.FileIndex);
		Dialogue.Main_Message = _Data.Question;
		SetMainMessage();
		OnRightTail();
		State.ChangeState(EUICONERSATIONSTATE::Output);
		break;
	case ECONVERSATIONENTITY::Ellie:
		SetEllieExpression(_Data.FileIndex);
		Dialogue.Main_Message = _Data.Question;
		SetMainMessage();
		OnLeftTail();
		State.ChangeState(EUICONERSATIONSTATE::Output);
		break;
	case ECONVERSATIONENTITY::Virgil:
		SetVirgilExpression(_Data.FileIndex);
		Dialogue.Virgil_Message = _Data.Question;
		SetVirgilMessage();
		State.ChangeState(EUICONERSATIONSTATE::VirgilOutput);
		break;
	default:
		break;
	}

	PlayPageSound();
}


void UI_Conversation::NPCDefaultIndexSetting()
{
	if (true == Portrait.isNoNpc)
	{
		return;
	}

	if (-1 == Portrait.Default_Index)
	{
		return;
	}

	if (nullptr == Portrait.Other)
	{
		MsgBoxAssert("생성되지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Other->ChangeCurSprite(Portrait.Default_Index);
}

void UI_Conversation::SetEllieExpression(unsigned int _SpriteIndex)
{
	SetAllExpressionBlack();
	Portrait.Ellie->GetColorData().MulColor = Portrait.SayingColor;
	Portrait.Virgil->GetColorData().MulColor = Portrait.SayingColor;


	const std::uint32_t Virgil_Sprite_Index = ReturnVirgilIndexToElliePortrait(_SpriteIndex);

	Portrait.Ellie->ChangeCurSprite(_SpriteIndex);
	Portrait.Virgil->ChangeCurSprite(Virgil_Sprite_Index);

	Portrait.VirgilIndex = Virgil_Sprite_Index;
}

void UI_Conversation::SetNPCExpression(unsigned int _SpriteIndex)
{
	if (true == Portrait.isNoNpc)
	{
		return;
	}

	SetAllExpressionBlack();

	Portrait.Other->GetColorData().MulColor = Portrait.SayingColor;
	Portrait.Other->ChangeCurSprite(_SpriteIndex);
}

void UI_Conversation::SetVirgilExpression(unsigned int _SpriteIndex)
{
	SetAllExpressionBlack();

	Portrait.Ellie->GetColorData().MulColor = Portrait.SayingColor;
	Portrait.Virgil->GetColorData().MulColor = Portrait.SayingColor;
	

	if (false == isJustVirgilTalked)
	{
		const int Virgil_Saying_Index = Portrait.VirgilIndex - 1;
		Portrait.Virgil->ChangeCurSprite(Virgil_Saying_Index);
	}

	isJustVirgilTalked = true;
}

void UI_Conversation::SetAllExpressionBlack()
{
	if (nullptr == Portrait.Virgil)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Portrait.Other)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Portrait.Ellie)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Virgil->GetColorData().MulColor = Portrait.UnsaidColor;
	Portrait.Ellie->GetColorData().MulColor = Portrait.UnsaidColor;

	if (false == Portrait.isNoNpc)
	{
		Portrait.Other->GetColorData().MulColor = Portrait.UnsaidColor;
	}
}


void UI_Conversation::SetMainMessage()
{
	if (nullptr == Dialogue.Main_Font)
	{
		MsgBoxAssert("FontRenderer가 없습니다.");
		return;
	}

	float4 MessageLinePosition;

	bool isMessageOverLineStringCount = (Dialogue.Main_Message.size() > Dialogue.Main_Message_Max_Line_String_Count);
	if (isMessageOverLineStringCount)
	{
		MessageLinePosition = Place2thLinePosition(Dialogue.Main_Dialogue_1th_Line_Position);

		const unsigned int InputLineNumber = Dialogue.Main_Message_Max_Line_String_Count;
		Dialogue.Main_Message.insert(InputLineNumber, L"\n");
	}
	else
	{
		MessageLinePosition = Place1thLinePosition(Dialogue.Main_Dialogue_1th_Line_Position);
	}

	Dialogue.Main_Font->Transform.SetLocalPosition(MessageLinePosition);
	Dialogue.Main_Font->On();
}

void UI_Conversation::SetVirgilMessage()
{
	if (nullptr == Dialogue.Virgil_Font)
	{
		MsgBoxAssert("FontRenderer가 없습니다.");
		return;
	}

	Dialogue.Virgil_Dialogue->On();


	float4 MessageLinePosition;

	bool isMessageOverLineStringCount = (Dialogue.Virgil_Message.size() > Dialogue.Virgil_Message_Max_Line_String_Count);
	if (isMessageOverLineStringCount)
	{
		MessageLinePosition = Place2thLinePosition(Dialogue.Virgil_Dialogue_1th_Line_Position);

		const unsigned int InputLineNumber = Dialogue.Virgil_Message_Max_Line_String_Count;
		Dialogue.Virgil_Message.insert(InputLineNumber, L"\n");
	}
	else
	{
		MessageLinePosition = Place1thLinePosition(Dialogue.Virgil_Dialogue_1th_Line_Position);
	}

	Dialogue.Virgil_Font->Transform.SetLocalPosition(MessageLinePosition);
	Dialogue.Virgil_Font->On();
}


float4 UI_Conversation::Place1thLinePosition(const float4& _LinePosition)
{
	float4 Message1thLinePosition = _LinePosition;
	Message1thLinePosition.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Message);
	return Message1thLinePosition;
}

float4 UI_Conversation::Place2thLinePosition(const float4& _LinePosition)
{
	float4 Message2thLinePosition = CalculateNextLinePosition(_LinePosition);
	Message2thLinePosition.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Conversation_Message);
	return Message2thLinePosition;
}

float4 UI_Conversation::CalculateNextLinePosition(const float4& _MessagePosition)
{
	float4 MessagePosition = _MessagePosition;
	MessagePosition.Y += Dialogue.Over_Message_Line_Y_Distance;
	return MessagePosition;
}


const unsigned int UI_Conversation::ReturnVirgilIndexToElliePortrait(unsigned int _Index)
{
	switch (_Index)
	{
	case 0:
	{
		MsgBoxAssert("스프라이트에 앨리가 존재하지 않습니다.");
		return 0;
	}
		break;
	case 1:
	case 5:
	case 10:
		return 2;
	default:
		break;
	}

	return 6;
}


void UI_Conversation::LoseSpeechControlVirgil()
{
	if (nullptr == Portrait.Virgil)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Portrait.Virgil->ChangeCurSprite(Portrait.VirgilIndex);

	ResetVirgil();
}


void UI_Conversation::OnRightTail()
{
	ResetAllTail();

	if (true == Portrait.isNoNpc)
	{
		return;
	}

	Dialogue.Right_Tail->On();
}

void UI_Conversation::OnLeftTail()
{
	ResetAllTail();

	Dialogue.Left_Tail->On();
}

void UI_Conversation::ResetAllTail()
{
	if (nullptr == Dialogue.Left_Tail)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	if (nullptr == Dialogue.Right_Tail)
	{
		MsgBoxAssert("생성하지 않은 컴포넌트를 사용하려 했습니다.");
		return;
	}

	Dialogue.Left_Tail->Off();
	Dialogue.Right_Tail->Off();
}