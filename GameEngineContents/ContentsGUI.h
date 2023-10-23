#pragma once



class UITab
{
public:
	virtual void OnGUI(GameEngineLevel* _Level, float _Delta) = 0;

	UITab(std::string_view _Name)
	{
		Name = _Name;
	}


public:
	std::string Name = "";
	int Index = 0;

};


// Ό³Έν :
class ContentsGUI : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;


	std::shared_ptr<UITab> CurTab = nullptr;
	std::vector<std::shared_ptr<UITab>> AllTabs;

};


class LevelChangeTab : public UITab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

public:
	LevelChangeTab(std::string_view _Name)
		: UITab(_Name)
	{
	}
};




class CheatTab : public UITab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


public:
	CheatTab(std::string_view _Name)
		: UITab(_Name)
	{

	}
};


class DebugTab : public UITab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


public:
	DebugTab(std::string_view _Name)
		: UITab(_Name)
	{

	}
};


class ManualTab : public UITab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


public:
	ManualTab(std::string_view _Name)
		: UITab(_Name)
	{

	}
};


class MapEditorTab : public UITab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

public:
	void OnFPSTime(float _DeltaTime);
	void MousePos();
	void MapEditorMode();


public:
	MapEditorTab(std::string_view _Name)
		: UITab(_Name)
	{

	}

	std::vector<std::string> SpriteNameVector;

private:
	bool IsCheckBox = false;

	std::string SpriteName = "";

	int SliderAmount = 0;
	float ColorEdit3Value = 0.2f;
	int iFPS = 0;


};

