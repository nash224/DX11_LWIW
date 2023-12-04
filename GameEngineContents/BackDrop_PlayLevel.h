#pragma once
#include "BackDrop.h"


// Ό³Έν :
class BackDrop_PlayLevel : public BackDrop
{
	friend class Ellie;

public:
	// constrcuter destructer
	BackDrop_PlayLevel();
	~BackDrop_PlayLevel();

	// delete Function
	BackDrop_PlayLevel(const BackDrop_PlayLevel& _Other) = delete;
	BackDrop_PlayLevel(BackDrop_PlayLevel&& _Other) noexcept = delete;
	BackDrop_PlayLevel& operator=(const BackDrop_PlayLevel& _Other) = delete;
	BackDrop_PlayLevel& operator=(BackDrop_PlayLevel&& _Other) noexcept = delete;

	void CreateItem(std::string_view _ItemName, const float4& _Position = float4::ZERO, const int _Stack = 1, const float _FallYPosition = 0.0f);

	GameEngineColor GetColor(const float4& _Position, GameEngineColor _Color = GameEngineColor::WHITE);

protected:
	void Start() override;
	void Update(float _Delta) override{}
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void CreateRenderActor(int _UpdateOrder, std::string_view _SpriteName, const float4& _Position
		, int _DepthType, bool _isFixDepth = true, float _DepthCorrection = 0.0f);

protected:
	std::shared_ptr<class PixelManager> PixelManagerPtr;

};

