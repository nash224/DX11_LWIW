#pragma once
#include "StaticEntity.h"
#include "HoldingGauge.h"


// Ό³Έν :
class BranchTree : public StaticEntity
{
private:
	enum class EBRANCHFALLORDER
	{
		Third,
		Second,
		First,
		Max,
	};

	enum class EBRANCHTREESTATE
	{
		Idle,
		Shake,
		None,
	};

public:
	// constrcuter destructer
	BranchTree();
	~BranchTree();

	// delete Function
	BranchTree(const BranchTree& _Other) = delete;
	BranchTree(BranchTree&& _Other) noexcept = delete;
	BranchTree& operator=(const BranchTree& _Other) = delete;
	BranchTree& operator=(BranchTree&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void RendererSetting();
	void BranchRendererSetting();
	void StateSetting();

	void ChangeAnimation(std::string_view _SpriteName);

	void StartIdle(GameEngineState* _Parent);
	void UpdateIdle(float _Delta, GameEngineState* _Parent);

	void StartShake(GameEngineState* _Parent);
	void UpdateShake(float _Delta, GameEngineState* _Parent);


	void UpdateBranch(float _Delta);

	void FallBranch();
	void EraseBranch();
	void DropBranchItem();


private:
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> BranchRenderers;
	HoldingGauge Gauge;

	GameEngineState State;

	bool isGauging = false;
	bool IsShaked = false;

	int BranchCount = 3;
	float ShakingTime = 0.0f;
	float PrevFallBranchTime = 0.0f;
	float NextFallBranchTime = 0.0f;
	float DropCoolTime = 0.6f;
	float BranchTotalTime = 0.0f;

	static constexpr float TreeRenderCorrection = 112.0f;

};

