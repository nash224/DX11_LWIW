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
class Juicer : public StaticEntity
{
public:
	// constrcuter destructer
	Juicer();
	~Juicer();

	// delete Function
	Juicer(const Juicer& _Other) = delete;
	Juicer(Juicer&& _Other) noexcept = delete;
	Juicer& operator=(const Juicer& _Other) = delete;
	Juicer& operator=(Juicer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void InitJuicer();

	void CreateRendererAndAnimation();
	void CreateInteractiveCollision();


private:
	void UpdateState(float _Delta);
	void ChangeState(EJUICERSTATE _State);
	void ChangeJuicerCompositionAnimation(std::string_view _StateName);


	void StartBroken();
	void UpdateBroken(float _Delta);

	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartJuicy();
	void UpdateJuicy(float _Delta);

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Juicer;

private:
	EJUICERSTATE m_State = EJUICERSTATE::None;


};

