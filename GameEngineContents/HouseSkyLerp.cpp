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

	Items.resize(SkyPtr->SkyData.size());
	for (int i = 0; i < Items.size(); i++)
	{
		Items[i] = std::string("SkyData") + std::to_string(i);
	}

	PlotData.resize(SkyPtr->SkyData.size());
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

	ImGui::Text(std::string("Time : " + std::to_string(PlayLevel::s_TimeManager->GetTime())).c_str());
	ImGui::Text(std::string("Time : " + std::to_string(PlayLevel::s_TimeManager->GetHour())).c_str());
	ImGui::SameLine();
	ImGui::Text(std::string(": " + std::to_string(PlayLevel::s_TimeManager->GetMinute())).c_str());


	ImGui::Checkbox("Time Pause", &PlayLevel::s_TimeManager->GetPause());
	ImGui::SameLine();
	ImGui::SliderFloat("Time Ratio", &PlayLevel::s_TimeManager->GetTimeFlowRatio(), 1.0f, 10.0f, "%.0f");


	if (nullptr != SkyPtr)
	{
		ImGui::SeparatorText("SkyDebug");
		if (ImGui::ColorEdit4("Sky Color", &SkyPtr->SkyColor.R))
		{
			PlayLevel::s_TimeManager->Pause(true);
			SkyPtr->SetDebugSkyColor(SkyPtr->SkyColor);
		}

		ImGui::Checkbox("Pause Update", &SkyPtr->PauseSkyLerp);

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

		ImGui::Spacing();

		char NumString[] = {'R', 'G', 'B', 'A'};
		for (int RGBA = 0; RGBA < 4; RGBA++)
		{
			for (int i = 0; i < SkyPtr->SkyData.size(); i++)
			{
				float Value;
				switch (RGBA)
				{
				case 0:
					Value = SkyPtr->SkyData[i].R;
					break;
				case 1:
					Value = SkyPtr->SkyData[i].G;
					break;
				case 2:
					Value = SkyPtr->SkyData[i].B;
					break;
				case 3:
					Value = SkyPtr->SkyData[i].A;
					break;
				default:
					break;
				}

				PlotData[i] = Value;
			}

			std::string PlotName = std::string("Frame Color ") + NumString[RGBA];
			ImGui::PlotLines(PlotName.c_str(), PlotData.data(), static_cast<int>(PlotData.size()));
		}


		ImGui::Spacing();

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

		ImGui::SameLine();

		if (ImGui::Button("Load"))
		{
			SkyPtr->LoadData();
		}
	}

}


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

void HouseSkyLerp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	if (nullptr != SkyGUIWindow)
	{
		SkyGUIWindow->Off();
	}
}

void HouseSkyLerp::SetSkyData()
{
	LoadData();
}

void HouseSkyLerp::LoadData()
{
	GameEngineSerializer LoadBin;
	GameEngineFile File;
	File.MoveParentToExistsChild("Resources");
	File.MoveChild("Resources\\Data\\Sky\\SkyData.sky");
	File.Open(FileOpenType::Read, FileDataType::Binary);
	File.DataAllRead(LoadBin);

	unsigned int Size;
	LoadBin >> Size;

	SkyData.resize(Size);
	for (unsigned int i = 0; i < Size; i++)
	{
		float4 Color;
		LoadBin.Read(&Color, sizeof(Color));
		SkyData[i] = Color;
	}
}