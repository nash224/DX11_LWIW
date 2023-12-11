#include "PreCompile.h"
#include "ContentsGUI.h"

#include <GameEngineCore/GameEngineCamera.h>

#include "MapEditorLevel.h"
#include "PlayLevel.h"

#include "CameraControler.h"
#include "BackDrop_PlayLevel.h"
#include "TimeManager.h"
#include "UI_Inventory.h"


#include "GroundRenderUnit.h"
#include "NormalPropEditor.h"
#include "SkyLerp.h"
#include "FireWorks.h"

#include "ItemData.h"
#include "BGMManager.h"
#include "PixelManager.h"

void ContentsGUI::Start()
{
	AllTabs.push_back(std::make_shared<LevelChangeTab>("LevelChange"));
	CurTab = AllTabs[0];
	AllTabs.push_back(std::make_shared<CheatTab>("CheatTab"));
	AllTabs.push_back(std::make_shared<MapEditorTab>("MapEditor"));
	AllTabs.push_back(std::make_shared<DebugTab>("Debug"));
	AllTabs.push_back(std::make_shared<ManualTab>("Manual"));
	AllTabs.push_back(std::make_shared<LightTest>("LightTest"));

	for (int i = 0; i < AllTabs.size(); i++)
	{
		AllTabs[i]->Start();
	}
}



void ContentsGUI::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	for (std::shared_ptr<UITab> Tab : AllTabs)
	{
		ImGui::SameLine();

		if (nullptr != CurTab)
		{
			if (ImGui::Button(Tab->Name.c_str()))
			{
				CurTab = Tab;

				if ("MapEditor" == Tab->Name)
				{
					GameEngineCore::ChangeLevel("MapEditorLevel");
				}
			}
		}
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _Delta);
	}
}



void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	const std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevelRef = GameEngineCore::GetAllLevel();
	for (const auto&[LevelName,Level] : AllLevelRef)
	{
		if (ImGui::Button(LevelName.c_str()))
		{
			GameEngineCore::ChangeLevel(LevelName);
		}
	}
}


void CheatTab::Start()
{
	{
		std::map<std::string, std::shared_ptr<ItemData>>& AllItemData = ItemData::GetAllData();

		std::map<std::string, std::shared_ptr<ItemData>>::iterator StartIter = AllItemData.begin();
		std::map<std::string, std::shared_ptr<ItemData>>::iterator EndIter = AllItemData.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			std::shared_ptr<ItemData> ItemData = (*StartIter).second;

			ItemContainer[static_cast<int>(ItemData->ItemType)].push_back(ItemData->Name);
		}
	}
}

void CheatTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (_Level->GetName() == "MainMenu")
	{
		return;
	}

	if (ImGui::BeginTabBar("Cheat"))
	{
		QuestCheat();
		ItemCheat();
		InventoryCheat();
	}
	ImGui::EndTabBar();
}

void CheatTab::QuestCheat()
{
	if (ImGui::BeginTabItem("Quest"))
	{
		for (const std::pair<std::string, std::weak_ptr<ContentsEvent::QuestUnitBase>>& pair : ContentsEvent::QuestData)
		{
			if (true == pair.second.expired())
			{
				continue;
			}

			ImGui::Checkbox(pair.first.c_str(), &pair.second.lock()->isQuestCompleted);
		}

		ImGui::EndTabItem();
	}
}

void CheatTab::ItemCheat()
{
	static std::vector<const char*> CNames;
	char Number = 0;
	for (const auto& [index, NameGroup] : ItemContainer)
	{
		CNames.clear();

		const std::string ItemTabName = "ItemType" + std::to_string(Number);
		const std::string ListName = "ItemList" + std::to_string(Number);
		if (ImGui::BeginTabItem(ItemTabName.c_str()))
		{
			for (const std::string& Name : NameGroup)
			{
				CNames.push_back(Name.c_str());
			}

			if (ImGui::ListBox(ListName.c_str(), &SelectItem, CNames.data(), static_cast<int>(CNames.size())))
			{
				UI_Inventory::PushItem(CNames[SelectItem]);
			}
			ImGui::EndTabItem();
		}

		++Number;
	}
}

void CheatTab::InventoryCheat()
{
	if (ImGui::BeginTabItem("Inventory"))
	{
		if (ImGui::Button("Unlock Slot"))
		{
			UI_Inventory::UnlockSlot();
		}

		ImGui::EndTabItem();
	}
}

void DebugTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Checkbox("Show CollisionDebug", &GameEngineLevel::IsDebug);
	ImGui::Checkbox("Show PixelDebug", &PixelManager::PixelDebugMode);

	OnFPSTime(_DeltaTime);
	ImGui::SeparatorText("Show Position");
	CameraPos();
	ScreenMousePos();
	WorldMousePos(_Level);

	const std::shared_ptr<SkyLerp>& Sky = PlayLevel::GetCurLevel()->GetSkyPtr();
	if (nullptr != Sky)
	{
		SkyColor();
		SkyOn();
	}

	TimeDebug();
	SoundDebug();
}


void DebugTab::OnFPSTime(float _DeltaTime)
{
	ImGui::SeparatorText("Fps");
	static float GUI_UpdateTime = 0.0f;

	GUI_UpdateTime += _DeltaTime;
	if (GUI_UpdateTime > 1.0f)
	{
		GUI_UpdateTime -= 1.0f;
		iFPS = static_cast<int>(1.0f / _DeltaTime);
	}
	const std::string FPS_String = "FPS : " + std::to_string(iFPS);

	ImGui::Text(FPS_String.c_str());
}

void DebugTab::CameraPos()
{
	float4 CameraPosition = PlayLevel::GetCurLevel()->GetLevelCameraPtr()->GetCameraCurrentPostion();
	ImGui::Text(("CameraPos :" + CameraPosition.ToString()).c_str());
}

void DebugTab::ScreenMousePos()
{
	std::string ScreenMousePos = "Screen : ";
	ScreenMousePos += GameEngineCore::MainWindow.GetMousePos().ToString();
	ImGui::Text(ScreenMousePos.c_str());
}

void DebugTab::WorldMousePos(GameEngineLevel* _CurLevel)
{
	std::string WorldMousePos = "World : ";
	WorldMousePos += _CurLevel->GetMainCamera()->GetWorldMousePos2D().ToString();
	ImGui::Text(WorldMousePos.c_str());
}

void DebugTab::SkyColor()
{
	ImGui::SeparatorText("Sky Light");
	const std::shared_ptr<SkyLerp>& Sky = PlayLevel::GetCurLevel()->GetSkyPtr();
	if (nullptr != Sky)
	{
		if (ImGui::SliderFloat4("Sky Color", &Sky->SkyColor.R, 0.0f, 1.0f, "%.2f"))
		{
			Sky->SetSkyColor();
		}
	}
}

void DebugTab::SkyOn()
{
	const std::shared_ptr<SkyLerp>& Sky = PlayLevel::GetCurLevel()->GetSkyPtr();
	if (nullptr != Sky)
	{
		if (ImGui::Checkbox("Sky On", &isSkyOn))
		{
			isSkyOn ? Sky->On() : Sky->Off();
		}
	}
}

void DebugTab::TimeDebug()
{
	ImGui::SeparatorText("TimeDebug");
	if (nullptr != PlayLevel::GetTimeManager())
	{
		if (ImGui::SliderFloat("TimeCustom", &PlayLevel::GetTimeManager()->GetTimePointer(), 0.0f, PlayLevel::GetTimeManager()->GetMaxTime(), "%.0f"))
		{
			PlayLevel::GetTimeManager()->Pause(true);
			PlayLevel::GetTimeManager()->SetTime(PlayLevel::GetTimeManager()->GetTime());
		}

		ImGui::Text(std::string("Time : " + std::to_string(PlayLevel::GetTimeManager()->GetTime())).c_str());

		ImGui::Text(std::string("Time : " + std::to_string(PlayLevel::GetTimeManager()->GetHour())).c_str());
		ImGui::SameLine();
		ImGui::Text(std::string(": " + std::to_string(PlayLevel::GetTimeManager()->GetMinute())).c_str());

		
		ImGui::Checkbox("Time Pause", &PlayLevel::GetTimeManager()->GetPause());
		ImGui::SameLine();
		ImGui::SliderFloat("Time Ratio", &PlayLevel::GetTimeManager()->GetTimeFlowRatio(), 1.0f, 10.0f, "%.0f");
	}
}

void DebugTab::SoundDebug()
{
	ImGui::SeparatorText("SoundDebug");
	ImGui::SliderFloat("Global Volume", &GlobalValue::GetGlobalVolumePointer(), 0.0f, 2.0f, "%.1f");
	if (true == ImGui::SliderFloat("BGM Volume", &GlobalValue::GetBGMVolumePointer(), 0.0f, 1.0f, "%.1f"))
	{
		ContentsLevel::GetBGMPlayerPtr()->SetVolume();
	}
	
	ImGui::SliderFloat("SFX Volume", &GlobalValue::GetSFXVolumePointer(), 0.0f, 1.0f, "%.1f");
}


void ManualTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Text("Left Arrow : Move Left ");
	ImGui::Text("Right Arrow  : Move Right ");
	ImGui::Text("Up Arrow  : Move Up & Front ");
	ImGui::Text("Donw Arrow  : Move Down & Back ");
	ImGui::Text("Shift + Arrow : Slow Move ");
	ImGui::Text("Ctrl : Ride Broom ");
	ImGui::Text("Z : Interaction with Entity");
	ImGui::Text("S : Open&Close Inventory");
	ImGui::Text("D : Open&Close Dictionary");
	ImGui::Text("Q : Select PrevTool");
	ImGui::Text("E : Select NextTool");
	ImGui::Text("1 : Create Item");
	ImGui::Text("Ctrl + 3 : Delete Item");
	ImGui::SameLine();
	ImGui::Text("(Alert!!! Do not use on empty inventory slots.)");
	ImGui::Text("Ctrl + 4 ~ 7 : Add Item");
	ImGui::Text("Ctrl + 8 : Unlock Inventory");

}


MapEditorTab* MapEditorTab::MapEditorGui = nullptr;
void MapEditorTab::Start()
{
	CreateItemTab<BaseRendererItemTab>("BaseRendererItemTab");
	CurItemTab = AllItemTabs[0];
	CreateItemTab<PropItemTab>("PropItemTab");


	MapEditorGui = this;
}



void MapEditorTab::ChangeItemTab(std::string_view _ItemName)
{
	CurItemTab = FindItemTab(_ItemName);
	SavePath.clear();
	LoadPath.clear();
}

std::shared_ptr<ItemTab> MapEditorTab::FindItemTab(std::string_view _ItemName)
{
	const std::string UpperName = GameEngineString::ToUpperReturn(_ItemName);

	for(const std::shared_ptr<ItemTab>& item : AllItemTabs)
	{
		if (UpperName == item->TabName)
		{
			return item;
		}
	}

	MsgBoxAssert("존재하지 않는 아이템을 참조하려 했습니다.");
	return nullptr;
}

std::string MapEditorTab::GetCurItemTabName()
{
	return CurItemTab->TabName;
}



void MapEditorTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (_Level->GetName() != "MapEditorLevel")
	{
		return;
	}

	if (ImGui::Checkbox("Show Only Pixel Collision", &PixelDebugValue))
	{
		std::vector<std::shared_ptr<RendererActor>> Actors = _Level->GetObjectGroupConvert<RendererActor>(0);

		if (true == PixelDebugValue)
		{
			for (const std::shared_ptr<RendererActor>& Actor : Actors)
			{
				Actor->Renderer->Off();
			}
		}
		else
		{
			for (const std::shared_ptr<RendererActor>& Actor : Actors)
			{
				Actor->Renderer->On();
		}
		}
	}

	if (ImGui::BeginTabBar("Eidtor"))
	{
		if (ImGui::BeginTabItem("Setting"))
		{
			SettingTab(_Level, _DeltaTime);

			ImGui::EndTabItem();
		}


		for (const std::shared_ptr<ItemTab>& ItemTab : AllItemTabs)
		{
			const char* CItemName = ItemTab->TabName.c_str();

			if (ImGui::BeginTabItem(CItemName))
			{
				if (CurItemTab->TabName != CItemName)
				{
					static_cast<MapEditorLevel*>(_Level)->SelectActor = nullptr;
					ChangeItemTab(CItemName);
				}

				CurItemTab->EditoritemTab(_Level, _DeltaTime);
				SaveTab(_Level, _DeltaTime);
				LoadTab(_Level, _DeltaTime);

				ImGui::EndTabItem();
			}

		}

		if (ImGui::BeginTabItem("Help"))
		{
			HelpTab(_Level, _DeltaTime);

			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();
}



void MapEditorTab::SaveTab(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::Button("Save"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Data");
		std::string DataPath = Dir.GetStringPath();

		OPENFILENAMEA OFN;
		char filePathName[256] = {};
		char lpstrFile[256] = {};
		static constexpr std::string_view filter1 = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
		OFN.lpstrFilter = filter1.data();
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = "map";
		OFN.lpstrInitialDir = DataPath.c_str();

		if (GetOpenFileNameA(&OFN) != 0)
		{
			SavePath = OFN.lpstrFile;
		}
	}

	if (false == SavePath.empty())
	{
		ImGui::Text(SavePath.c_str());

		MapEditorLevel* MapLevel = dynamic_cast<MapEditorLevel*>(_Level);

		if (ImGui::Button("Save GroupData"))
		{
			CurItemTab->SaveItemTab(_Level);
		}

		ImGui::InputText("Save Path", PathString, 256);
	}
}

void MapEditorTab::SettingTab(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::Button("Yard Base Setting"))
	{
		const float4 BaseScale = GlobalValue::GetWindowScale();

		float4 BasePosition = BaseScale.Half();
		BasePosition.Y *= -1.0f;
		BasePosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

		MapEditorLevel* MapEditorPtr = static_cast<MapEditorLevel*>(_Level);
		MapEditorPtr->MapBaseRenderer->SetSprite("GroundBase.png");
		MapEditorPtr->MapBaseRenderer->GetImageTransform().SetLocalScale(BaseScale);
		MapEditorPtr->MapBaseRenderer->Transform.SetLocalPosition(BasePosition);
		MapEditorPtr->MapBaseRenderer->On();
		MapEditorPtr->m_BaseScale = BaseScale;
	}

	if (ImGui::Button("Center Field Base Setting"))
	{
		MapEditorLevel* MapEditorPtr = static_cast<MapEditorLevel*>(_Level);
		MapEditorPtr->CenterFieldMapSetting();
	}

	if (ImGui::Button("Reset Camera"))
	{
		float4 Position = GlobalValue::GetWindowScale().Half();
		Position.Y *= -1.0f;
		_Level->GetMainCamera()->Transform.SetLocalPosition(Position);
	}
}

void MapEditorTab::LoadTab(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::Button("Load"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Data");

		OPENFILENAMEA OFN;
		char filePathName[256] = "";
		char lpstrFile[256] = "";
		static char filter[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		std::string Path = Dir.GetStringPath();

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = "map";
		OFN.lpstrInitialDir = Path.c_str();

		if (GetOpenFileNameA(&OFN) != 0) {
			LoadPath = OFN.lpstrFile;
		}
	}

	if ("" != LoadPath)
	{
		ImGui::Text(LoadPath.c_str());

		if (ImGui::Button("Load Data"))
		{
			CurItemTab->LoadItemTab(_Level);
		}
	}
}



void BaseRendererItemTab::TabStart()
{
	SpriteNames.reserve(128);

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\Map\\MapSingle");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile pFile = Files[i];
		SpriteNames.push_back(pFile.GetFileName());
	}

	DepthTypes.insert(std::make_pair("DarkGrass", static_cast<int>(ERENDERDEPTH::DarkGrass)));
	DepthTypes.insert(std::make_pair("DeepDarkGrass", static_cast<int>(ERENDERDEPTH::DeepDarkGrass)));
	DepthTypes.insert(std::make_pair("Grass", static_cast<int>(ERENDERDEPTH::Grass)));
	DepthTypes.insert(std::make_pair("Object", static_cast<int>(ERENDERDEPTH::Object)));
	DepthTypes.insert(std::make_pair("Hill_Object", static_cast<int>(ERENDERDEPTH::Hill_Object)));
}

void BaseRendererItemTab::EditoritemTab(GameEngineLevel* _Level, float _DeltaTime)
{
	MapEditorLevel* EditorLevel = dynamic_cast<MapEditorLevel*>(_Level);

	std::vector<const char*> CNames;
	CNames.reserve(SpriteNames.size());

	for (size_t i = 0; i < SpriteNames.size(); i++)
	{
		CNames.push_back(SpriteNames[i].c_str());
	}

	if (ImGui::ListBox("SpriteNames", &SelectSpriteItem, &CNames[0], static_cast<int>(CNames.size())))
	{
		if (nullptr != EditorLevel->SelectActor)
		{
			EditorLevel->SelectActor->Renderer->SetSprite(SpriteNames[SelectSpriteItem]);
		}

		EditorLevel->_SelcetSprite = SpriteNames[SelectSpriteItem];
		SelectSpriteName = SpriteNames[SelectSpriteItem];
	}

	ImGui::Text("Select : ");
	ImGui::SameLine();
	if (nullptr != EditorLevel->SelectActor)
	{
		ImGui::Text("On");
	}
	else
	{
		ImGui::Text("Off");
	}

	if (false == SelectSpriteName.empty())
	{
		std::vector<const char*> CNames;

		CNames.reserve(DepthTypes.size());
		for (std::pair<const std::string, int>& Type : DepthTypes)
		{
			CNames.push_back(Type.first.c_str());
		}

		if (ImGui::ListBox("Depth", &SelectDepthItem, &CNames[0], static_cast<int>(CNames.size())), 3)
		{
			static_cast<MapEditorLevel*>(_Level)->_SelectDepth = DepthTypes.find(CNames[SelectDepthItem])->second;
		}


		if (nullptr != EditorLevel->SelectActor)
		{
			if (ImGui::SliderFloat("Renderer Correction", &EditorLevel->_RendererHeight, -100.0f, 200.0f, "%.0f"))
			{
				const std::shared_ptr<GameEngineSpriteRenderer>& Renderer = EditorLevel->SelectActor->Renderer;
				float4 Position = Renderer->Transform.GetLocalPosition();
				Position.Y = EditorLevel->_RendererHeight;
				Renderer->Transform.SetLocalPosition(Position);
			}

			if (true == _Level->IsDebug)
			{
				float4 WPos = EditorLevel->SelectActor->Transform.GetWorldPosition();
				WPos.Z -= 1.0f;
				GameEngineDebug::DrawBox2D(float4(4.0f, 4.0f), float4::ZERO, WPos);
			}
		}
	}

	if (ImGui::Button("All Clear"))
	{
		std::vector<std::shared_ptr<RendererActor>> GroupObject = _Level->GetObjectGroupConvert<RendererActor>(0);
		for (const std::shared_ptr<RendererActor>& Object : GroupObject)
		{
			Object->Death();
		}

		EditorLevel->SelectActor = nullptr;
	}
}

void BaseRendererItemTab::SaveItemTab(GameEngineLevel* _Level)
{
	GameEngineSerializer BinSerial;
	const std::vector<std::shared_ptr<GroundRenderUnit>> ObjectGroup = _Level->GetObjectGroupConvert<GroundRenderUnit>(0);

	BinSerial << static_cast<unsigned int>(ObjectGroup.size());

	for (std::shared_ptr<GroundRenderUnit> RenderUnit : ObjectGroup)
	{
		RenderUnit->Serializer(BinSerial);
	}

	GameEngineFile File = Parent->SavePath;
	File.Open(FileOpenType::Write, FileDataType::Binary);
	File.Write(BinSerial);
}

void BaseRendererItemTab::LoadItemTab(GameEngineLevel* _Level)
{
	GameEngineSerializer LoadBin;

	GameEngineFile File = Parent->LoadPath;
	File.Open(FileOpenType::Read, FileDataType::Binary);
	File.DataAllRead(LoadBin);

	std::vector<std::shared_ptr<GroundRenderUnit>> ObjectGroup = _Level->GetObjectGroupConvert<GroundRenderUnit>(0);
	for (const std::shared_ptr<GroundRenderUnit>& Object : ObjectGroup)
	{
		Object->Death();
	}

	// 객체 수 읽어옴
	unsigned int ActorCount = 0;
	LoadBin >> ActorCount;

	for (unsigned int i = 0; i < ActorCount; i++)
	{
		std::shared_ptr<GroundRenderUnit> Object = _Level->CreateActor<GroundRenderUnit>();
		Object->DeSerializer(LoadBin);
	}
}



void PropItemTab::TabStart()
{
	{
		SpriteNames.reserve(128);

		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\Map\\MapSingle");
		const std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile pFile : Files)
		{
			SpriteNames.push_back(pFile.GetFileName());
		}
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\Map\\MapPixel");

		const std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile pFile : Files)
		{
			PixelSpriteNames.push_back(pFile.GetFileName());
		}
	}


	{
		DepthTypes.insert(std::make_pair("DarkGrass", static_cast<int>(ERENDERDEPTH::DarkGrass)));
		DepthTypes.insert(std::make_pair("DeepDarkGrass", static_cast<int>(ERENDERDEPTH::DeepDarkGrass)));
		DepthTypes.insert(std::make_pair("Grass", static_cast<int>(ERENDERDEPTH::Grass)));
		DepthTypes.insert(std::make_pair("Object", static_cast<int>(ERENDERDEPTH::Object)));
		DepthTypes.insert(std::make_pair("Hill_Object", static_cast<int>(ERENDERDEPTH::Hill_Object)));
	}
}

void PropItemTab::EditoritemTab(GameEngineLevel* _Level, float _DeltaTime)
{
	MapEditorLevel* EditorLevel = dynamic_cast<MapEditorLevel*>(_Level);

	{
		std::vector<const char*> CNames;
		CNames.reserve(SpriteNames.size());

		for (int i = 0; i < SpriteNames.size(); i++)
		{
			CNames.push_back(SpriteNames[i].c_str());
		}

		if (ImGui::Combo("SpriteNames", &SelectSpriteItem, &CNames[0], static_cast<int>(CNames.size()), 8))
		{
			if (nullptr != EditorLevel->SelectActor)
			{
				EditorLevel->SelectActor->Renderer->SetSprite(SpriteNames[SelectSpriteItem]);
			}

			EditorLevel->_SelcetSprite = SpriteNames[SelectSpriteItem];
			SelectSpriteName = SpriteNames[SelectSpriteItem];
		}

		ImGui::SameLine();
		HelpMarker::Marker("Select Sprite And Pixel Collision Texture");
	}

	ImGui::Text("Select : ");
	ImGui::SameLine();
	if (nullptr != EditorLevel->SelectActor)
	{
		ImGui::Text("On");
	}
	else
	{
		ImGui::Text("Off");
	}

	if (false == SelectSpriteName.empty())
	{
		std::vector<const char*> CNames;

		CNames.reserve(DepthTypes.size());
		for (std::pair<const std::string, int>& Type : DepthTypes)
		{
			CNames.push_back(Type.first.c_str());
		}

		if (ImGui::ListBox("Depth", &SelectDepthItem, &CNames[0], static_cast<int>(CNames.size())))
		{
			static_cast<MapEditorLevel*>(_Level)->_SelectDepth = DepthTypes.find(CNames[SelectDepthItem])->second;
		}


		if (nullptr != EditorLevel->SelectActor)
		{
			if (ImGui::SliderFloat("Adjustment Height", &EditorLevel->_RendererHeight, 0.0f, 200.0f, "%.0f"))
			{
				EditorLevel->SelectActor->Renderer->Transform.SetLocalPosition(float4(Width, EditorLevel->_RendererHeight));
			}
			if (ImGui::SliderFloat("Adjustment Weight", &Width, -100.0f, 100.0f, "%.0f"))
			{
				EditorLevel->SelectActor->Renderer->Transform.SetLocalPosition(float4(Width, EditorLevel->_RendererHeight));
			}

			if (true == _Level->IsDebug)
			{
				float4 WPos = EditorLevel->SelectActor->Transform.GetWorldPosition();
				WPos.Z -= 1.0f;
				GameEngineDebug::DrawBox2D(float4(4.0f, 4.0f), float4::ZERO, WPos);
			}
		}

		{
			std::vector<const char*> CNames;
			CNames.reserve(PixelSpriteNames.size());

			for (const std::string& SpriteName : PixelSpriteNames)
			{
				CNames.push_back(SpriteName.c_str());
			}

			if (ImGui::Combo("Pixel Sprite List", &SelectPixelSpriteItem, &CNames[0], static_cast<int>(CNames.size())))
			{
				EditorLevel->_SelcetPixelSprite = PixelSpriteNames[SelectPixelSpriteItem];
				SelectSpriteName = PixelSpriteNames[SelectPixelSpriteItem];

				if (nullptr != EditorLevel->SelectActor)
				{
					NormalPropEditor* Object = static_cast<NormalPropEditor*>(EditorLevel->SelectActor);
					Object->ChangePixeldata(SelectSpriteName);
				}
			}
		}
	}

	if (ImGui::Button("All Clear"))
	{
		const std::vector<std::shared_ptr<NormalPropEditor>> Objects = _Level->GetObjectGroupConvert<NormalPropEditor>(0);
		for (const std::shared_ptr<NormalPropEditor>& Object : Objects)
		{
			Object->Death();
		}

		EditorLevel->SelectActor = nullptr;
	}
}

void PropItemTab::SaveItemTab(GameEngineLevel* _Level)
{
	constexpr std::uint32_t GroupIndex = 0;
	GameEngineSerializer BinSerial;
	const std::vector<std::shared_ptr<NormalPropEditor>> ObjectGroup = _Level->GetObjectGroupConvert<NormalPropEditor>(GroupIndex);

	const std::uint32_t objectCount = static_cast<std::uint32_t>(ObjectGroup.size());
	BinSerial << objectCount;

	for(const std::shared_ptr<NormalPropEditor>& Object : ObjectGroup)
	{
		Object->Serializer(BinSerial);
	}

	// Write
	GameEngineFile File = Parent->SavePath;
	File.Open(FileOpenType::Write, FileDataType::Binary);
	File.Write(BinSerial);
}

void PropItemTab::LoadItemTab(GameEngineLevel* _Level)
{
	GameEngineSerializer LoadBin;

	GameEngineFile File = Parent->LoadPath;
	File.Open(FileOpenType::Read, FileDataType::Binary);
	File.DataAllRead(LoadBin);

	std::vector<std::shared_ptr<NormalPropEditor>> ObjectGroup = _Level->GetObjectGroupConvert<NormalPropEditor>(0);
	for (const std::shared_ptr<NormalPropEditor>& Object : ObjectGroup)
	{
		Object->Death();
	}

	// 객체 수 읽어옴
	unsigned int ActorCount = 0;
	LoadBin >> ActorCount;

	for (size_t i = 0; i < ActorCount; i++)
	{
		std::shared_ptr<NormalPropEditor> Object = _Level->CreateActor<NormalPropEditor>();
		Object->DeSerializer(LoadBin);
	}
}



void MapEditorTab::HelpTab(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Text("Camera");
	ImGui::Text("Shift : Camera Acceleration ");
	ImGui::Text("A : Move Left ");
	ImGui::Text("W : Move Up & Front ");
	ImGui::Text("S : Move Down & Back ");
	ImGui::Text("D : Move Right ");
	ImGui::Text("");

	ImGui::Text("Select");
	ImGui::Text("MMouseButton : Create Actor");
	ImGui::Text("RMouseButton : Select Actor");
	ImGui::Text("LMouseButton : Drag Selected Actor");
	ImGui::Text("Arrow : Move Actor 1px");
	ImGui::Text("Q : Rotate Transform");
	ImGui::Text("E : Rotate Transform");
	ImGui::Text("X : Erase Actor");
	ImGui::Text("F : Place Actor ");
}


void LightTest::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == FireWork)
	{
		if (ImGui::Button("SetFireWorkTest"))
		{
			float4 FireWorksPos = GlobalValue::GetWindowScale().Half();
			FireWorksPos.Y *= -1.0f;

			FireWork = _Level->CreateActor<FireWorks>();
			FireWork->Transform.SetLocalPosition(FireWorksPos);
			FireWork->Init();
		}
	}


	if (nullptr != FireWork)
	{
		ImGui::SeparatorText("ColorEdit");

		if (ImGui::ColorEdit4("Color4", &LightColor.X))
		{
			FireWork->SetLightColor(LightColor);
		}
	}
}