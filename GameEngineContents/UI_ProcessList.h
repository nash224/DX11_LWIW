#pragma once
#include "UI_ButtonGuide.h"


// 설명 :
class UI_ProcessList : public GameEngineActor
{
public:
	class UI_ProcessManager* ProcessManagerPtr = nullptr;

private:
	class ProcessListCursor
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> UpArrow = nullptr;
		std::shared_ptr<GameEngineUIRenderer> DownArrow = nullptr;
		std::shared_ptr<GameEngineUIRenderer> ScrollBase = nullptr;
		std::shared_ptr<GameEngineUIRenderer> ScrollBar = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;

		float ScrollBarYSize = 0.0f;
		float ScrollBarTotalYSize = 0.0f;

	};

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
	void CloseAllSlot();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void UpdateInput();
	void MoveCursor(int _Value);
	void ResetCursor();
	void RenewSlot();
	void RenewCursor();
	void SetScrollBarMovePosition(float _YPos);

private:
	std::vector<std::shared_ptr<class UI_ProcessListUnit>> SlotVec;
	std::shared_ptr<GameEngineUIRenderer> BaseRenderer = nullptr;
	ProcessListCursor CursorInfo;

	UI_ButtonGuide UIGuide;

	int CurrentCursor = 0;
	int CurCursorLine = 0;
	int StartLine = 0;

};
