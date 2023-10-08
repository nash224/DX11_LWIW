#pragma once
#include "DynamicEntity.h"


enum class EMONGSIRISTATE
{
	Idle,
	Jump,
	Look,
	Escape,
	None,
};

// 설명 :
class MongSiri : public DynamicEntity
{
	friend class MongSiri_Population;

private:
	class MongSiri_Population* MongSiriParant = nullptr;

public:
	// constrcuter destructer
	MongSiri();
	~MongSiri();

	// delete Function
	MongSiri(const MongSiri& _Other) = delete;
	MongSiri(MongSiri&& _Other) noexcept = delete;
	MongSiri& operator=(const MongSiri& _Other) = delete;
	MongSiri& operator=(MongSiri&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateAndSetRenderer();

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;

private:
	// 상태
	EMONGSIRISTATE m_State = EMONGSIRISTATE::None;

	void UpdateState(float _Delta);
	void ChangeState(EMONGSIRISTATE _State);

	void StartIdle();
	void UpdateIdle();

	void StartJump();
	void UpdateJump();

	void StartLook();
	void UpdateLook();

	void StartEscape();
	void UpdateEscape();
};

