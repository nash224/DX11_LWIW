#include "PreCompile.h"
#include "FireWorks.h"

FireWorks::FireWorks() 
{
	GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Event");

	GameEngineSprite::CreateSingle("Pot_2.png");
	GameEngineSprite::CreateCut("FireLine.png", 5, 1);
	GameEngineSprite::CreateCut("Firewalkhalf_Pop_Light.png", 4, 3);
	GameEngineSprite::CreateCut("Fireworkhalf_Main.png", 7, 7);
	GameEngineSprite::CreateCut("Fireworkhalf_Sub_A_Light.png", 4, 3);
	GameEngineSprite::CreateCut("Fireworkhalf_Sub_B_Light.png", 4, 3);
	GameEngineSprite::CreateCut("Fireworkhalf_Sub_C_Light.png", 4, 3);
	GameEngineSprite::CreateCut("Fireworkhalf_Sub_D_Light.png", 4, 3);

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Sound\\Event\\FireWork");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile& pFile : Files)
	{
		GameEngineSound::SoundLoad(pFile.GetStringPath());
	}
}

FireWorks::~FireWorks() 
{
}


void FireWorks::Update(float _Delta)
{
	State.Update(_Delta);
}

void FireWorks::Release()
{

}

void FireWorks::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void FireWorks::Init()
{
	RendererSetting();
	StateSetting();
}

void FireWorks::RendererSetting()
{
	PotionRenderer = CreateComponent<GameEngineSpriteRenderer>();
	PotionRenderer->SetSprite("Pot_2.png");

	LightRenderer = CreateComponent<GameEngineSpriteRenderer>();
	LightRenderer->SetAutoScaleRatio(0.265f);
	LightRenderer->Transform.SetLocalPosition(float4(1.0f, -8.0f, -2.0f));
	LightRenderer->SetMaterial("2DTexture_Light");
	LightRenderer->SetSprite("Soft.png");
	LightRenderer->RenderBaseInfoValue.Target3 = 1;
	LightRenderer->Off();

	LightData.reserve(5);
	LightData.push_back(Light1);
	LightData.push_back(Light2);
	LightData.push_back(Light3);
	LightData.push_back(Light4);
	LightData.push_back(Light5);

	FxRenderer = CreateComponent<GameEngineSpriteRenderer>();
	FxRenderer->Transform.SetLocalPosition(float4(16.0f, 220.0f));
	FxRenderer->AutoSpriteSizeOn();
	FxRenderer->CreateAnimation("Pong", "Fireworkhalf_Main.png", 0.1f,0, 9, false);
	FxRenderer->CreateAnimation("Line", "FireLine.png", 0.1f, 0, 4, false);
	FxRenderer->FindAnimation("Line")->Inter[0] = 2.0f;

	FxRenderer->RenderBaseInfoValue.Target3 = 1;
	FxRenderer->Off();

	FxRenderer->SetEndEvent("Pong", [&](GameEngineSpriteRenderer* _Renderer)
		{
			State.ChangeState(ECRACKERPOTIONSTATE::FireLine);
			_Renderer->Off();
		});
}

void FireWorks::StateSetting()
{
	CreateStateParameter LightState;
	LightState.Start = std::bind(&FireWorks::StartLight, this, std::placeholders::_1);
	LightState.Stay = std::bind(&FireWorks::UpdateLight, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECRACKERPOTIONSTATE::Light, LightState);
	
	CreateStateParameter FireState;
	FireState.Start = std::bind(&FireWorks::StartFire, this, std::placeholders::_1);
	State.CreateState(ECRACKERPOTIONSTATE::Fire, FireState);

	CreateStateParameter FireState;
	FireState.Start = std::bind(&FireWorks::StartFire, this, std::placeholders::_1);
	State.CreateState(ECRACKERPOTIONSTATE::FireLine, FireState);

	State.ChangeState(ECRACKERPOTIONSTATE::Light);
}

void FireWorks::StartLight(GameEngineState* _Parent)
{
	SetLightColor(LightData[0]);
	LightRenderer->On();

	LightStateTime = 0.0f;
	ChangeCount = 0;
}

void FireWorks::StartFire(GameEngineState* _Parent)
{
	FxRenderer->ChangeAnimation("Pong");
	FxRenderer->On();

	GlobalUtils::PlaySFX("SFX_BadGrassPotion.wav");
}

void FireWorks::UpdateLight(float _Delta, GameEngineState* _Parent)
{
	LightStateTime += _Delta / ChangeLightTime;

	const int NextLightNum = ChangeCount + 1;
	LightLerp(LightData[ChangeCount], LightData[NextLightNum], LightStateTime);

	if (LightStateTime > 1.0f)
	{
		LightStateTime -= 1.0f;
		++ChangeCount;
		int DataSize = static_cast<int>(LightData.size());
		if (ChangeCount >= DataSize - 1)
		{
			SetLightColor(LightData[4]);
			State.ChangeState(ECRACKERPOTIONSTATE::Fire);
			return;
		}
	}
}

void FireWorks::StartFireLine(GameEngineState* _Parent)
{

}

void FireWorks::SetLightColor(const float4& _Color)
{
	if (nullptr == LightRenderer)
	{
		MsgBoxAssert("존재하지 않는 렌더러입니다.");
		return;
	}

	LightColor = _Color;
	LightRenderer->GetColorData().MulColor = _Color;
}

void FireWorks::LightLerp(const float4& _ColorA, const float4& _ColorB, float _Time)
{
	LightColor.R = std::lerp(_ColorA.R, _ColorB.R, _Time);
	LightColor.G = std::lerp(_ColorA.G, _ColorB.G, _Time);
	LightColor.B = std::lerp(_ColorA.B, _ColorB.B, _Time);
	LightColor.A = std::lerp(_ColorA.A, _ColorB.A, _Time);

	SetLightColor(LightColor);
}
