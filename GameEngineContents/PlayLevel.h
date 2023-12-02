#pragma once
#include "ContentsLevel.h"


// Ό³Έν :
class PlayLevel : public ContentsLevel
{
public:
	static PlayLevel* s_MainPlayLevel;
	static std::unique_ptr<class TimeManager> s_TimeManager;
	static std::unique_ptr<class AlertManager> s_AlertManager; 
	std::shared_ptr<class Ellie> Player = nullptr;
	std::shared_ptr<class UIManager> UIManagerPtr = nullptr;
	std::shared_ptr<class BackDrop_PlayLevel> Back = nullptr;

public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	std::string_view GetPrevLevelName() const
	{
		return PrevLevelName;
	}

	static PlayLevel* GetPlayLevelPtr();
	std::shared_ptr<class UIManager> GetUIManagerPtr() const;
	std::shared_ptr<class Ellie> GetPlayerPtr() const;
	std::shared_ptr<class BackDrop_PlayLevel> GetBackDropPtr() const;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

protected:
	std::string LocationKRName;
	std::string PrevLevelName;

};