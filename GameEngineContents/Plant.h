#pragma once
#include "StaticEntity.h"

enum class EPLANTSTATE
{
	Idle,
	UpRoot,
	None,
};


// ���� :
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
	// �Ѹ��� ������ ��� �Ҳ��� 
	// �ڽĿ��� �������մϴ�.
	virtual void ChildUpRoot() {}


protected:
	std::shared_ptr<GameEngineSpriteRenderer> m_Plant = nullptr;

protected:
	EPLANTSTATE m_State = EPLANTSTATE::None;


};

