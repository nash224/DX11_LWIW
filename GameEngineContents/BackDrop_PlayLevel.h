#pragma once
#include "BackDrop.h"


// 설명 :
class BackDrop_PlayLevel : public BackDrop
{
	friend class Ellie;

public:
	static BackDrop_PlayLevel* MainBackDrop;

public:
	// constrcuter destructer
	BackDrop_PlayLevel();
	~BackDrop_PlayLevel();

	// delete Function
	BackDrop_PlayLevel(const BackDrop_PlayLevel& _Other) = delete;
	BackDrop_PlayLevel(BackDrop_PlayLevel&& _Other) noexcept = delete;
	BackDrop_PlayLevel& operator=(const BackDrop_PlayLevel& _Other) = delete;
	BackDrop_PlayLevel& operator=(BackDrop_PlayLevel&& _Other) noexcept = delete;



	bool IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor);

	float ZSort(const float _PositionY) const;
	float ReturnPlusDepth(const float _PositionY) const;

	// 아이템
	void CreateItem(std::string_view _ItemName, const float4& _Position = float4::ZERO, const int _Stack = 1, const float _FallYPosition = 0.0f);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	std::vector<std::shared_ptr<class NormalProp>> PixelVec;
	std::vector<std::shared_ptr<class StaticEntity>> PixelStaticEntityVec;

};

