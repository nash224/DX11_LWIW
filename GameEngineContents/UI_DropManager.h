#pragma once

// Ό³Έν :
class UI_DropManager : public GameEngineActor
{
public:
	static UI_DropManager* DropManager;

public:
	// constrcuter destructer
	UI_DropManager();
	~UI_DropManager();

	// delete Function
	UI_DropManager(const UI_DropManager& _Other) = delete;
	UI_DropManager(UI_DropManager&& _Other) noexcept = delete;
	UI_DropManager& operator=(const UI_DropManager& _Other) = delete;
	UI_DropManager& operator=(UI_DropManager&& _Other) noexcept = delete;

	void Init();

	void NoticeItemDrop(std::string_view _ItemName);
	std::list<std::shared_ptr<class UI_Drop>>& GetSystemNoticeList();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::list<std::shared_ptr<class UI_Drop>> UI_SystemNoticeList;

public:
	int DropUICount = 0;

};

