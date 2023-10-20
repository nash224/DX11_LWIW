#pragma once
#include "Props.h"


// 설명 : Props 기능을 물려받는 일반 소품입니다.
class NormalProp : public Props
{
public:
	// constrcuter destructer
	NormalProp();
	~NormalProp();

	// delete Function
	NormalProp(const NormalProp& _Other) = delete;
	NormalProp(NormalProp&& _Other) noexcept = delete;
	NormalProp& operator=(const NormalProp& _Other) = delete;
	NormalProp& operator=(NormalProp&& _Other) noexcept = delete;

	template<typename OrderType>
	void Init(OrderType _Order)
	{
		Init(static_cast<int>(_Order));
	}


	void Init(int _Order = 0);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

};

