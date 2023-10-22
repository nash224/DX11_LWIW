#pragma once



class ProcessListCursor
{
public:
	std::shared_ptr<GameEngineUIRenderer> m_UpArrow = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_DownArrow = nullptr;

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

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	std::vector<std::shared_ptr<class UI_ProcessListUnit>> SlotVec;

	std::shared_ptr<GameEngineUIRenderer> m_Base = nullptr;
	ProcessListCursor m_ProcessListCursor;


};
