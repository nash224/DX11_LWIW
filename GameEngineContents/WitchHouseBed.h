#pragma once
#include "InteractiveActor.h"

// ���� :
class WitchHouseBed : public InteractiveActor
{
private:
	enum class EBEDSTATE
	{
		NotActive,
		Active,
	};

public:
	// constrcuter destructer
	WitchHouseBed();
	~WitchHouseBed();

	// delete Function
	WitchHouseBed(const WitchHouseBed& _Other) = delete;
	WitchHouseBed(WitchHouseBed&& _Other) noexcept = delete;
	WitchHouseBed& operator=(const WitchHouseBed& _Other) = delete;
	WitchHouseBed& operator=(WitchHouseBed&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void StateSetting();
	void UISetting();

	void StartNotActive(GameEngineState* _Parent);
	void StartActive(GameEngineState* _Parent);

	void UpdateNotActive(float _Delta, GameEngineState* _Parent);
	void UpdateActive(float _Delta, GameEngineState* _Parent);

private:
	GameEngineState State;
	std::weak_ptr<class BedUI> BedUIActor;

	static constexpr unsigned int Bed_Active_Hour = 9;


};

