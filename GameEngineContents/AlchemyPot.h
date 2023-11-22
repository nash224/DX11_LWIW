#pragma once
#include "StaticEntity.h"

enum class EPOTSTATE
{
	None,
	Broken,
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

	static AlchemyPot* s_PotPointer;

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
	void StateSetting();
	void DispensationSetting();

	void DispensatePotion(std::string_view _CraftedPotionName);

	static void RepairPot();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void ChangePotAnimation(std::string_view _StateName);

	void StartBroken(GameEngineState* _Parent);
	void StartIdle(GameEngineState* _Parent);
	void StartBoil(GameEngineState* _Parent);
	void StartFail(GameEngineState* _Parent);
	void StartSuccess(GameEngineState* _Parent);

	void UpdateBroken(float _Delta, GameEngineState* _Parent);
	void UpdateIdle(float _Delta, GameEngineState* _Parent);
	void UpdateBoil(float _Delta, GameEngineState* _Parent);
	void UpdateFail(float _Delta, GameEngineState* _Parent);
	void UpdateSuccess(float _Delta, GameEngineState* _Parent);

	void EndBroken(GameEngineState* _Parent);
	void EndSuccess(GameEngineState* _Parent);


	void EndPotionCreation();

	void CheckCraftPotionEvent();
	void CheckCraftFireCrackerEvent();
	void ShowCraftPotionEvent();
	void ShowFireCrackerEvent();
	


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_PotRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_WaterRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_FxRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_FireRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_SteamRenderer;

	GameEngineState State;

	std::string CraftedPotion;

	EPOTSTATE m_State = EPOTSTATE::None;

};

