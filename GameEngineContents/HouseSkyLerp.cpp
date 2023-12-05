#include "PreCompile.h"
#include "HouseSkyLerp.h"

#include "TimeManager.h"


void SkyGUI::GUIStart()
{
	if (nullptr == SkyPtr)
	{
		MsgBoxAssert("부모를 지정해주지 않았습니다.");
		return;
	}

	Items.resize(static_cast<int>(SkyPtr->SkyData.size()));
	for (int i = 0; i < Items.size(); i++)
	{
		Items[i] = std::string("SkyData") + std::to_string(i);
	}
}

void SkyGUI::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	if (nullptr == SkyPtr) 
	{
		return;
	}

	ImGui::SeparatorText("TimeDebug");
	if (ImGui::SliderFloat("TimeCustom", &PlayLevel::s_TimeManager->GetTimePointer(), 0.0f, PlayLevel::s_TimeManager->GetMaxTime(), "%.0f"))
	{
		PlayLevel::s_TimeManager->Pause(true);
		PlayLevel::s_TimeManager->SetTime(PlayLevel::s_TimeManager->GetTime());
	}


	if (nullptr != SkyPtr)
	{
		ImGui::SeparatorText("SkyDebug");
		if (ImGui::ColorEdit4("Sky Color", &SkyPtr->SkyColor.R))
		{
			SkyPtr->SetSkyColor();
		}

		if (ImGui::BeginCombo("Sky Combo", Items.at(Curidx).c_str()))
		{
			for (int n = 0; n < Items.size(); n++)
			{
				const bool isSelected = (Curidx == n);
				if (ImGui::Selectable(Items[n].c_str(), isSelected))
				{
					Curidx = n;
				}

				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::Text(Items.at(Curidx).c_str());
		ImGui::Text(SkyPtr->SkyData.at(Curidx).ToString().c_str());

		if (ImGui::Button("Save Current SkyColor"))
		{
			SkyPtr->SkyData.at(Curidx) = SkyPtr->SkyColor;
		}

		if (ImGui::Button("Save"))
		{
			GameEngineSerializer BinSerial;
			BinSerial << static_cast<unsigned int>(SkyPtr->SkyData.size());
			for (const float4& Color : SkyPtr->SkyData)
			{
				BinSerial << Color;
			}

			GameEngineFile File;
			File.MoveParentToExistsChild("Resources");
			File.MoveChild("Resources\\Data\\Sky");
			std::string Path = File.GetStringPath();
			Path += "\\SkyData.sky";
			File = Path;
			File.Open(FileOpenType::Write, FileDataType::Binary);
			File.Write(BinSerial);
		}
	}

}


#define Sky_300 { 0.6f, 0.8f, 0.0f, 0.1f }
#define Sky_310 { 0.65f, 0.7f, 0.0f, 0.11f }
#define Sky_320 { 0.7f, 0.6f, 0.0f, 0.12f }
#define Sky_330 { 0.75f, 0.5f, 0.0f, 0.13f }
#define Sky_340 { 0.8f, 0.4f, 0.0f, 0.14f }
#define Sky_350 { 0.8f, 0.34f, 0.0f, 0.15f }
#define Sky_400 { 0.8f, 0.3f, 0.0f, 0.16f }
#define Sky_410 { 0.85f, 0.26f, 0.0f, 0.18f }
#define Sky_420 { 0.9f, 0.21f, 0.0f, 0.19f }
#define Sky_430 { 0.95f, 0.15f, 0.0f, 0.2f }
#define Sky_440 { 0.95f, 0.11f, 0.0f, 0.21f }
#define Sky_450 { 0.95f, 0.08f, 0.0f, 0.23f }
#define Sky_500 { 0.94f, 0.04f, 0.0f, 0.24f }
#define Sky_510 { 0.91f, 0.02f, 0.0f, 0.25f }
#define Sky_520 { 0.91f, 0.01f, 0.0f, 0.26f }
#define Sky_530 { 0.91f, 0.0f, 0.0f, 0.27f }
#define Sky_540 { 0.91f, 0.0f, 0.0f, 0.28f }
#define Sky_550 { 0.88f, 0.0f, 0.01f, 0.3f }
#define Sky_600 { 0.82f, 0.0f, 0.02f, 0.32f }
#define Sky_610 { 0.74f, 0.0f, 0.03f, 0.35f }
#define Sky_620 { 0.62f, 0.0f, 0.05f, 0.38f }
#define Sky_630 { 0.5f, 0.0f, 0.06f, 0.42f }
#define Sky_640 { 0.4f, 0.0f, 0.07f, 0.46f }
#define Sky_650 { 0.3f, 0.0f, 0.08f, 0.5f }
#define Sky_700 { 0.2f, 0.0f, 0.09f, 0.54f }
#define Sky_710 { 0.1f, 0.0f, 0.1f, 0.58f }
#define Sky_720 { 0.03f, 0.0f, 0.12f, 0.62f } 
#define Sky_730 { 0.02f, 0.0f, 0.15f, 0.66f }
#define Sky_740 { 0.0f, 0.0f, 0.18f, 0.7f }

HouseSkyLerp::HouseSkyLerp() 
{
}

HouseSkyLerp::~HouseSkyLerp() 
{
}


void HouseSkyLerp::Start()
{
	SkyLerp::Start();

	GameEngineInput::AddInputObject(this);
	SkyGUIWindow = GameEngineGUI::CreateGUIWindow<SkyGUI>("SkyGUI");
	SkyGUIWindow->SkyPtr = this;
	SkyGUIWindow->GUIStart();
	SkyGUIWindow->Off();
}

void HouseSkyLerp::Update(float _Delta)
{
	SkyLerp::Update(_Delta);
	if (true == GameEngineInput::IsDown(VK_F8, this))
	{
		if (true == SkyGUIWindow->IsUpdate())
		{
			SkyGUIWindow->Off();
		}
		else
		{
			SkyGUIWindow->On();
		}
	}
}

void HouseSkyLerp::Release()
{
	SkyLerp::Release();

	SkyGUIWindow = nullptr;
}

void HouseSkyLerp::LevelStart(class GameEngineLevel* _NextLevel)
{
	On();
}

void HouseSkyLerp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	if (nullptr != SkyGUIWindow)
	{
		SkyGUIWindow->Off();
	}

	Off();
}

void HouseSkyLerp::SetSkyData()
{
	SkyData.reserve(32);
	SkyData.push_back(Sky_300);
	SkyData.push_back(Sky_310);
	SkyData.push_back(Sky_320);
	SkyData.push_back(Sky_330);
	SkyData.push_back(Sky_340);
	SkyData.push_back(Sky_350);
	SkyData.push_back(Sky_400);
	SkyData.push_back(Sky_410);
	SkyData.push_back(Sky_420);
	SkyData.push_back(Sky_430);
	SkyData.push_back(Sky_440);
	SkyData.push_back(Sky_450);
	SkyData.push_back(Sky_500);
	SkyData.push_back(Sky_510);
	SkyData.push_back(Sky_520);
	SkyData.push_back(Sky_530);
	SkyData.push_back(Sky_540);
	SkyData.push_back(Sky_550);
	SkyData.push_back(Sky_600);
	SkyData.push_back(Sky_610);
	SkyData.push_back(Sky_620);
	SkyData.push_back(Sky_630);
	SkyData.push_back(Sky_640);
	SkyData.push_back(Sky_650);
	SkyData.push_back(Sky_700);
	SkyData.push_back(Sky_710);
	SkyData.push_back(Sky_720);
	SkyData.push_back(Sky_730);
	SkyData.push_back(Sky_740);
}