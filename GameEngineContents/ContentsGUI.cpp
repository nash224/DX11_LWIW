#include "PreCompile.h"
#include "ContentsGUI.h"

#include "MapEditorLevel.h"
#include "PlayLevel.h"

#include "CameraControler.h"

#include "BackDrop_PlayLevel.h"

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



	/*BackDrop_PlayLevel::MainBackDrop->CreatePropInCurBackDrop();*/

	// std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	// Position, Rotation
	// Depth => (RenderDepth, ZOrder)
	// Renderer->SetSprite
	/*Renderer->Transform.SetLocalPosition();*/
	// pushback

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


void DebugTab::MapEditorMode()
{

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


void MapEditorTab::Start()
{
	
}


void MapEditorTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (_Level->GetName() != "MapEditorLevel")
	{
		return;
	}

	if (ImGui::BeginTabBar("Eidtor"))
	{
		if (ImGui::BeginTabItem("SaveTab"))
		{
			if (ImGui::Button("Save"))
			{
				GameEngineDirectory Dir;
				Dir.MoveParentToExistsChild("ContentsResources");
				Dir.MoveChild("ContentsResources");
				Dir.MoveChild("Data");

				std::string Path = Dir.GetStringPath();

				OPENFILENAMEA OFN;
				char filePathName[100] = "";
				char lpstrFile[100] = "";
				static char filter[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

				memset(&OFN, 0, sizeof(OPENFILENAME));
				OFN.lStructSize = sizeof(OPENFILENAME);
				OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
				OFN.lpstrFilter = filter;
				OFN.lpstrFile = lpstrFile;
				OFN.nMaxFile = 100;
				OFN.lpstrDefExt = "GameData";
				OFN.lpstrInitialDir = Path.c_str();

				if (GetSaveFileNameA(&OFN) != 0) {
					SavePath = OFN.lpstrFile;
				}
			}

			if ("" != SavePath)
			{
				ImGui::Text(SavePath.c_str());

				MapEditorLevel* MapLevel = dynamic_cast<MapEditorLevel*>(_Level);

				if (nullptr == MapLevel)
				{
					return;
				}

				/*if (ImGui::Button("MapDataSave"))
				{
					GameEngineSerializer BinSer;
					BinSer << MapLevel->BackGroundRenderer->GetSprite()->GetName();
					std::vector<std::shared_ptr<Monster>> ObjectType = _Level->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);
					BinSer << static_cast<unsigned int>(ObjectType.size());
					for (size_t i = 0; i < ObjectType.size(); i++)
					{
						ObjectType[i]->Serializer(BinSer);
					}


					GameEngineFile File = SavePath;
					File.Open(FileOpenType::Write, FileDataType::Binary);
					File.Write(BinSer);

				}*/

				ImGui::InputText("Save Path", BackGroundName, 256);

				//if (ImGui::Button("Setting"))
				//{

				//	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(BackGroundName);

				//	float4 HScale = Tex->GetScale().Half();
				//	HScale.Y *= -1.0f;

				//	MapLevel->BackGroundRenderer->SetSprite(BackGroundName);
				//	MapLevel->BackGroundRenderer->Transform.SetLocalPosition(HScale);
				//}
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("LoadTab"))
		{

			if (ImGui::Button("Load"))
			{
				GameEngineDirectory Dir;
				Dir.MoveParentToExistsChild("ContentsResources");
				Dir.MoveChild("ContentsResources");
				Dir.MoveChild("Data");


				OPENFILENAMEA OFN;
				char filePathName[100] = "";
				char lpstrFile[100] = "";
				static char filter[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

				std::string Path = Dir.GetStringPath();

				memset(&OFN, 0, sizeof(OPENFILENAME));
				OFN.lStructSize = sizeof(OPENFILENAME);
				OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
				OFN.lpstrFilter = filter;
				OFN.lpstrFile = lpstrFile;
				OFN.nMaxFile = 100;
				OFN.lpstrDefExt = "GameData";
				OFN.lpstrInitialDir = Path.c_str();

				if (GetOpenFileNameA(&OFN) != 0) {
					LoadPath = OFN.lpstrFile;
				}
			}

			if (LoadPath != "")
			{
				ImGui::Text(LoadPath.c_str());

				if (ImGui::Button("MapDataLoad"))
				{
					GameEngineSerializer BinSer;

					GameEngineFile File = LoadPath;
					File.Open(FileOpenType::Read, FileDataType::Binary);
					File.DataAllRead(BinSer);

					//std::vector<std::shared_ptr<Monster>> ObjectType = _Level->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);
					//for (size_t i = 0; i < ObjectType.size(); i++)
					//{
					//	// 다 죽인다.
					//	ObjectType[i]->Death();
					//}


					//std::string BackFileName;
					//BinSer >> BackFileName;
					//unsigned int MonsterCount = 0;
					//BinSer >> MonsterCount;

					//for (size_t i = 0; i < MonsterCount; i++)
					//{
					//	std::shared_ptr<Monster> Object = _Level->CreateActor<Monster>(ContentsObjectType::Monster);
					//	Object->DeSerializer(BinSer);
					//}



					// GameEngineSerializer BinSer;
					// SaveBin << MapLevel->BackGroundRenderer->GetSprite()->GetName();
				}
			}



			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();

	// MapLevel->BackGroundRenderer->SetSprite
}