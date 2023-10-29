#pragma once

enum class ECONVERSATIONENTITY
{
	NPC,
	Ellie,
	MagicHat,
	None,
};

class ConversationData
{
public:
	ConversationData(
		std::string_view _FileName,
		std::string_view _Question,
		ECONVERSATIONENTITY _ConversationEntity,
		int _FileIndex = 0)
		:
		FileName(_FileName),
		Question(_Question),
		ConversationEntity(_ConversationEntity),
		FileIndex(_FileIndex)
	{

	}


public:
	std::function<void()> Event;
	std::string FileName;
	std::string Question;
	ECONVERSATIONENTITY ConversationEntity = ECONVERSATIONENTITY::None;
	int FileIndex = 0;

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

	void Init();
	void RendererSetting();

	void CreateConversationData(int _ConversationType, const std::vector<ConversationData>& _Topic);
	const std::vector<ConversationData>& FindData(int _ConversationType);


	template<typename ConversationType>
	void StartConversation(ConversationType _ConversationType)
	{
		StartConversation(static_cast<int>(_ConversationType));
	}

	void StartConversation(int _ConversationType);
	void NextConversation();
	void ConversationEvent();
	void EndConversation();

	void UpdateConversation(float _Delta);

protected:

private:
	std::shared_ptr<class UI_Conversation> m_ConversationUI;
	std::map<int, std::vector<ConversationData>> ConversationDatas;
	std::vector<ConversationData> CurTopic;
	int CurLine = 0;

	bool isConversed = false;

	float ConversationTime = 0.0f;
	static constexpr const float Interaction_Cooldown = 0.3f;

};

