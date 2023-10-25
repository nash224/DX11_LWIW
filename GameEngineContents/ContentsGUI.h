#pragma once



class UITab
{
public:
	virtual void Start() {}
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
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


public:
	int SelectItem = 0;

	std::map<int, std::list<std::string>> ItemContainer;
	

public:
	CheatTab(std::string_view _Name)
		: UITab(_Name)
	{

	}
};


class DebugTab : public UITab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	void OnFPSTime(float _DeltaTime);
	void MousePos();

public:
	DebugTab(std::string_view _Name)
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
	void Start() override;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

public:
	void SaveTab(GameEngineLevel* _Level, float _DeltaTime);
	void SettingTab(GameEngineLevel* _Level, float _DeltaTime);
	void EditorTab(GameEngineLevel* _Level, float _DeltaTime);
	void LoadTab(GameEngineLevel* _Level, float _DeltaTime);


public:
	MapEditorTab(std::string_view _Name)
		: UITab(_Name)
	{

	}

public:
	std::string DefSavePath;
	std::string SavePath;
	std::string LoadPath;
	std::string InputPath;

	std::vector<std::string> SpriteNames;
	std::vector<std::string> DepthTypes;


	char BackGroundName[256] = { 0, };
	bool BaseRendererCheckBox = false;
	int SelectItem;
	

};

