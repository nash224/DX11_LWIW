#pragma once

#define PROCESS_FIRST_SLOT_POSITION { -4.0f, 134.0f }
#define PROCESS_SLOT_GAP 64.0f

class ProcessListCursor
{
public:
	std::shared_ptr<GameEngineUIRenderer> UpArrow = nullptr;
	std::shared_ptr<GameEngineUIRenderer> DownArrow = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ScrollBase = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ScrollBar = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;


};


// Ό³Έν :
class UI_ProcessList : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_ProcessList();
	~UI_ProcessList();

	// delete Function
	UI_ProcessList(const UI_ProcessList& _Other) = delete;
	UI_ProcessList(UI_ProcessList&& _Other) noexcept = delete;
	UI_ProcessList& operator=(const UI_ProcessList& _Other) = delete;
	UI_ProcessList& operator=(UI_ProcessList&& _Other) noexcept = delete;

	void Init();
	void RendererSetting();
	void CreateProcessSlot(std::string_view _ProcessName);
	void CursorSetting();


	void Open();
	void Close();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void UpdateInput();
	void MoveCursor(int _Value);

private:
	std::vector<std::shared_ptr<class UI_ProcessListUnit>> SlotVec;

	std::shared_ptr<GameEngineUIRenderer> m_Base = nullptr;
	ProcessListCursor m_ProcessListCursor;
	int CurrentCursor = 0;

};
