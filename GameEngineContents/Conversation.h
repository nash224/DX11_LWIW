#pragma once

class ConversationFont
{
public:
	ConversationFont(
		float4 _Color = float4(0.0f, 0.0f, 0.0f, 1.0f),
		std::string_view _FontName = GlobalValue::Font_Sandoll
	)
		:
		Color(_Color),
		FontName(_FontName)
	{

	}

public:
	std::string FontName;
	float4 Color;

	static const float4 Color_RED;
	static const float4 Color_BLACK;
	static const ConversationFont VigilDefaultFont;

};

class ConversationData
{
public:
	ConversationData(
		std::wstring_view _Question,
		ECONVERSATIONENTITY _ConversationEntity,
		int _FileIndex = 0,
		const ConversationFont& _Font = {}
	)
		:
		Question(_Question),
		ConversationEntity(_ConversationEntity),
		FileIndex(_FileIndex),
		Font(_Font)
	{

	}


public:
	ECONVERSATIONENTITY ConversationEntity = ECONVERSATIONENTITY::None;
	int FileIndex = 0;
	std::wstring Question;
	ConversationFont Font;
	std::function<void()> Event;

};


class Topic
{
public:
	std::vector<ConversationData> Data;
	std::function<void()> EndEvent;
	std::string EntitySpriteName;

	int Default_Npc_Sprite_Index = -1;
	int Elli_First_Sprite_Index = 1;

public:
	static constexpr const char* Expression_Aurea_Sprite_Name = "Aurea_Expression.png";
	static constexpr const char* Expression_Crow_Sprite_Name = "Crow_Expression.png";
	static constexpr const char* Expression_Dian_Sprite_Name = "Dian_Expression.png";

};




// Ό³Έν :
class Conversation
{
public:
	// constrcuter destructer
	Conversation();
	~Conversation() {}

	// delete Function
	Conversation(const Conversation& _Other) = delete;
	Conversation(Conversation&& _Other) noexcept = delete;
	Conversation& operator=(const Conversation& _Other) = delete;
	Conversation& operator=(Conversation&& _Other) noexcept = delete;

	template<typename TopicType>
	void CreateTopic(TopicType _ConversationType, const Topic& _Topic)
	{
		CreateTopic(static_cast<int>(_ConversationType), _Topic);
	}

	void CreateTopic(int _ConversationType, const Topic& _Topic);


	const std::shared_ptr<Topic> FindTopic(int _ConversationType);

	template<typename EnumType>
	void SetConversationEvent(EnumType _Topic, int _index, std::function<void()> _Function)
	{
		SetConversationEvent(static_cast<int>(_Topic), _index, _Function);
	}

	void SetConversationEvent(int _Topic, int _index, std::function<void()> _Function);

	template<typename EnumType>
	void SetConversationEndEvent(EnumType _Topic, std::function<void()> _Function)
	{
		SetConversationEndEvent(static_cast<int>(_Topic), _Function);
	}

	void SetConversationEndEvent(int _Topic, std::function<void()> _Function);


	template<typename ConversationType>
	void StartConversation(ConversationType _ConversationType)
	{
		StartConversation(static_cast<int>(_ConversationType));
	}

	void StartConversation(int _ConversationType);

	void UpdateConversation(float _Delta);


protected:
	void ConverseLine();
	void ConversationBTWEvent();
	void NextConversationLine();
	void EndConversationEvent();
	void EndConversation();

private:
	std::map<int, std::shared_ptr<Topic>> Topics;
	std::shared_ptr<Topic> CurTopic;

	int CurLine = 0;

};