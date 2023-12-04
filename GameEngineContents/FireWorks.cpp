#include "PreCompile.h"
#include "FireWorks.h"

#include "CameraControler.h"


static constexpr int MaxPopCount = 6;

#define Light1 {0.0f, 0.0f, 0.0f, 0.0f} 
#define Light2 {0.25f, 0.28f, 0.156f, 1.0f} 
#define Light3 {0.1f, 0.25f, 0.17f, 0.58f} 
#define Light4 {0.68f, 1.0f, 0.56f, 1.0f} 
#define Light5 {0.31f, 0.29f, 0.56f, 0.67f} 


FireWorks::FireWorks() 
{
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Event");

	GameEngineSprite::CreateSingle("Pot_2.png");
	GameEngineSprite::CreateCut("FireLine.png", 5, 1);
	GameEngineSprite::CreateCut("DisappearRay.png", 4, 1);
	GameEngineSprite::CreateCut("Firewalkhalf_Pop_Light.png", 4, 3);
	GameEngineSprite::CreateCut("Fireworkhalf_Main.png", 7, 7);
	GameEngineSprite::CreateCut("Fireworkhalf_Sub_A.png", 4, 4);
	GameEngineSprite::CreateCut("Fireworkhalf_Sub_B.png", 4, 4);
	GameEngineSprite::CreateCut("Fireworkhalf_Sub_C.png", 4, 4);
	GameEngineSprite::CreateCut("Fireworkhalf_Sub_D.png", 4, 4);
	GameEngineSprite::CreateCut("WitchLock_Twinkle.png", 3, 2);

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
	PotionRenderer = nullptr;
	LightRenderer = nullptr;
	FxRenderer = nullptr;
	Crackers.clear();
	LightData.clear();

	GameEngineSprite::Release("Pot_2.png");
	GameEngineSprite::Release("FireLine.png");
	GameEngineSprite::Release("DisappearRay.png");
	GameEngineSprite::Release("Firewalkhalf_Pop_Light.png");
	GameEngineSprite::Release("Fireworkhalf_Main.png");
	GameEngineSprite::Release("Fireworkhalf_Sub_A.png");
	GameEngineSprite::Release("Fireworkhalf_Sub_B.png");
	GameEngineSprite::Release("Fireworkhalf_Sub_C.png");
	GameEngineSprite::Release("Fireworkhalf_Sub_D.png");

	FileLoadFunction::ReleaseAllTextureInPath("Resources\\PlayContents\\PlayResourecs\\Event");
}

void FireWorks::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}



void FireWorks::Init()
{
	RendererSetting();
	StateSetting();
	RayLightStateInfo.StateSetting();
	CrackersSetting();
}

void FireWorks::Fire()
{
	State.ChangeState(ECRACKERPOTIONSTATE::Light);
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
	FxRenderer->CreateAnimation("Pong", "Fireworkhalf_Main.png", 0.09f,0, 9, false);
	FxRenderer->CreateAnimation("Ray", "FireLine.png", 0.1f, 0, 4, false);
	FxRenderer->FindAnimation("Ray")->Inter[0] = 1.4f;
	FxRenderer->CreateAnimation("DisappearRay", "DisappearRay.png", 0.025f, 0, 3, false);
	
	FxRenderer->RenderBaseInfoValue.Target3 = 1;
	FxRenderer->Off();

	FxRenderer->SetEndEvent("Pong", [&](GameEngineSpriteRenderer* _Renderer)
		{
			State.ChangeState(ECRACKERPOTIONSTATE::FocusRayLight);
			_Renderer->Off();
		});

	FxRenderer->SetStartEvent("Ray", [](GameEngineSpriteRenderer* _Renderer)
		{
			const float4& TexScale = _Renderer->GetCurSprite().Texture->GetScale();

			_Renderer->Transform.SetLocalPosition(float4(0.0f, 120.0f + TexScale.Half().Y));
		});

	FxRenderer->SetEndEvent("Ray", [](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("DisappearRay");
		});

	FxRenderer->SetStartEvent("DisappearRay", [](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->Transform.SetLocalPosition(float4(0.0f, 1880.0f));
		});

	FxRenderer->SetEndEvent("DisappearRay", [&](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->Off();
			State.ChangeState(ECRACKERPOTIONSTATE::PopCrackers);
		});
}

void FireWorks::CrackersSetting()
{
	const float4& CenterPopPos = float4(22.0f, 2000.0f);

	float4 CrackerPosArr[MaxPopCount] =
	{
		CenterPopPos,
		CenterPopPos + float4(-250.0f, 30.0f),
		CenterPopPos + float4(80.0f, -150.0f),
		CenterPopPos + float4(-50.0f, 120.0f),
		CenterPopPos + float4(240.0f, 200.0f),
		CenterPopPos + float4(-140.0f, 60.0f),
	};

	float NextPopTimeArr[MaxPopCount] = { 0.1f, 2.1f, 1.03f, 0.23f, 0.92f, 0.75f };

	Crackers.resize(MaxPopCount);
	for (int i = 0; i < MaxPopCount; i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> PopCracker = CreateComponent<GameEngineSpriteRenderer>();
		PopCracker->Transform.SetLocalPosition(CrackerPosArr[i]);
		PopCracker->AutoSpriteSizeOn();
		PopCracker->RenderBaseInfoValue.Target3 = 1;
		PopCracker->Off();
		Crackers[i].PopRenderer = PopCracker;
		Crackers[i].NextPopTime = NextPopTimeArr[i];
	}

	static constexpr float PopInter = 0.1f;

	Crackers[0].PopRenderer->CreateAnimation("Pop", "Fireworkhalf_Main.png", PopInter, 33, 48, false);
	Crackers[1].PopRenderer->CreateAnimation("Pop", "Fireworkhalf_Sub_A.png", PopInter, -1, -1, false);
	Crackers[2].PopRenderer->CreateAnimation("Pop", "Fireworkhalf_Sub_C.png", PopInter, -1, -1, false);
	Crackers[3].PopRenderer->CreateAnimation("Pop", "Fireworkhalf_Sub_D.png", PopInter, -1, -1, false);
	Crackers[4].PopRenderer->CreateAnimation("Pop", "Fireworkhalf_Sub_B.png", PopInter, -1, -1, false);
	Crackers[5].PopRenderer->CreateAnimation("Pop", "Fireworkhalf_Sub_C.png", PopInter, -1, -1, false);
	Crackers[5].PopRenderer->SetAutoScaleRatio(0.5f);

	for (int i = 0; i < MaxPopCount - 1; i++)
	{
		Crackers[i].PopRenderer->ChangeAnimation("Pop");
		Crackers[i].PopRenderer->SetEndEvent("Pop", [](GameEngineSpriteRenderer* _Renderer)
			{
				_Renderer->Off();
			});
	}

	const int LastCrackerCount = MaxPopCount - 1;
	Crackers[LastCrackerCount].PopRenderer->ChangeAnimation("Pop");
	Crackers[LastCrackerCount].PopRenderer->SetEndEvent("Pop", [&](GameEngineSpriteRenderer* _Renderer)
		{
			State.ChangeState(ECRACKERPOTIONSTATE::Done);
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

	CreateStateParameter FocusRayLightState;
	FocusRayLightState.Start = std::bind(&FireWorks::StartFocusRayLight, this, std::placeholders::_1);
	FocusRayLightState.Stay = std::bind(&FireWorks::UpdateFocusRayLight, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECRACKERPOTIONSTATE::FocusRayLight, FocusRayLightState);

	CreateStateParameter WaitState;
	WaitState.Stay = std::bind(&FireWorks::UpdateWait, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECRACKERPOTIONSTATE::Wait, WaitState);

	CreateStateParameter PopCrackersState;
	PopCrackersState.Stay = std::bind(&FireWorks::UpdatePopCrackers, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECRACKERPOTIONSTATE::PopCrackers, PopCrackersState);

	CreateStateParameter DoneState;
	DoneState.Start = std::bind(&FireWorks::StartDone, this, std::placeholders::_1);
	State.CreateState(ECRACKERPOTIONSTATE::Done, DoneState);
}

void FireWorks::StartLight(GameEngineState* _Parent)
{
	SetLightColor(LightData[0]);
	LightRenderer->On();

	LightStateTime = 0.0f;
	LightTransitionCount = 0;
}

void FireWorks::UpdateLight(float _Delta, GameEngineState* _Parent)
{
	const float ChangeLightTime = 0.25f;
	LightStateTime += _Delta / ChangeLightTime;

	const int NextLightNum = LightTransitionCount + 1;
	LightLerp(LightData[LightTransitionCount], LightData[NextLightNum], LightStateTime);

	if (LightStateTime > 1.0f)
	{
		LightStateTime -= 1.0f;
		++LightTransitionCount;
		int DataSize = static_cast<int>(LightData.size());
		if (LightTransitionCount >= DataSize - 1)
		{
			SetLightColor(LightData[4]);
			State.ChangeState(ECRACKERPOTIONSTATE::Fire);
			return;
		}
	}
}

void FireWorks::StartFire(GameEngineState* _Parent)
{
	FxRenderer->ChangeAnimation("Pong");
	FxRenderer->On();

	SFXFunction::PlaySFX("SFX_BadGrassPotion.wav");
}

void FireWorks::StartFocusRayLight(GameEngineState* _Parent)
{
	RayLightStateInfo.Parent = this;
	RayLightStateInfo.State.ChangeState(FireWorks::RayLightState::EFIRELINESTATE::Ready);

	PlayLevel::GetCurLevel();
	PlayLevel::GetCurLevel()->GetLevelCameraPtr()->SetCameraMode(ECAMERAMODE::Cinematic);

	const float4& CameraPos = PlayLevel::GetCurLevel()->GetLevelCameraPtr()->GetCameraCurrentPostion();
	LimitCameraPos = CameraPos + float4(0.0f, TargetDistance);

	SFXFunction::PlaySFX("SFX_Firework.wav");
}


void FireWorks::UpdateFocusRayLight(float _Delta, GameEngineState* _Parent)
{
	const std::shared_ptr<CameraControler>& CurCameraPtr = PlayLevel::GetCurLevel()->GetLevelCameraPtr();

	RayLightStateInfo.State.Update(_Delta);

	const float TargetTime = 1.8f;
	const float CameraMoveForce = TargetDistance* _Delta / TargetTime;
	CurCameraPtr->AddCameraPos(float4(0.0f, CameraMoveForce));

	const float4& CameraPos = CurCameraPtr->GetCameraCurrentPostion();
	if (CameraPos.Y > LimitCameraPos.Y)
	{
		CurCameraPtr->SetCameraPos(LimitCameraPos);
		State.ChangeState(ECRACKERPOTIONSTATE::Wait);
		return;
	}
}

void FireWorks::UpdateWait(float _Delta, GameEngineState* _Parent)
{
	RayLightStateInfo.State.Update(_Delta);
}

void FireWorks::UpdatePopCrackers(float _Delta, GameEngineState* _Parent)
{
	const float NextPopTime = Crackers[CurPopCount].NextPopTime;

	PopRemainTime += _Delta;
	if (PopRemainTime > NextPopTime)
	{
		PopRemainTime -= NextPopTime;

		Crackers[CurPopCount].PopRenderer->On();

		++CurPopCount;
		if (CurPopCount >= MaxPopCount)
		{
			State.ChangeState(ECRACKERPOTIONSTATE::Done);
			return;
		}
	}
}

void FireWorks::StartDone(GameEngineState* _Parent)
{
	isFireWorkEnd = true;
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


void FireWorks::RayLightState::StateSetting()
{
	CreateStateParameter ReadyState;
	ReadyState.Start = std::bind(&FireWorks::RayLightState::StartReady, this, std::placeholders::_1);
	ReadyState.Stay = std::bind(&FireWorks::RayLightState::UpdateReady, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EFIRELINESTATE::Ready, ReadyState);

	CreateStateParameter RayState;
	RayState.Start = std::bind(&FireWorks::RayLightState::StartRay, this, std::placeholders::_1);
	State.CreateState(EFIRELINESTATE::Ray, RayState);
}


void FireWorks::RayLightState::StartReady(GameEngineState* _Parent)
{
	if (nullptr == Parent || nullptr == Parent->FxRenderer)
	{
		MsgBoxAssert("nullpointer를 참조하려 했습니다.");
		return;
	}
	
	Parent->FxRenderer->Off();
}

void FireWorks::RayLightState::UpdateReady(float _Delta, GameEngineState* _Parent)
{
	const float ReadyTime = 0.1f;
	if (_Parent->GetStateTime() > ReadyTime)
	{
		State.ChangeState(EFIRELINESTATE::Ray);
		return;
	}
}

void FireWorks::RayLightState::StartRay(GameEngineState* _Parent)
{
	if (nullptr == Parent || nullptr == Parent->FxRenderer)
	{
		MsgBoxAssert("nullpointer를 참조하려 했습니다.");
		return;
	}

	Parent->FxRenderer->ChangeAnimation("Ray");
	Parent->FxRenderer->On();
}