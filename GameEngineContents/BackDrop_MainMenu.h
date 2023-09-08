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
	void CreateProp(class GameEngineLevel* _CurLevel);

public:
	void ReleaseCurrentLevelChildActor();

private:


	//const float4 MainMenuMagicFront2CenterPosition = float4{ 1147.0f , -202.0f };
};

