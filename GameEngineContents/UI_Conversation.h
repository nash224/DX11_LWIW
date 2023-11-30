#pragma once
#include "Conversation.h"


// Ό³Έν :
class UI_Conversation : public GameEngineActor
{
public:
	static UI_Conversation* MainConversationUI;

public:
	class PortraitStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Ellie;
		std::shared_ptr<GameEngineUIRenderer> Virgil;
		std::shared_ptr<GameEngineUIRenderer> Other;

		int DefaultIndex = 0;
		int VirgilIndex = 0;

	};

	class DialogueStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Left_Tail;
		std::shared_ptr<GameEngineUIRenderer> Right_Tail;
		std::shared_ptr<GameEngineUIRenderer> Main_Dialogue;
		std::shared_ptr<GameEngineUIRenderer> Main_Cursor;
		std::shared_ptr<GameEngineUIRenderer> Main_Font;
		std::wstring Main_Message;

		std::shared_ptr<GameEngineUIRenderer> Virgil_Dialogue;
		std::shared_ptr<GameEngineUIRenderer> Virgil_Cursor;
		std::shared_ptr<GameEngineUIRenderer> Virgil_Font;
		std::wstring Virgil_Message;

	};

	enum class EUICONERSATIONSTATE
	{
		Output,
		VirgilOutput,
		Done,
		None,
	};


public:
	// constrcuter destructer
	UI_Conversation();
	~UI_Conversation();

	// delete Function
	UI_Conversation(const UI_Conversation& _Other) = delete;
	UI_Conversation(UI_Conversation&& _Other) noexcept = delete;
	UI_Conversation& operator=(const UI_Conversation& _Other) = delete;
	UI_Conversation& operator=(UI_Conversation&& _Other) noexcept = delete;

	void Init();

	void StartConversation(std::string_view _NPCSpriteName, int _NPC_Default_Sprite_Index = -1, int _Ellie_First_Sprite_Index = 1);
	void ShowConversation(const ConversationData& _Data);
	void EndConversation();

	bool IsConversation() const;


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void RendererSetting();
	void ResourceSetting();
	void PortraitSetting();
	void DialogueSetting();

	void StateSetting();

	void StartDoneState(GameEngineState* _Parent);
	void StartOutputState(GameEngineState* _Parent);
	void StartVirgilOutputState(GameEngineState* _Parent);

	void UpdateOutputState(float _Delta, GameEngineState* _Parent);
	void UpdateVirgilOutputtState(float _Delta, GameEngineState* _Parent);

	void EndOutputState(GameEngineState* _Parent);
	void EndVirgilOutputState(GameEngineState* _Parent);

	void Reset();
	void ResetVirgil();

	void NPCDefaultIndexSetting();

	void SetNPCExpression(unsigned int _SpriteIndex);
	void SetEllieExpression(unsigned int _SpriteIndex);
	void SetVirgilExpression(unsigned int _SpriteIndex);
	void SetAllExpressionBlack();

	void SetMainMessage();
	void SetVirgilMessage();


	float4 Place2thLinePosition(const float4& _LinePosition);
	float4 Place1thLinePosition(const float4& _LinePosition);
	float4 CalculateNextLinePosition(const float4& _MessagePosition);

	const unsigned int ReturnVirgilIndexToElliePortrait(unsigned int _Index);

	void NotVirgilSay();

	void OnRightTail();
	void OnLeftTail();
	void ResetAllTail();

	void PlayPageSound();

private:
	PortraitStruct Portrait;
	DialogueStruct Dialogue;

	GameEngineState State;
	float StateTime = 0.0f;

	int OutputCount = 0;
	const float OutPutSize = 18.0f;

	bool isJustVirgilTalked = false;
	bool isOutPutMessage = false;
	bool isNoneNpc = false;

	std::string OutPutFontStyle;

	const float4 MainDialogue_FirstLinePosition = float4(-164.0f, -174.0f);
	const float4 SayingColor = float4::ONE;
	float4 OutputFontColor;

	static constexpr unsigned int MainMessage_MaxCharCount = 24;
	static constexpr unsigned int VirgilMessage_MaxCharCount = 17;
	static constexpr int EnableSkip_CharCount = 1;
	static constexpr float MessageOutputInter = 0.11f;

};