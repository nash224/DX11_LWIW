#pragma once

enum class ECONVERSATIONENTITY
{
	NPC,
	Ellie,
	Virgil,
	None,
};


class ConversationData
{
public:
	ConversationData(
		std::string_view _Question,
		ECONVERSATIONENTITY _ConversationEntity,
		int _FileIndex = 0)
		:
		Question(_Question),
		ConversationEntity(_ConversationEntity),
		FileIndex(_FileIndex)
	{

	}


public:
	std::function<void()> Event;
	std::string Question;
	ECONVERSATIONENTITY ConversationEntity = ECONVERSATIONENTITY::None;
	int FileIndex = 0;

public:
	static constexpr const char* Font_LiberationSans = "Liberation Sans";
	static constexpr const char* Font_Sandoll = "Sandoll »ï¸³È£»§Ã¼ TTF Basic";
	static constexpr const char* Font_PerfectDOS = "Perfect DOS VGA 437";

};


class Topic
{
public:
	std::vector<ConversationData> Data;
	std::function<void()> EndEvent;
	std::string EntitySpriteName;

public:
	static constexpr const char* Aurea_Expression_Sprite_Name = "Aurea_Expression.png";
	static constexpr const char* Crow_Expression_Sprite_Name = "Crow_Expression.png";
	static constexpr const char* Dian_Expression_Sprite_Name = "Dian_Expression.png";

};




// ¼³¸í :
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

	bool isConversed = false;

	int CurLine = 0;

	float ConversationTime = 0.0f;
	static constexpr const float Interaction_Cooldown = 0.3f;

};

