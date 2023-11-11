#pragma once

enum class EFRAMETYPE
{
	Mail,
	BroomStick,
	None,
};

// Ό³Έν :
class UI_Frame : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Frame();
	~UI_Frame();

	// delete Function
	UI_Frame(const UI_Frame& _Other) = delete;
	UI_Frame(UI_Frame&& _Other) noexcept = delete;
	UI_Frame& operator=(const UI_Frame& _Other) = delete;
	UI_Frame& operator=(UI_Frame&& _Other) noexcept = delete;

	template<typename EnumType>
	void Init(EnumType _Type)
	{
		Init(static_cast<int>(_Type));
	}

	void Init(int _Type);

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting(int _Type);
	std::string GetCutsceneName(EFRAMETYPE _Type);

private:
	std::shared_ptr<GameEngineUIRenderer> Frame;
	std::shared_ptr<GameEngineUIRenderer> Cutscene;


};

