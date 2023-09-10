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


public:
	void Init();

private:
	void CreateScenery(class GameEngineLevel* _CurLevel);
	void CreateProp(class GameEngineLevel* _CurLevel);
	void CreateTrain(class GameEngineLevel* _CurLevel);
	void CreateChainProp(class GameEngineLevel* _CurLevel);

public:
	void ActorRelease();

private:
	std::shared_ptr<MainMenu_Trains> m_MainMenu_Train;
	std::vector<std::shared_ptr<ChainProp>> vecMainMenu_Chain;

private:

	// Prop




	



	// ChainProp
	const float CONST_MountainSpeed = -60.0f;
	const float CONST_BridgeSpeed = -480.0f;
	const float CONST_TreeSpeed = -1200.0f;

	const float COSNT_TreeSpawnDistance = 2400.0f;


};

