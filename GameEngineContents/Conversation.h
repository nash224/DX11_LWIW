#pragma once


class ConversationData
{
public:
	ConversationData(
		std::wstring_view _Question,
		ECONVERSATIONENTITY _ConversationEntity,
		int _FileIndex = 0,
		float4 _Color = float4(0.0f, 0.0f, 0.0f, 1.0f),
		std::string_view _Font = Font_Sandoll
		)
		:
		Question(_Question),
		ConversationEntity(_ConversationEntity),
		FileIndex(_FileIndex),
		Color(_Color),
		Font(_Font)
	{

	}


public:
	ECONVERSATIONENTITY ConversationEntity = ECONVERSATIONENTITY::None;
	int FileIndex = 0;
	std::wstring Question;
	std::string Font;
	float4 Color;
	std::function<void()> Event;

public:
	static constexpr const char* Font_Sandoll = "Sandoll 삼립호빵체 TTF Basic";

};


class Topic
{
public:
	std::vector<ConversationData> Data;
	std::function<void()> EndEvent;
	std::string EntitySpriteName;
	
	int Default_Npc_Sprite_Index = -1;

public:
	static constexpr const char* Aurea_Expression_Sprite_Name = "Aurea_Expression.png";
	static constexpr const char* Crow_Expression_Sprite_Name = "Crow_Expression.png";
	static constexpr const char* Dian_Expression_Sprite_Name = "Dian_Expression.png";

	// ConversationData에서 사용하는 변수입니다. 
	const float4 Color_RED = float4(0.6f, 0.1f, 0.1f, 1.0f);
	const float4 Color_BLACK = float4(0.0f, 0.0f, 0.0f, 1.0f);

	// 양심의 가책을 느끼고 있습니다.. 어디에 둬야할지 모르곘습니다..
	static constexpr const char* Font_JejuHanlasan = "제주한라산";

};




// 설명 :
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