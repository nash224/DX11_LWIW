#pragma once


// Ό³Έν :
class UI_MainMenu_Button : public GameEngineActor
{
private:
	enum class MainMenuState
	{
		AnyPress,
		Title,
		None,
	};

private:
	class PressAnyButton
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Button_Font;

	};



public:
	// constrcuter destructer
	UI_MainMenu_Button();
	~UI_MainMenu_Button();

	// delete Function
	UI_MainMenu_Button(const UI_MainMenu_Button& _Other) = delete;
	UI_MainMenu_Button(UI_MainMenu_Button&& _Other) noexcept = delete;
	UI_MainMenu_Button& operator=(const UI_MainMenu_Button& _Other) = delete;
	UI_MainMenu_Button& operator=(UI_MainMenu_Button&& _Other) noexcept = delete;

	void Init();

protected:
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();
	void StateSetting();

	void StartAnyPress(GameEngineState* _Parent);
	void StartNone(GameEngineState* _Parent);

	void UpdateAnyPress(float _Delta, GameEngineState* _Parent);

	void EndAnyPress(GameEngineState* _Parent);



private:
	GameEngineState UIState;
	PressAnyButton TitleButton_Press;

	

};

