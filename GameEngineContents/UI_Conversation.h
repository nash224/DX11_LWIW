#pragma once
#include "Conversation.h"

#define ELLIE_PORTRAIT { -400.0f , -250.0f }


// Ό³Έν :
class UI_Conversation : public GameEngineActor
{
public:
	static UI_Conversation* MainConversationUI;


public:

	class PortraitInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Ellie;
		std::shared_ptr<GameEngineUIRenderer> Virgil;
		std::shared_ptr<GameEngineUIRenderer> Other;

		int Default_Index = 0;
		unsigned int VirgilIndex = 0;

		bool isNoNpc = false;

	public:
		static constexpr const int Ellie_Portrait_Default_Index = 1;
		static constexpr const float Portrait_Default_X_Gap = 340.0f;

		const float4 UnsaidColor = float4(0.3f, 0.3f, 0.3f, 1.0f);
		const float4 SayingColor = float4::ONE;

	};

	class DialogueInfo
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

		std::string FontName;
		float4 FontColor;
		int OutputCount = 0;
		bool isOutPutMessage = false;

	public:
		static constexpr const float Virgil_Dialogue_Animation_Inter = 0.2f;
		
		static constexpr const float FontSize = 18.0f;

		const float4 Main_Dialogue_1th_Line_Position = float4(-164.0f, -174.0f);
		const float4 Virgil_Dialogue_1th_Line_Position = float4(-440.0f, 90.0f);


		const float4 Virgil_Dialogue_Position = float4(-340.0f, 70.0f);


		static constexpr const unsigned int Main_Message_Max_Line_String_Count = 24;
		static constexpr const unsigned int Virgil_Message_Max_Line_String_Count = 15;
		static constexpr const float Over_Message_Line_Y_Distance = 6.0f;


		static constexpr const float Message_Output_Once_Inter = 0.11f;

		static constexpr const int Skip_Able_Count = 1;


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

	void StartConversation(std::string_view _NPCSpriteName, int _Default_Sprite_Index = -1);
	void ShowConversation(const ConversationData& _Data);
	void EndConversation();

	bool IsConversation();


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
	void PlayPageSound();
	void PlayConversationSound(std::string_view _FileName);

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

	void LoseSpeechControlVirgil();

	void OnRightTail();
	void OnLeftTail();
	void ResetAllTail();

	


private:
	PortraitInfo Portrait;
	DialogueInfo Dialogue;

	GameEngineState State;
	float StateTime = 0.0f;

	bool isJustVirgilTalked = false;

};

