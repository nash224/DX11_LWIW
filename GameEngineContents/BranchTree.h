#pragma once
#include "StaticEntity.h"



constexpr float FallingPositionBranchMinRange = 5.0f;
constexpr float FallingPositionBranchMaxRange = 25.0f;


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


// Ό³Έν :
class BranchTree : public StaticEntity
{
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
	void CreateBranchTreehAnimation();
	void SetBranchInter();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateState(float _Delta);
	void ChangeState(EBRANCHTREESTATE _State);
	void ChangeBranchTreeAnimation(std::string_view _SpriteName);
	void CreateBranchRenderer();

	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartShake();
	void UpdateShake(float _Delta);


	void UpdateBranch(float _Delta);
	void FallBranch();
	void EraseBranch();
	void CreateBranchItem();


private:
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> BranchVector;
	std::shared_ptr<GameEngineSpriteRenderer> m_Tree = nullptr;

	EBRANCHTREESTATE m_State = EBRANCHTREESTATE::None;

	bool IsShaked = false;
	int m_BranchCount = 3;
	float m_BranchStateTime = 0.0f;
	float BranchFallInter = 0.8f;
	float BranchTotalInter = 0.0f;
	const float TreeRenderCorrection = 112.0f;

};

