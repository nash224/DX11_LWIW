#pragma once
#include "ContentsLevel.h"
#include <GameEngineCore/GameEngineGUI.h>


class ContentsGUIWindow : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


private:
	void MapEditorMode();

private:
	std::vector<std::string> SpriteNameVector;

private:
	bool IsCheckBox = false;

	std::string SpriteName = "";

	int SliderAmount = 0;
	float ColorEdit3Value = 0.2f;
	int iFPS = 0;

};


// ���� :
class Ellie;
class PortalObject;
class UIManager;
class PlayLevel : public ContentsLevel
{
public:
	static bool PixelDebugMode;


public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;



private:
	void CreateUIManager();
	void CreateEllie();


private:
	void ChangeDebugMode();


protected:
	std::shared_ptr<Ellie> m_Ellie = nullptr;
	std::shared_ptr<UIManager> m_UIManager = nullptr;

protected:
	bool LevelInitCheck = false;

};