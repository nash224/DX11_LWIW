#pragma once


#define ELLIE_PORTRAIT { -400.0f , -250.0f }

class ConversationParameter
{
public:
	ConversationParameter(ECONVERSATIONENTITY _Entity, int _FileIndex, std::string_view _Message, std::string_view _FontName)
		:
		Entity(_Entity),
		FileIndex(_FileIndex),
		Message(_Message),
		FontName(_FontName)
	{

	}

public:
	ECONVERSATIONENTITY Entity;
	int FileIndex = 0;
	std::string_view Message;
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

	};

	class DialogueInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Left_Tail;
		std::shared_ptr<GameEngineUIRenderer> Right_Tail;
		std::shared_ptr<GameEngineUIRenderer> Main_Dialogue;
		std::shared_ptr<GameEngineUIRenderer> Main_Cursor;
		std::shared_ptr<GameEngineSpriteRenderer> Main_Font;
		std::string Main_Message;

		std::shared_ptr<GameEngineUIRenderer> Virgil_Dialogue;
		std::shared_ptr<GameEngineUIRenderer> Virgil_Cursor;
		std::shared_ptr<GameEngineUIRenderer> Virgil_Font;
		std::string Virgil_Message;

		static constexpr const float FontSize = 17.0f;
		float4 DefaultColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
		float4 RedColor = float4(0.8f, 0.0f, 0.0f, 1.0f);

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


	void SetNPCExpression(unsigned int _SpriteIndex);
	void SetEllieExpression(unsigned int _SpriteIndex);
	void SetVirgilExpression(unsigned int _SpriteIndex);

	void SetMainMessage(std::string_view _FontName);
	void SetVirgilMessage(std::string_view _FontName);

	const unsigned int ReturnVirgilIndexToEllie(unsigned int _Index);

	
	


private:
	PortraitInfo Portrait;
	DialogueInfo Dialogue;

	GameEngineState State;

	bool isJustVirgilTalked = false;

};

