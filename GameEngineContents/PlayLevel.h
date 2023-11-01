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
	class PlaySoundInfo
	{
	public:
		GameEngineSoundPlayer BGM;
		GameEngineSoundPlayer BGM_SFX;
		std::string BGMName;

		static float BGMVolume;

	public:
		void PlayBGM(std::string_view _BGMName, std::string_view _BGM_SFXName = "");
		void ResourceLoad();
		void Stop();
		void SetVolume(float _Value);

		static constexpr const float Max_BGM_Volume = 2.0f;
		static constexpr const float Min_BGM_Volume = 0.0f;

	};

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

	PlaySoundInfo MainPlaySound;

	bool LevelInitCheck = false;

};