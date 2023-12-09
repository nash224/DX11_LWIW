#pragma once

// Ό³Έν :
class InteractiveActor;
class UI_InterativeMark : public GameEngineActor
{
	friend class UIManager;
public:
	static UI_InterativeMark* UI_Mark;
	static InteractiveActor* Pointer;

public:
	// constrcuter destructer
	UI_InterativeMark();
	~UI_InterativeMark();

	// delete Function
	UI_InterativeMark(const UI_InterativeMark& _Other) = delete;
	UI_InterativeMark(UI_InterativeMark&& _Other) noexcept = delete;
	UI_InterativeMark& operator=(const UI_InterativeMark& _Other) = delete;
	UI_InterativeMark& operator=(UI_InterativeMark&& _Other) noexcept = delete;

	void Init();

	static void PointThis(InteractiveActor* _ActorPtr);

	void Reset();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void CurLevelPointer();
	void UpdateMark(float _Delta);

private:
	std::shared_ptr<GameEngineUIRenderer> MarkRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ButtonRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> FontRenderer = nullptr;

	bool IsPointerInteracted = false;
	bool IsLevelChange = false;

};

