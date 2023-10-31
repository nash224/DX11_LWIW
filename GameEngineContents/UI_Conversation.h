#pragma once


#define ELLIE_PORTRAIT { -400.0f , -250.0f }

class ConversationParameter
{
public:
	ConversationParameter(
		ECONVERSATIONENTITY _Entity, 
		int _FileIndex, 
		std::wstring_view _Message, 
		std::string_view _FontName)
		:
		FileIndex(_FileIndex),
		Entity(_Entity),
		Message(_Message),
		FontName(_FontName)
	{

	}

public:
	int FileIndex = 0;
	ECONVERSATIONENTITY Entity;
	std::wstring_view Message;
	std::string_view FontName;

};



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

	public:
		unsigned int VirgilIndex = 0;
		static constexpr const int Ellie_Portrait_Default_Index = 1;
		static constexpr const float Portrait_Default_X_Gap = 360.0f;

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
		std::string Main_Message_Output;

		std::shared_ptr<GameEngineUIRenderer> Virgil_Dialogue;
		std::shared_ptr<GameEngineUIRenderer> Virgil_Cursor;
		std::shared_ptr<GameEngineUIRenderer> Virgil_Font;
		std::wstring Virgil_Message;
		std::string Virgil_Message_Output;

	public:
		static constexpr const float Virgil_Dialogue_Animation_Inter = 0.24f;
		
		static constexpr const float FontSize = 17.0f;

		const float4 DefaultColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
		const float4 RedColor = float4(0.8f, 0.0f, 0.0f, 1.0f);

		const float4 Virgil_Dialogue_Position = float4(-360.0f, 70.0f);


		static constexpr const unsigned int Main_Message_Max_Line_String_Count = 12;

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

	void StartConversation(std::string_view _NPCSpriteName);
	void ShowConversation(const ConversationParameter& _Para);
	void EndConversation();


protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void RendererSetting();
	void ResourceSetting();
	void PortraitSetting();
	void DialogueSetting();

	void Reset();
	void ResetVirgil();


	void SetNPCExpression(unsigned int _SpriteIndex);
	void SetEllieExpression(unsigned int _SpriteIndex);
	void SetVirgilExpression(unsigned int _SpriteIndex);
	void SetAllExpressionBlack();

	void SetMainMessage(std::string_view _FontName);
	void SetVirgilMessage(std::string_view _FontName);

	std::string ConvertWstirngToString(std::wstring_view _wMessage);

	const unsigned int ReturnVirgilIndexToEllie(unsigned int _Index);

	void LoseSpeechControlVirgil();

	void SetRightTail();
	void SetLeftTail();
	void ResetAllTail();

	


private:
	PortraitInfo Portrait;
	DialogueInfo Dialogue;

	GameEngineState State;

	bool isJustVirgilTalked = false;

};

