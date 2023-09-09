#pragma once
#include "BackDrop.h"



// Ό³Έν :
class MainMenu_Trains;
class ChainProp;
class BackDrop_MainMenu : public BackDrop
{
public:
	// constrcuter destructer
	BackDrop_MainMenu();
	~BackDrop_MainMenu();

	// delete Function
	BackDrop_MainMenu(const BackDrop_MainMenu& _Other) = delete;
	BackDrop_MainMenu(BackDrop_MainMenu&& _Other) noexcept = delete;
	BackDrop_MainMenu& operator=(const BackDrop_MainMenu& _Other) = delete;
	BackDrop_MainMenu& operator=(BackDrop_MainMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:

private:
	void CreateBackDrop();
	void CreateScenery(class GameEngineLevel* _CurLevel);
	void CreateProp(class GameEngineLevel* _CurLevel);

public:
	void ActorRelease();

private:
	std::shared_ptr<MainMenu_Trains> m_MainMenu_Train;
	std::vector<std::shared_ptr<ChainProp>> vecMainMenu_Chain;

private:


	const float4 CONST_TwinkleStarPosition = float4{ 20.0f , -100.0f };
	const float4 CONST_WaterPosition = float4{ 0.0f , -398.0f };
	const float4 CONST_MountainblurPosition = float4{ 0.0f , -382.0f };
	const float4 CONST_BridgeDownPosition = float4{ 0.0f , -470.0f };
	const float4 CONST_BridgeblurPosition = float4{ 0.0f , -464.0f };
	const float4 CONST_TranblurPosition = float4{ 26.0f , -492.0f };
	const float4 CONST_TranLightblurPosition = float4{ 220.0f , -508.0f };
	const float4 CONST_LastTranLightblurPosition = float4{ 0.0f , -508.0f };
	const float4 CONST_WaterblurPosition = float4{ 0.0f , -426.0f };

	const float4 CONST_WaterShinePosition = float4{ 0.0f , -484.0f };
	const float4 CONST_MountainPosition = float4{ 0.0f , -164.0f };
	const float4 CONST_MoonPosition = float4{ 176.0f , -50.0f };

	const float4 CONST_Cloud0_Position = float4{ 176.0f , -50.0f };
	const float4 CONST_Cloud1_Position = float4{ 176.0f , -50.0f };

	const float4 CONST_BridgePosition = float4{ 0.0f , -386.0f };

};

