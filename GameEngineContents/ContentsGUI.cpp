#include "PreCompile.h"
#include "ContentsGUI.h"

#include "MapEditorLevel.h"
#include "PlayLevel.h"

#include "CameraControler.h"
#include "BackDrop_PlayLevel.h"

#include "GroundRenderUnit.h"
#include "NormalProp.h"

#include "UI_Inventory.h"

#include "ItemData.h"



void ContentsGUI::Start()
{
	AllTabs.push_back(std::make_shared<LevelChangeTab>("LevelChange")); 
	CurTab = AllTabs[0];
	AllTabs.push_back(std::make_shared<CheatTab>("CheatTab"));
	AllTabs.push_back(std::make_shared<MapEditorTab>("MapEditor"));
	AllTabs.push_back(std::make_shared<DebugTab>("Debug"));
	AllTabs.push_back(std::make_shared<ManualTab>("Manual"));

	for (size_t i = 0; i < AllTabs.size(); i++)
	{
		AllTabs[i]->Start();
	}
}



void ContentsGUI::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	for (size_t i = 0; i < AllTabs.size(); i++)
	{
		if (nullptr != CurTab)
		{
			if (ImGui::Button(AllTabs[i]->Name.c_str()))
			{
				CurTab = AllTabs[i];

				if ("MapEditor" == AllTabs[i]->Name)
				{
					GameEngineCore::ChangeLevel("MapEditorLevel");
				}
			}
		}

		if (i != static_cast<int>(AllTabs.size()) - 1)
		{
			ImGui::SameLine();
		}
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _Delta);
	}
}



void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevelRef = GameEngineCore::GetAllLevel();
	for (std::pair<std::string, std::shared_ptr<GameEngineLevel>> pair : AllLevelRef)
	{
		if (ImGui::Button((pair.first).c_str()))
		{
			GameEngineCore::ChangeLevel(pair.first);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void CheatTab::Start()
{
	EITEM_TYPE::Ingredient;
	std::map<std::string, std::shared_ptr<ItemData>>& AllItemData = ItemData::GetAllData();

	std::map<std::string, std::shared_ptr<ItemData>>::iterator StartIter = AllItemData.begin();
	std::map<std::string, std::shared_ptr<ItemData>>::iterator EndIter = AllItemData.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		std::shared_ptr<ItemData> ItemData = (*StartIter).second;

		ItemContainer[static_cast<int>(ItemData->ItemType)].push_back(ItemData->Name);
	}
}

void CheatTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (_Level->GetName() == "MainMenu")
	{
		return;
	}

	if (ImGui::BeginTabBar("Cheat Items")) 
	{
		char Number = 0;
		for (std::pair<const int, std::list<std::string>>& _Pair : ItemContainer)
		{
			std::string ItemTabName = "ItemType" + std::to_string(Number);
			std::string ListName = "ItemList" + std::to_string(Number);
			if (ImGui::BeginTabItem(ItemTabName.c_str()))
			{
				std::list<std::string>& NameGroup = _Pair.second;

				std::list<std::string>::iterator StartIter = NameGroup.begin();
				std::list<std::string>::iterator EndIter = NameGroup.end();

				std::vector<const char*> CNames;
				for (; StartIter != EndIter; ++StartIter)
				{
					CNames.push_back((*StartIter).c_str());
				}
				
				if (ImGui::ListBox(ListName.c_str(), &SelectItem, &CNames[0], static_cast<int>(CNames.size())))
				{
					UI_Inventory::PushItem(CNames[SelectItem]);
				}
				ImGui::EndTabItem();
			}

			++Number;
		}


		if (ImGui::BeginTabItem("Inventory Cheat"))
		{
			if (nullptr == UI_Inventory::MainInventory)
			{
				MsgBoxAssert("인벤토리가 존재하지 않습니다.");
				return;
			}

			if (ImGui::Button("Unlock Slot"))
			{
				UI_Inventory::MainInventory->UnlockSlot();
			}

			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();
}

void DebugTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Checkbox("Show CollisionDebug", &GameEngineLevel::IsDebug); 
	if (true == GameEngineLevel::IsDebug)
	{
		ImGui::Checkbox("Show PixelDebug", &PlayLevel::PixelDebugMode);
	}

	float4 CamepraPosition = GlobalValue::g_CameraControler->GetCameraCurrentPostion();
	ImGui::Text(CamepraPosition.ToString().c_str());

	if (ImGui::Button("Play"))
	{
		int a = 0;
	}

	if (ImGui::Checkbox("CheckBox", &IsCheckBox))
	{

	}

	if (ImGui::SliderInt("Slider", &SliderAmount, 0, 100, "%d"))
	{

	}

	OnFPSTime(_DeltaTime);
	MousePos();
}


void DebugTab::OnFPSTime(float _DeltaTime)
{
	static float GUI_UpdateTime = 0.0f;

	GUI_UpdateTime += _DeltaTime;
	if (GUI_UpdateTime > 1.0f)
	{
		GUI_UpdateTime -= 1.0f;
		iFPS = static_cast<int>(1.0f / _DeltaTime);
	}
	std::string FPS_String = "FPS : " + std::to_string(iFPS);

	ImGui::Text(FPS_String.c_str());
}

void DebugTab::MousePos()
{
	std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();
	ImGui::Text(MousePos.c_str());
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
}

std::shared_ptr<ItemTab> MapEditorTab::FindItemTab(std::string_view _ItemName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_ItemName);

	for (size_t i = 0; i < AllItemTabs.size(); i++)
	{
		std::shared_ptr<ItemTab> item = AllItemTabs[i];

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

	if (ImGui::BeginTabBar("Eidtor"))
	{
		if (ImGui::BeginTabItem("Setting"))
		{
			SettingTab(_Level, _DeltaTime);

			ImGui::EndTabItem();
		}


		for (size_t i = 0; i < AllItemTabs.size(); i++)
		{
			const char* CItemName = AllItemTabs[i]->TabName.c_str();

			if (ImGui::BeginTabItem(CItemName))
			{
				ChangeItemTab(CItemName);
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
		char filePathName[256] = "";
		char lpstrFile[256] = "";
		static char filter1[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
		OFN.lpstrFilter = filter1;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = "map";
		OFN.lpstrInitialDir = DataPath.c_str();

		if (GetOpenFileNameA(&OFN) != 0)
		{
			SavePath = OFN.lpstrFile;
		}
	}

	if ("" != SavePath)
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
		float4 BaseScale = GlobalValue::GetWindowScale();

		float4 BasePosition = BaseScale.Half();
		BasePosition.Y *= -1.0f;
		BasePosition.Z = GlobalUtils::CalculateDepth(ERENDERDEPTH::Back_Paint);

		MapEditorLevel* MapEditorPtr = dynamic_cast<MapEditorLevel*>(_Level);
		MapEditorPtr->m_MapBaseRenderer->SetSprite("GroundBase.png");
		MapEditorPtr->m_MapBaseRenderer->GetImageTransform().SetLocalScale(BaseScale);
		MapEditorPtr->m_MapBaseRenderer->Transform.SetLocalPosition(BasePosition);
		MapEditorPtr->m_MapBaseRenderer->On();
		MapEditorPtr->m_BaseScale = BaseScale;
	}

	if (ImGui::Button("Center Field Base Setting"))
	{
		float4 BaseScale = float4(1920.0f, 1080.0f);
		float4 BasePosition = BaseScale.Half();
		BasePosition.Y *= -1.0f;

		MapEditorLevel* MapEditorPtr = dynamic_cast<MapEditorLevel*>(_Level);
		MapEditorPtr->m_MapBaseRenderer->SetSprite("GroundBase.png");
		MapEditorPtr->m_MapBaseRenderer->GetImageTransform().SetLocalScale(BaseScale);
		MapEditorPtr->m_MapBaseRenderer->Transform.SetLocalPosition(BasePosition);
		MapEditorPtr->m_MapBaseRenderer->On();
		MapEditorPtr->m_BaseScale = BaseScale;
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
	DepthTypes.insert(std::make_pair("Object", static_cast<int>(ERENDERDEPTH::Object)));
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

	if ("" != SelectSpriteName)
	{
		std::vector<const char*> CNames;

		CNames.reserve(DepthTypes.size());
		for (std::pair<const std::string, int>& Type : DepthTypes)
		{
			CNames.push_back(Type.first.c_str());
		}

		if (ImGui::ListBox("Depth", &SelectDepthItem, &CNames[0], static_cast<int>(CNames.size())), 3)
		{
			dynamic_cast<MapEditorLevel*>(_Level)->_SelectDepth = DepthTypes.find(CNames[SelectDepthItem])->second;
		}


		if (nullptr != EditorLevel->SelectActor)
		{
			if (ImGui::SliderFloat("Adjustment Height", &EditorLevel->_RendererHeight, 0.0f, 200.0f, "%.0f"))
			{
				EditorLevel->SelectActor->m_Renderer->Transform.SetLocalPosition(float4(0.0f, EditorLevel->_RendererHeight));
			}

			float4 WPos = EditorLevel->SelectActor->Transform.GetWorldPosition();
			WPos.Z -= 1.0f;
			GameEngineDebug::DrawBox2D(float4(4.0f, 4.0f), float4::ZERO, WPos);
		}
	}

	if (ImGui::Button("All Clear"))
	{
		std::vector<std::shared_ptr<RendererActor>> Objects = _Level->GetObjectGroupConvert<RendererActor>(0);
		for (size_t i = 0; i < Objects.size(); i++)
		{
			Objects[i]->Death();
		}

		EditorLevel->SelectActor = nullptr;
	}
}

void BaseRendererItemTab::SaveItemTab(GameEngineLevel* _Level)
{
	GameEngineSerializer BinSerial;
	std::vector<std::shared_ptr<GroundRenderUnit>> ObjectType = _Level->GetObjectGroupConvert<GroundRenderUnit>(0);

	// 객체수 저장
	BinSerial << static_cast<unsigned int>(ObjectType.size());

	// 객체 정보 저장
	for (size_t i = 0; i < ObjectType.size(); i++)
	{
		ObjectType[i]->Serializer(BinSerial);
	}

	// Write
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

	std::vector<std::shared_ptr<NormalProp>> ObjectGroup = _Level->GetObjectGroupConvert<NormalProp>(0);
	for (size_t i = 0; i < ObjectGroup.size(); i++)
	{
		ObjectGroup[i]->Death();
	}

	// 객체 수 읽어옴
	unsigned int ActorCount = 0;
	LoadBin >> ActorCount;

	for (size_t i = 0; i < ActorCount; i++)
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>();
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
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			SpriteNames.push_back(pFile.GetFileName());
		}
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\Map\\MapPixel");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			PixelSpriteNames.push_back(pFile.GetFileName());
		}
	}


	{
		DepthTypes.insert(std::make_pair("DarkGrass", static_cast<int>(ERENDERDEPTH::DarkGrass)));
		DepthTypes.insert(std::make_pair("DeepDarkGrass", static_cast<int>(ERENDERDEPTH::DeepDarkGrass)));
		DepthTypes.insert(std::make_pair("Object", static_cast<int>(ERENDERDEPTH::Object)));
	}
}

void PropItemTab::EditoritemTab(GameEngineLevel* _Level, float _DeltaTime)
{
	MapEditorLevel* EditorLevel = dynamic_cast<MapEditorLevel*>(_Level);

	{
		std::vector<const char*> CNames;
		CNames.reserve(SpriteNames.size());

		for (size_t i = 0; i < SpriteNames.size(); i++)
		{
			CNames.push_back(SpriteNames[i].c_str());
		}

		if (ImGui::ListBox("SpriteNames", &SelectSpriteItem, &CNames[0], static_cast<int>(CNames.size())))
		{
			EditorLevel->_SelcetSprite = SpriteNames[SelectSpriteItem];
			SelectSpriteName = SpriteNames[SelectSpriteItem];
		}
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

	if ("" != SelectSpriteName)
	{
		std::vector<const char*> CNames;

		CNames.reserve(DepthTypes.size());
		for (std::pair<const std::string, int>& Type : DepthTypes)
		{
			CNames.push_back(Type.first.c_str());
		}

		if (ImGui::ListBox("Depth", &SelectDepthItem, &CNames[0], static_cast<int>(CNames.size())), 3)
		{
			dynamic_cast<MapEditorLevel*>(_Level)->_SelectDepth = DepthTypes.find(CNames[SelectDepthItem])->second;
		}


		if (nullptr != EditorLevel->SelectActor)
		{
			if (ImGui::SliderFloat("Adjustment Height", &EditorLevel->_RendererHeight, 0.0f, 200.0f, "%.0f"))
			{
				EditorLevel->SelectActor->m_Renderer->Transform.SetLocalPosition(float4(0.0f, EditorLevel->_RendererHeight));
			}

			float4 WPos = EditorLevel->SelectActor->Transform.GetWorldPosition();
			WPos.Z -= 1.0f;
			GameEngineDebug::DrawBox2D(float4(4.0f, 4.0f), float4::ZERO, WPos);
		}

		{
			std::vector<const char*> CNames;
			CNames.reserve(PixelSpriteNames.size());

			for (size_t i = 0; i < PixelSpriteNames.size(); i++)
			{
				CNames.push_back(PixelSpriteNames[i].c_str());
			}

			if (ImGui::ListBox("Pixel Sprite List", &SelectPixelSpriteItem, &CNames[0], static_cast<int>(CNames.size())))
			{
				EditorLevel->_SelcetPixelSprite = PixelSpriteNames[SelectPixelSpriteItem];
				SelectSpriteName = PixelSpriteNames[SelectPixelSpriteItem];
			}
		}
	}

	if (ImGui::Button("All Clear"))
	{
		std::vector<std::shared_ptr<NormalProp>> Objects = _Level->GetObjectGroupConvert<NormalProp>(0);
		for (size_t i = 0; i < Objects.size(); i++)
		{
			Objects[i]->Death();
		}

		EditorLevel->SelectActor = nullptr;
	}
}

void PropItemTab::SaveItemTab(GameEngineLevel* _Level)
{
	GameEngineSerializer BinSerial;
	std::vector<std::shared_ptr<NormalProp>> ObjectType = _Level->GetObjectGroupConvert<NormalProp>(0);

	// 객체수 저장
	BinSerial << static_cast<unsigned int>(ObjectType.size());

	// 객체 정보 저장
	for (size_t i = 0; i < ObjectType.size(); i++)
	{
		ObjectType[i]->Serializer(BinSerial);
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

	std::vector<std::shared_ptr<NormalProp>> ObjectGroup = _Level->GetObjectGroupConvert<NormalProp>(0);
	for (size_t i = 0; i < ObjectGroup.size(); i++)
	{
		ObjectGroup[i]->Death();
	}

	// 객체 수 읽어옴
	unsigned int ActorCount = 0;
	LoadBin >> ActorCount;

	for (size_t i = 0; i < ActorCount; i++)
	{
		std::shared_ptr<NormalProp> Object = _Level->CreateActor<NormalProp>();
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