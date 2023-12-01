#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class EndingLevel : public ContentsLevel
{
private:
	class EndingBackDrop
	{
	public:
		void RendererSetting(GameEngineLevel* _Level);
		void RendererRelease();

	public:
		std::shared_ptr<GameEngineActor> BackBase;
		std::shared_ptr<GameEngineActor> Font;
		std::shared_ptr<GameEngineActor> Logo;

		std::shared_ptr<GameEngineActor> EndButton;
		std::shared_ptr<GameEngineActor> EndText;
	};

public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void UpdateExit();

private:
	EndingBackDrop BackDrop;


};

