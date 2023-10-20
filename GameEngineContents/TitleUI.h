#pragma once

// Ό³Έν :
class TitleUI : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleUI();
	~TitleUI();

	// delete Function
	TitleUI(const TitleUI& _Other) = delete;
	TitleUI(TitleUI&& _Other) noexcept = delete;
	TitleUI& operator=(const TitleUI& _Other) = delete;
	TitleUI& operator=(TitleUI&& _Other) noexcept = delete;

	void Init();
	void ButtonSetting(GameEngineLevel* _Level);
	void StateSetting(GameEngineLevel* _Level);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateUI();
	

private:
	GameEngineState m_State;
	


};

