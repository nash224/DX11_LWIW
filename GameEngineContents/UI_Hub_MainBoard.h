#pragma once
#include "UI_Hub_Actor.h"
#include "QuestData.h"

class QuestManager
{
	friend class UI_Hub_MainBoard;

public:
	QuestManager();
	~QuestManager();

	// delete Function
	QuestManager(const QuestManager& _Other) = delete;
	QuestManager(QuestManager&& _Other) noexcept = delete;
	QuestManager& operator=(const QuestManager& _Other) = delete;
	QuestManager& operator=(QuestManager&& _Other) noexcept = delete;

	void RegisterData(std::string_view _QuestName);
	void PopData(std::string_view _QuestName);
	bool IsQuestRegister(std::string_view _QuestName);

private:
	std::list<std::string> QuestContainer;
	std::list<std::string> ClearContainer;

};



// Ό³Έν :
class UI_Hub_MainBoard : public UI_Hub_Actor
{
private:
	static std::unique_ptr<QuestManager> s_QuestManager;

public:
	// constrcuter destructer
	UI_Hub_MainBoard();
	~UI_Hub_MainBoard();

	// delete Function
	UI_Hub_MainBoard(const UI_Hub_MainBoard& _Other) = delete;
	UI_Hub_MainBoard(UI_Hub_MainBoard&& _Other) noexcept = delete;
	UI_Hub_MainBoard& operator=(const UI_Hub_MainBoard& _Other) = delete;
	UI_Hub_MainBoard& operator=(UI_Hub_MainBoard&& _Other) noexcept = delete;
	
	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void InitQuestManager();
	void RegisterQuest(std::string_view _QuestName);
	void CreateQuestUnit(std::string_view _QuestName);
	void PopQuest(std::string_view _QuestName);

	void RemoveAllQuestList();
	void RenewUnitList();
	bool IsSameList();

private:
	std::shared_ptr<GameEngineSpriteRenderer> Base;

	std::list<std::shared_ptr<class UI_QuestUnit>> QuestList;

};