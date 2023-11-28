#pragma once
#include "ContentsEvent.h"


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
	std::string Name;

};


// 설명 :
class ContentsGUI : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;


private:
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

	void QuestCheat();
	void ItemCheat();
	void InventoryCheat();

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
	void CameraPos();
	void ScreenMousePos();
	void WorldMousePos(GameEngineLevel* _CurLevel);
	void SkyColor();
	void SkyOn();
	void TimeDebug();
	void SoundDebug();

public:
	DebugTab(std::string_view _Name)
		: UITab(_Name)
	{

	}


	std::vector<std::string> SpriteNameVector;

private:

	std::string SpriteName;

	bool isSkyOn = true;
	int SliderAmount = 0;
	int iFPS = 0;
	float ColorEdit3Value = 0.2f;
	float RendererHeightItem = 0.0f;
	float TimeCustom = 0.0f;
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

class LightTest : public UITab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

public:
	LightTest(std::string_view _Name)
		: UITab(_Name)
	{

	}

private:
	std::shared_ptr<class FireWorks> FireWork;
	float4 LightColor = float4::ZERO;

};


class ItemTab;
class MapEditorTab : public UITab
{
public:
	static MapEditorTab* MapEditorGui;

public:
	void Start() override;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

public:
	// 생성
	template<typename TabType>
	void CreateItemTab(std::string_view _ItemName)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_ItemName);

		std::shared_ptr<TabType> HTab = std::make_shared<TabType>(UpperName);

		HTab->Parent = this;
		HTab->TabStart();
		AllItemTabs.push_back(HTab);
	}

	void ChangeItemTab(std::string_view _ItemName);

	std::shared_ptr<ItemTab> FindItemTab(std::string_view _ItemName);
	std::string GetCurItemTabName();



	void SaveTab(GameEngineLevel* _Level, float _DeltaTime);
	void SettingTab(GameEngineLevel* _Lesvel, float _DeltaTime);
	void LoadTab(GameEngineLevel* _Level, float _DeltaTime);
	void HelpTab(GameEngineLevel* _Level, float _DeltaTime);



public:
	MapEditorTab(std::string_view _Name)
		: UITab(_Name)
	{

	}

public:
	std::vector<std::shared_ptr<ItemTab>> AllItemTabs;
	std::shared_ptr<ItemTab> CurItemTab = nullptr;

	std::string SavePath;
	std::string LoadPath;

	char PathString[256] = { 0, };
	


	

};


class ItemTab
{
public:
	virtual void TabStart() {}

	virtual void EditoritemTab(GameEngineLevel* _Level, float _DeltaTime) {}
	virtual void SaveItemTab(GameEngineLevel* _Level) {}
	virtual void LoadItemTab(GameEngineLevel* _Level) {}

	ItemTab(std::string_view _ItemName)
	{
		TabName = _ItemName;
	}

public:
	class MapEditorTab* Parent = nullptr;

	std::string ActorType;

	std::string TabName;

};


class BaseRendererItemTab : public ItemTab
{
public:
	void TabStart() override;

	void EditoritemTab(GameEngineLevel* _Level, float _DeltaTime) override;
	void SaveItemTab(GameEngineLevel* _Level) override;
	void LoadItemTab(GameEngineLevel* _Level) override;

	BaseRendererItemTab(std::string_view _TabName)
		: ItemTab(_TabName)
	{

	}

public:
	std::vector<std::string> SpriteNames;
	std::string SelectSpriteName;
	std::map<std::string, int> DepthTypes;

	int SelectSpriteItem = 0;
	int SelectDepthItem = 0;

	float4 RendererCorrection = float4::ZERONULL;

};



class PropItemTab : public ItemTab
{
public:
	void TabStart() override;

	void EditoritemTab(GameEngineLevel* _Level, float _DeltaTime) override;
	void SaveItemTab(GameEngineLevel* _Level) override;
	void LoadItemTab(GameEngineLevel* _Level) override;

	PropItemTab(std::string_view _TabName)
		: ItemTab(_TabName)
	{

	}


public:
	std::map<std::string, int> DepthTypes;
	std::vector<std::string> SpriteNames;
	std::vector<std::string> PixelSpriteNames;
	std::string SelectSpriteName;
	std::string PixelSelectSpriteName;


	int SelectSpriteItem = 0;
	int SelectPixelSpriteItem = 0;
	int SelectDepthItem = 0;
	float Width = 0.0f;


};
