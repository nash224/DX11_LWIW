#pragma once

// 설명 :
class UI_ToggleActor : public GameEngineActor
{
	friend class UIManager;

public:
	// constrcuter destructer
	UI_ToggleActor();
	~UI_ToggleActor();

	// delete Function
	UI_ToggleActor(const UI_ToggleActor& _Other) = delete;
	UI_ToggleActor(UI_ToggleActor&& _Other) noexcept = delete;
	UI_ToggleActor& operator=(const UI_ToggleActor& _Other) = delete;
	UI_ToggleActor& operator=(UI_ToggleActor&& _Other) noexcept = delete;

	void Open();
	void Close();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	// Open 또는 Close 함수를 호출할 때 자식에서 끄고 싶은 기능을 추가해줍니다.
	virtual void OpenChild() {}
	virtual void CloseChild() {}

protected:
	bool IsHub = false;
	bool IsOpen = false;
	bool OpenCheck = false;

};

