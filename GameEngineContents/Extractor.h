#pragma once
#include "StaticEntity.h"

enum class EJUICERSTATE
{
	None,
	Broken,
	Idle,
	Juicy,
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

	void CreateRendererAndAnimation();


private:
	void UpdateState(float _Delta);
	void ChangeState(EJUICERSTATE _State);
	void ChangeExtractorCompositionAnimation(std::string_view _StateName);


	void StartBroken();
	void UpdateBroken(float _Delta);

	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartJuicy();
	void UpdateJuicy(float _Delta);

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Extractor;

private:
	EJUICERSTATE m_State = EJUICERSTATE::None;


};

