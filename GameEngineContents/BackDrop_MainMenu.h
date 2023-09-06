#pragma once
#include "BackDrop.h"



// Ό³Έν :
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
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:

private:
	void CreateBackDrop();
	void CreateScenery(class GameEngineLevel* _CurLevel);
	void CreateProps(class GameEngineLevel* _CurLevel);

public:
	void ReleaseCurrentLevelChildActor();

private:

	const float4 Layer1LeftTopPosition = float4{ 24.0f , 0.0f };
	const float4 Layer3LeftTopPosition = float4{ 990.0f , -201.0f };
	const float4 Layer5LeftTopPosition = float4{ 320.0f , -291.0f };
	const float4 Layer6LeftTopPosition = float4{ 768.0f , -229.0f };
	const float4 Layer8LeftTopPosition = float4{ 0.0f , -269.0f };
	const float4 Layer10LeftTopPosition = float4{ 24.0f , 0.0f };


	const float4 MainMenuHairLeftTopPosition = float4{ 1216.0f, -170.0f };
	const float4 MainMenuHairSize = float4{ 63.0f , 33.0f };
	//const float4 MainMenuHairLeftTopPosition = float4::ZERO;
};

