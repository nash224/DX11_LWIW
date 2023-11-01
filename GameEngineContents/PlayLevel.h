#pragma once
#include "ContentsLevel.h"
#include <GameEngineCore/GameEngineGUI.h>




// Ό³Έν :
class Ellie;
class PortalObject;
class UIManager;
class PlayLevel : public ContentsLevel
{
public:
	static std::shared_ptr<class TimeManager> s_TimeManager;

public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;



private:
	void CreateUIManager();
	void CreateEllie();


protected:
	std::shared_ptr<Ellie> m_Ellie = nullptr;
	std::shared_ptr<UIManager> m_UIManager = nullptr;

	bool LevelInitCheck = false;

};