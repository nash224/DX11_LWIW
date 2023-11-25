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


	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateProp(class GameEngineLevel* _CurLevel);
	void CreateTrain(class GameEngineLevel* _CurLevel);
	void CreateChainProp(class GameEngineLevel* _CurLevel);

private:

	const float CONST_TreeSpeed = -1200.0f;

	


};

