#include "PreCompile.h"
#include "PlayLevel.h"

#include "GlobalUtils.h"


#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"
#include "Ellie.h"
#include "UIManager.h"


void PlayGUIWindow::Start()
{

}

void PlayGUIWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
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

	if (ImGui::SliderFloat("Slider", &SliderAmount, 0.0f, 100.0f, "%.2f"))
	{

	}



	static float GUI_UpdateTime = 0.0f;

	GUI_UpdateTime += _DeltaTime;
	if (GUI_UpdateTime > 1.0f)
	{
		GUI_UpdateTime -= 1.0f;
		iFPS = static_cast<int>(1.0f / _DeltaTime);
	}

	ImGui::Text(std::to_string(iFPS).c_str());
}

bool PlayLevel::PixelDebugMode = false;
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	GameEngineGUI::CreateGUIWindow<PlayGUIWindow>("PlayLevel");

	ContentsLevel::Start();
}

void PlayLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	// ����� ��ȯ
	ChangeDebugMode();
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	if (false == LevelInitCheck)
	{
		CreateEllie();			// �÷��̾� ����
		CreateUIManager();		// UI ����
	}

	LevelInitCheck = true;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// UI
void PlayLevel::CreateUIManager()
{
	m_UIManager = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	if (nullptr == m_UIManager)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_UIManager->Init();
}

// �÷��̾� 
void PlayLevel::CreateEllie()
{
	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_Ellie->Init();
}

// ����� ��� ��ȯ
void PlayLevel::ChangeDebugMode()
{
	if (true == IsDebug)
	{
		if (true == GameEngineInput::IsDown(VK_F2, this))
		{
			PixelDebugMode = !PixelDebugMode;
			if (nullptr == BackDrop_PlayLevel::MainBackDrop)
			{
				MsgBoxAssert("�۷ι� ���Ͱ� �������� �ʽ��ϴ�.");
				return;
			}

			BackDrop_PlayLevel::MainBackDrop->EnableDebugMode(PixelDebugMode);
		}
	}
	else
	{
		if (true == PixelDebugMode)
		{
			PixelDebugMode = false;

			if (nullptr == BackDrop_PlayLevel::MainBackDrop)
			{
				MsgBoxAssert("�۷ι� ���Ͱ� �������� �ʽ��ϴ�.");
				return;
			}
			BackDrop_PlayLevel::MainBackDrop->EnableDebugMode(PixelDebugMode);
		}
	}
}