#include "PreCompile.h"
#include "LoadingLevel.h"

#include "GlobalUtils.h"

#include "BackDrop_Loading.h"

#include "CameraControler.h"
#include "BiologyData.h"
#include "IngredientData.h"
#include "ItemData.h"
#include "ProductRecipeData.h"



LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}


void LoadingLevel::Start()
{
	ContentsLevel::Start();

	if (nullptr == m_LevelCameraControler)
	{
		MsgBoxAssert("존재하지 않는 액터를 사용하려고 했습니다.");
		return;
	}

	m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Play);
}

void LoadingLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	if (true == GameEngineInput::IsPress('T', this))
	{
		GameEngineCore::ChangeLevel("WitchHouse_Yard");
	}
}

void LoadingLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	LoadSprite();
	LoadActor();

	if (nullptr == GlobalValue::g_CameraControler)
	{
		MsgBoxAssert("카메라를 생성하지 않고 설정할 수 없습니다.");
		return;
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 않았습니다.");
		return;
	}

	float4 CameraPos = m_BackDrop->GetBackGroundScale();
	CameraPos = CameraPos.Half();
	CameraPos.Y *= -1.0f;
	GlobalValue::g_CameraControler->SetLocalPostion(CameraPos);
	
}

void LoadingLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);

	ReleaseSprite();
	ReleaseTexture();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void LoadingLevel::LoadSprite()
{
	GameEngineSprite::CreateSingle("Loading_Back.png");
}

void LoadingLevel::LoadActor()
{
	m_BackDrop = CreateActor<BackDrop_Loading>(EUPDATEORDER::Objects);
	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_BackDrop->Init();
}

void LoadingLevel::ReleaseSprite()
{
	// LoadingLevel Resources
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\LoadingLevel");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineSprite::Release(File.GetFileName());
	}
}

void LoadingLevel::ReleaseTexture()
{
	GlobalUtils::ReleaseAllTextureInPath("Resources\\LoadingLevel");
}