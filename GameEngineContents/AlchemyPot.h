#pragma once
#include "StaticEntity.h"

enum class EPOTSTATE
{
	None,
	Idle,
	Boil,
	Fail,
	Success
};



// Ό³Έν :
class AlchemyPot : public StaticEntity
{
private:
	std::shared_ptr<class UI_Dispensation> m_Dispensation = nullptr;

public:
	// constrcuter destructer
	AlchemyPot();
	~AlchemyPot();

	// delete Function
	AlchemyPot(const AlchemyPot& _Other) = delete;
	AlchemyPot(AlchemyPot&& _Other) noexcept = delete;
	AlchemyPot& operator=(const AlchemyPot& _Other) = delete;
	AlchemyPot& operator=(AlchemyPot&& _Other) noexcept = delete;

	void Init();

	void RendererSetting();
	void DispensationSetting();

	void DispensatePotion(std::string_view _CraftedPotionName);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateState(float _Delta);
	void ChangeState(EPOTSTATE _State);
	void ChangePotCompositionAnimation(std::string_view _StateName);

	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartBoil();
	void UpdateBoil(float _Delta);

	void StartFail();
	void UpdateFail(float _Delta);

	void StartSuccess();
	void UpdateSuccess(float _Delta);
	void EndSuccess();

	void EndPotionCreation();


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_PotRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_WaterRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_FxRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_FireRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_SteamRenderer;

	std::string CraftedPotion = "";

	EPOTSTATE m_State = EPOTSTATE::None;

};

