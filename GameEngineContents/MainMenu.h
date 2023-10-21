#pragma once
#include "ContentsLevel.h"



// Ό³Έν :
class BackDrop_MainMenu;
class MainMenu : public ContentsLevel
{
public :
	std::shared_ptr<BackDrop_MainMenu> m_BackDrop;

public:
	// constrcuter destructer
	MainMenu();
	~MainMenu();

	// delete Function
	MainMenu(const MainMenu& _Other) = delete;
	MainMenu(MainMenu&& _Other) noexcept = delete;
	MainMenu& operator=(const MainMenu& _Other) = delete;
	MainMenu& operator=(MainMenu&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


private:
	void LoadTexture();
	void LoadSprite();
	void LoadContentsData();
	void InitActor();


	void ReleaseSprite();
	void ReleaseTexture();

private:
	

};

