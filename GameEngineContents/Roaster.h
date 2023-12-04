#pragma once
#include "InteractiveActor.h"


enum class EROASTERSTATE
{
	None,
	Broken,
	Idle,
	Roasting,
};


// Ό³Έν :
class Roaster : public InteractiveActor
{
public:
	// constrcuter destructer
	Roaster();
	~Roaster();

	// delete Function
	Roaster(const Roaster& _Other) = delete;
	Roaster(Roaster&& _Other) noexcept = delete;
	Roaster& operator=(const Roaster& _Other) = delete;
	Roaster& operator=(Roaster&& _Other) noexcept = delete;


	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void RendererSetting();

	void UpdateState(float _Delta);
	void ChangeState(EROASTERSTATE _State);
	void ChangeRoasterCompositionAnimation(std::string_view _StateName);

	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartRoasting();
	void UpdateRoasting(float _Delta);

private:
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_Roaster;
	std::shared_ptr<GameEngineSpriteRenderer> m_RoasterFXSteam;

private:
	EROASTERSTATE m_State = EROASTERSTATE::None;

};

