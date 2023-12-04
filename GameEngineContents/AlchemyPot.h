#pragma once
#include "InteractiveActor.h"



// Ό³Έν :
class AlchemyPot : public InteractiveActor
{
private:
	enum class EPOTSTATE
	{
		None,
		Broken,
		Idle,
		Boil,
		Fail,
		Success
	};

private:
	std::shared_ptr<class UI_Dispensation> DispensationPage = nullptr;

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
	std::shared_ptr<GameEngineSpriteRenderer> PotRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> WaterRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> FxRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> FireRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> SteamRenderer;

	GameEngineState State;

	std::string CraftedPotion;

};

