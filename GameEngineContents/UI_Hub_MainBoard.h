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

private:
	std::list<std::string> QuestContainer;
	std::list<std::string> ClearContainer;

	bool IsQuestRegister(std::string_view _QuestName);

};

struct MainBoardStruct
{
	friend class UI_Hub_MainBoard;

private:
	std::shared_ptr<GameEngineUIRenderer> Base;
	std::shared_ptr<GameEngineUIRenderer> Toggle;
	std::shared_ptr<GameEngineUIRenderer> TabButton;
	std::shared_ptr<GameEngineUIRenderer> Alert;

};

// Ό³Έν :
class UI_Hub_MainBoard : public UI_Hub_Actor
{
	friend class UI_QuestUnit;
	friend class QuestManager;

private:
	static bool isShowAlertMark;

private:
	enum class EMAINBOARDSTATE
	{
		Open,
		Stay,
		Close,
		None,
	};

public:
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
	void RegisterQuest(std::string_view _QuestName);
	void PopQuest(std::string_view _QuestName);

	void Open();
	void OpenFrom(int _StartSlot);
	void Close();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void InitQuestManager();
	void CreateQuestUnit(std::string_view _QuestName);

	void RemoveAllQuestList();
	void RenewUnitList();
	bool IsSameList();

	////
	// State
	void StateSetting();

	// Start
	void StartNone(GameEngineState* _Parent);
	void StartOpen(GameEngineState* _Parent);
	void StartStay(GameEngineState* _Parent);
	void StartClose(GameEngineState* _Parent);

	// Update
	void UpdateOpen(float _Delta, GameEngineState* _Parent);
	void UpdateStay(float _Delta, GameEngineState* _Parent);
	void UpdateClose(float _Delta, GameEngineState* _Parent);

	// End
	void EndOpen(GameEngineState* _Parent);

	void AddPosAllQuestUnit(const float4& _Pos);
	void SetPosAllQuestUnit(const float4& _Pos);

private:
	std::list<std::shared_ptr<class UI_QuestUnit>> QuestList;

	GameEngineState State;
	MainBoardStruct MainBoard;
	const float MoveSpeed = 800.0f;

};