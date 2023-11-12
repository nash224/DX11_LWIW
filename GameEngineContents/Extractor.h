#pragma once
#include "StaticEntity.h"

enum class EJUICERSTATE
{
	Broken,
	Idle,
	Juicy,
	None,
};



// Ό³Έν :
class Extractor : public StaticEntity
{
public:
	// constrcuter destructer
	Extractor();
	~Extractor();

	// delete Function
	Extractor(const Extractor& _Other) = delete;
	Extractor(Extractor&& _Other) noexcept = delete;
	Extractor& operator=(const Extractor& _Other) = delete;
	Extractor& operator=(Extractor&& _Other) noexcept = delete;

	void PullThis();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void InitExtractor();

	void RendererSetting();
	void UIProcessSetting();
	void StateSetting();


private:
	void ChangeExtractorAnimation(std::string_view _StateName);

	void StartBroken(GameEngineState* _Parent);
	void UpdateBroken(float _Delta ,GameEngineState* _Parent);

	void StartIdle(GameEngineState* _Parent);
	void UpdateIdle(float _Delta, GameEngineState* _Parent);

	void StartJuicy(GameEngineState* _Parent);
	void UpdateJuicy(float _Delta, GameEngineState* _Parent);
	void EndJuicy(GameEngineState* _Parent);

	std::string RandomOpenJuicySoundFilleName();

private:
	GameEngineState State;

	std::shared_ptr<GameEngineSpriteRenderer> m_Extractor;
	std::shared_ptr<class UI_ProcessManager> m_ProcessManager;

};

