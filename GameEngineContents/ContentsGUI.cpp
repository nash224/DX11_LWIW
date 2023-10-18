#include "PreCompile.h"
#include "ContentsGUI.h"

#include "BackDrop_PlayLevel.h"


void ContentsGUI::Start()
{
	AllTabs.push_back(std::make_shared<LevelChangeTab>("LevelChange"));
	CurTab = AllTabs[0];
	AllTabs.push_back(std::make_shared<Field_CenterTab>("Field_Center"));
	AllTabs.push_back(std::make_shared<MapEditorTab>("MapEditor"));
	AllTabs.push_back(std::make_shared<DebugTab>("Debug"));
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

	if (ImGui::Button("Field_Center"))
	{
		GameEngineCore::ChangeLevel("Field_Center");
		return;
	}

	if (ImGui::Button("WitchHouse_Yard"))
	{
		GameEngineCore::ChangeLevel("WitchHouse_Yard");
		return;
	}

	if (ImGui::Button("WitchHouse_UpFloor"))
	{
		GameEngineCore::ChangeLevel("WitchHouse_UpFloor");
		return;
	}


	if (ImGui::Button("CreateActor"))
	{
		GameEngineCore::ChangeLevel("WitchHouse_UpFloor");
		return;
	}


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


void Field_CenterTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{

}

void DebugTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Checkbox("On Collision", &GameEngineLevel::IsDebug); 
}