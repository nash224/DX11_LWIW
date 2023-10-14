#pragma once
#include "StaticEntity.h"

enum class EPLANTSTATE
{
	Idle,
	UpRoot,
	None,
};


// 설명 :
class Plant : public StaticEntity
{
public:
	// constrcuter destructer
	Plant();
	~Plant();

	// delete Function
	Plant(const Plant& _Other) = delete;
	Plant(Plant&& _Other) noexcept = delete;
	Plant& operator=(const Plant& _Other) = delete;
	Plant& operator=(Plant&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	void ChangeState(EPLANTSTATE _State);

private:
	void UpdateState(float _Delta);
	void ChangePlantAnimation(std::string_view _Name);

	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartUpRoot();
	void UpdateUpRoot(float _Delta);
	// 뿌리를 뽑을때 어떻게 할꺼냐 
	// 자식에서 재정의합니다.
	virtual void ChildUpRoot() {}


protected:
	std::shared_ptr<GameEngineSpriteRenderer> m_Plant = nullptr;

protected:
	EPLANTSTATE m_State = EPLANTSTATE::None;


};

