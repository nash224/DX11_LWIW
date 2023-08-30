#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class TitleTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleTestLevel();
	~TitleTestLevel();

	// delete Function
	TitleTestLevel(const TitleTestLevel& _Other) = delete;
	TitleTestLevel(TitleTestLevel&& _Other) noexcept = delete;
	TitleTestLevel& operator=(const TitleTestLevel& _Other) = delete;
	TitleTestLevel& operator=(TitleTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

