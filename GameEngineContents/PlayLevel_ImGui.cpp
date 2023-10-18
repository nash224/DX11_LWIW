#include "PreCompile.h"
#include "PlayLevel.h"


#include "BackDrop_PlayLevel.h"



void ContentsGUIWindow::Start()
{
	// µî·Ï
}

void ContentsGUIWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
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

	ImGui::SameLine();

	static float GUI_UpdateTime = 0.0f;

	GUI_UpdateTime += _DeltaTime;
	if (GUI_UpdateTime > 1.0f)
	{
		GUI_UpdateTime -= 1.0f;
		iFPS = static_cast<int>(1.0f / _DeltaTime);
	}

	ImGui::Text(std::to_string(iFPS).c_str());
}



void ContentsGUIWindow::MapEditorMode()
{

}