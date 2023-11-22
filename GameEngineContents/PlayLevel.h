#pragma once
#include "ContentsLevel.h"
#include <GameEngineCore/GameEngineGUI.h>


// Ό³Έν :
class Ellie;
class PortalObject;
class UIManager;
class PlayLevel : public ContentsLevel
{
protected:
	enum class ELEVELTYPE
	{
		Field,
		House,
		None,
	};

public:
	static std::unique_ptr<class TimeManager> s_TimeManager;
	static std::unique_ptr<class AlertManager> s_AlertManager;

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
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void SetLocationName(std::string_view _KRName);

private:
	void EffectSetting();

	void CreateUIManager();
	void CreateEllie();

protected:
	std::shared_ptr<Ellie> Player = nullptr;
	std::shared_ptr<UIManager> UI_Manager = nullptr;

	bool LevelInitCheck = false;

	ELEVELTYPE LevelType = ELEVELTYPE::None;

private:
	std::string LocationKRName;

};