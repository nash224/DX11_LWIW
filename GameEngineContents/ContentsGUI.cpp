#include "PreCompile.h"
#include "ContentsGUI.h"

#include "PlayLevel.h"
#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"


void ContentsGUI::Start()
{
	AllTabs.push_back(std::make_shared<LevelChangeTab>("LevelChange"));
	CurTab = AllTabs[0];
	AllTabs.push_back(std::make_shared<Field_CenterTab>("Field_Center"));
	AllTabs.push_back(std::make_shared<MapEditorTab>("MapEditor"));
	AllTabs.push_back(std::make_shared<DebugTab>("Debug"));
	AllTabs.push_back(std::make_shared<ManualTab>("Manual"));
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




void Field_CenterTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::BeginTabBar("tabs", 0)) {
		if (ImGui::BeginTabItem("item")) {
			if (ImGui::Button("click this"))
			{

			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("item2")) {
			ImGui::Text("test  tab text");
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
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


void MapEditorTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MapEditorMode();
	}



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


void MapEditorTab::OnFPSTime(float _DeltaTime)
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

void MapEditorTab::MousePos()
{
	std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();
	ImGui::Text(MousePos.c_str());
}


void MapEditorTab::MapEditorMode()
{

}