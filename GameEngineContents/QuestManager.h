#pragma once

class QuestInfo
{

};

// Ό³Έν :
class QuestManager : public GameEngineActor
{
public:
	// constrcuter destructer
	QuestManager();
	~QuestManager();

	// delete Function
	QuestManager(const QuestManager& _Other) = delete;
	QuestManager(QuestManager&& _Other) noexcept = delete;
	QuestManager& operator=(const QuestManager& _Other) = delete;
	QuestManager& operator=(QuestManager&& _Other) noexcept = delete;

	void RegisterQuest(std::string_view _QuestName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void PopData(std::string_view _QuestName);

private:
	std::list<std::string> QuestContainer;

};

