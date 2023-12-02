#include "PreCompile.h"
#include "Ellie.h"

#include "EffectEnum.h"



void Ellie::RendererSetting()
{
	const float ShadowDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::ObjectShadow);


	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>();
	EllieFxRenderer = CreateComponent<GameEngineSpriteRenderer>();
	VirgilRenderer = CreateComponent<GameEngineSpriteRenderer>();

	VirgilRenderer->RenderBaseInfoValue.Target3 = 1;

	
	BodyRenderer->Transform.SetLocalPosition(float4(0.0f, LWIW_Ellie_Y_Correction));
	ShadowRenderer->Transform.SetLocalPosition(float4(0.0f, LWIW_Ellie_Y_Correction, ShadowDepth));
	EllieFxRenderer->Transform.SetLocalPosition(float4(0.0f, LWIW_Ellie_Y_Correction, -0.3f));
	VirgilRenderer->Transform.SetLocalPosition(float4(0.0f, LWIW_Ellie_Y_Correction, -0.2f));

	BodyRenderer->AutoSpriteSizeOn();

	EllieFxRenderer->Off();

#pragma region 기본 조작

	static constexpr float EllieIdleInter = 0.2f;
	static constexpr float Ellie_SlowWalk_Inter = 0.2f;
	static constexpr float Ellie_Run_Inter = 0.1f;
	static constexpr float Ellie_Throw_Inter = 0.1f;
	static constexpr float Ellie_Riding_Idle_Inter = 0.1f;
	static constexpr float Ellie_Riding_Move_Inter = 0.1f;
	static constexpr float Ellie_Riding_Boost_Inter = 0.1f;
	static constexpr float Ellie_ButterflyNet_Inter = 0.1f;
	static constexpr float Ellie_RootUp_Inter = 0.12f;
	static constexpr float Ellie_Sit_Inter = 0.12f;
	static constexpr float Ellie_MongSiri_Inter = 0.2f;


	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Idle_LEFT", "Ellie_Basic_Idle.png", EllieIdleInter, 4, 7);
		BodyRenderer->CreateAnimation("Ellie_Basic_Idle_LEFTDOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 4, 7);
		BodyRenderer->CreateAnimation("Ellie_Basic_Idle_DOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 8, 11);
		BodyRenderer->CreateAnimation("Ellie_Basic_Idle_RIGHT", "Ellie_Basic_Idle.png", EllieIdleInter, 12, 15);
		BodyRenderer->CreateAnimation("Ellie_Basic_Idle_RIGHTDOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 12, 15);
		BodyRenderer->CreateAnimation("Ellie_Basic_Idle_LEFTUP", "Ellie_Basic_Idle.png", EllieIdleInter, 16, 19);
		BodyRenderer->CreateAnimation("Ellie_Basic_Idle_UP", "Ellie_Basic_Idle.png", EllieIdleInter, 20, 23);
		BodyRenderer->CreateAnimation("Ellie_Basic_Idle_RIGHTUP", "Ellie_Basic_Idle.png", EllieIdleInter, 24, 27);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Idle_LEFT", { 28,29,29,30 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Idle_LEFTDOWN", { 28,29,29,30 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Idle_DOWN", { 31,32,33,34 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Idle_RIGHT", { 35,36,36,37 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Idle_RIGHTDOWN", { 35,36,36,37 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Idle_LEFTUP", { 38,39,39,38 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Idle_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Idle_RIGHTUP", { 40,41,41,40 });

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Walk_LEFT", "Ellie_Basic_Walk.png", 0.1f, 34, 41);
		BodyRenderer->CreateAnimation("Ellie_Basic_Walk_LEFTDOWN", "Ellie_Basic_Walk.png", 0.1f, 34, 41);
		BodyRenderer->CreateAnimation("Ellie_Basic_Walk_DOWN", "Ellie_Basic_Walk.png", 0.1f, 42, 49);
		BodyRenderer->CreateAnimation("Ellie_Basic_Walk_RIGHT", "Ellie_Basic_Walk.png", 0.1f, 54, 61);
		BodyRenderer->CreateAnimation("Ellie_Basic_Walk_RIGHTDOWN", "Ellie_Basic_Walk.png", 0.1f, 54, 61);
		BodyRenderer->CreateAnimation("Ellie_Basic_Walk_LEFTUP", "Ellie_Basic_Walk.png", 0.1f, 66, 73);
		BodyRenderer->CreateAnimation("Ellie_Basic_Walk_UP", "Ellie_Basic_Walk.png", 0.1f, 78, 85);
		BodyRenderer->CreateAnimation("Ellie_Basic_Walk_RIGHTUP", "Ellie_Basic_Walk.png", 0.1f, 91, 98);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Walk_LEFT", { 108,99,100,101,108,109,100,100 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Walk_LEFTDOWN", { 108,99,100,101,108,109,100,100 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Walk_DOWN", { 110,111,0,0,110,111,0,0 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Walk_RIGHT", { 115,116,117, 117,115,116,117,117 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Walk_RIGHTDOWN", { 115,116,117, 117,115,116,117,117 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Walk_LEFTUP", { 120,121,119,119,120,121,121,121 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Walk_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Walk_RIGHTUP", { 126,127,127,128,126,127,128,128 });

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_SlowWalk_LEFT", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 34, 41);
		BodyRenderer->CreateAnimation("Ellie_Basic_SlowWalk_LEFTDOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 34, 41);
		BodyRenderer->CreateAnimation("Ellie_Basic_SlowWalk_DOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 42, 49);
		BodyRenderer->CreateAnimation("Ellie_Basic_SlowWalk_RIGHT", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 54, 61);
		BodyRenderer->CreateAnimation("Ellie_Basic_SlowWalk_RIGHTDOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 54, 61);
		BodyRenderer->CreateAnimation("Ellie_Basic_SlowWalk_LEFTUP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 66, 73);
		BodyRenderer->CreateAnimation("Ellie_Basic_SlowWalk_UP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 78, 85);
		BodyRenderer->CreateAnimation("Ellie_Basic_SlowWalk_RIGHTUP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 91, 98);
	}


	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_SlowWalk_LEFT", { 108,99,100,101,108,109,100,100 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_SlowWalk_LEFTDOWN", { 108,99,100,101,108,109,100,100 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_SlowWalk_DOWN", { 110,111,0,0,110,111,0,0 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_SlowWalk_RIGHT", { 115,116,117, 117,115,116,117,117 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_SlowWalk_RIGHTDOWN", { 115,116,117, 117,115,116,117,117 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_SlowWalk_LEFTUP", { 120,121,119,119,120,121,121,121 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_SlowWalk_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_SlowWalk_RIGHTUP", { 126,127,127,128,126,127,128,128 });

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Run_LEFT", "Ellie_Basic_Run.png", Ellie_Run_Inter, 4, 9);
		BodyRenderer->CreateAnimation("Ellie_Basic_Run_LEFTDOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 4, 9);
		BodyRenderer->CreateAnimation("Ellie_Basic_Run_DOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 10, 15);
		BodyRenderer->CreateAnimation("Ellie_Basic_Run_RIGHT", "Ellie_Basic_Run.png", Ellie_Run_Inter, 17, 22);
		BodyRenderer->CreateAnimation("Ellie_Basic_Run_RIGHTDOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 17, 22);
		BodyRenderer->CreateAnimation("Ellie_Basic_Run_LEFTUP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 23, 28);
		BodyRenderer->CreateAnimation("Ellie_Basic_Run_UP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 30, 35);
		BodyRenderer->CreateAnimation("Ellie_Basic_Run_RIGHTUP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 36, 41);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Run_LEFT", { 42,43,44,42,45,46 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Run_LEFTDOWN", { 42,43,44,42,45,46 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Run_DOWN", { 47,48,48,47,49,49 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Run_RIGHT", { 51,52,53,51,54,55 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Run_RIGHTDOWN", { 51,52,53,51,54,55 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Run_LEFTUP", { 56,57,58,59,60,61 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Run_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Run_RIGHTUP", { 62,63,64,65,66,67 });

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Throw_LEFT", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 4, 8);
		BodyRenderer->CreateAnimation("Ellie_Basic_Throw_LEFTDOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 4, 8);
		BodyRenderer->CreateAnimation("Ellie_Basic_Throw_DOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 9, 13);
		BodyRenderer->CreateAnimation("Ellie_Basic_Throw_RIGHT", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 15, 19);
		BodyRenderer->CreateAnimation("Ellie_Basic_Throw_RIGHTDOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 15, 19);
		BodyRenderer->CreateAnimation("Ellie_Basic_Throw_LEFTUP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 20, 24);
		BodyRenderer->CreateAnimation("Ellie_Basic_Throw_UP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 25, 29);
		BodyRenderer->CreateAnimation("Ellie_Basic_Throw_RIGHTUP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 31, 35);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Throw_LEFT", { 36,37,38,39,39 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Throw_LEFTDOWN", { 36,37,38,39,39 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Throw_DOWN", { 40,0,41,42,42 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Throw_RIGHT", { 43,44,45,46,46 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Throw_RIGHTDOWN", { 43,44,45,46,46 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Throw_LEFTUP", { 47,48,49,50,50 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Throw_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Throw_RIGHTUP", {51,52,53,54,54});

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Standing_LEFT", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 3, 6);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Standing_LEFTDOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 7, 10);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Standing_DOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 11, 14);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Standing_RIGHTDOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 15, 18);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Standing_RIGHT", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 19, 22);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Standing_LEFTUP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 31, 34);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Standing_UP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 27, 30);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Standing_RIGHTUP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 23, 26);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFT", { 35,36,36,37 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFTDOWN", { 38,39,39,38 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_DOWN", { 40,41,41,42 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHT", { 45,46,46,45 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHTDOWN", { 43,44,44,43 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFTUP", { 47,48,48,47 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHTUP", { 49,50,50,49 });

	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFT", { 2,1,1,2 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFTDOWN", { 4,3,3,4 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_DOWN", { 6,5,5,6 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHT", { 8,7,7,8 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHTDOWN", { 10,9,9,10 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFTUP", { 12,11,11,12 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_UP", { 14,13,13,14 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHTUP", { 16,15,15,16 });

	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFT", { 18,17,17,18 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFTDOWN", { 20,19,19,20 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_DOWN", { 22,21,21,22 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHT", { 24,23,23,24 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHTDOWN", { 26,25,25,26 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_LEFTUP", { 28,27,27,28 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_UP", { 30,29,29,30 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Standing_RIGHTUP", { 32,31,31,32 });

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Moving_LEFT", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 3, 6);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Moving_LEFTDOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 7, 10);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Moving_DOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 11, 14);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Moving_RIGHTDOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 19,22);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Moving_RIGHT", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 15, 18);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Moving_LEFTUP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 23, 26);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Moving_UP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 27, 30);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Moving_RIGHTUP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 31, 34);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFT", { 35,35,36,37 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFTDOWN", { 38,38,39,39 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_DOWN", { 40,40,41,41 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHT", { 42,42,43,44 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHTDOWN", { 45,45,46,46 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFTUP", { 47,47,48,48 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHTUP", { 49,49,50,50 });

	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFT", { 1,1,2,2 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFTDOWN", { 3,3,4,4 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_DOWN", { 5,5,6,6 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHT", { 7,7,8,8 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHTDOWN", { 9,9,10,10 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFTUP", { 11,11,12,12 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_UP", { 13,13,14,14 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHTUP", { 15,15,16,16 });

	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFT", { 17,17,18,18 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFTDOWN", { 19,19,20,20 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_DOWN", { 21,21,22,22 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHT", { 23,23,24,24 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHTDOWN", { 25,25,26,26 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_LEFTUP", { 27,27,28,28 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_UP", { 29,29,30,30 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Moving_RIGHTUP", { 31,31,32,32 });

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Boosting_LEFT", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 3, 6);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Boosting_LEFTDOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 7, 10);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Boosting_DOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 11, 14);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Boosting_RIGHTDOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 19, 22);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Boosting_RIGHT", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 15, 18);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Boosting_LEFTUP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 23, 26);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Boosting_UP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 27, 30);
		BodyRenderer->CreateAnimation("Ellie_Basic_Riding_Boosting_RIGHTUP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 31, 34);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFT", { 35,35,36,36 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFTDOWN", { 38,38,39,39 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_DOWN", { 40,40,41,41 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHT", { 42,42,43,43});
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHTDOWN", { 45,45,46,46 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFTUP", { 47,47,48,48 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHTUP", { 49,49,50,50 });

	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFT", { 1,1,2,2 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFTDOWN", { 3,3,4,4 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_DOWN", { 5,5,6,6 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHT", { 7,7,8,8});
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHTDOWN", { 9,9,10,10 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFTUP", { 11,11,12,12 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_UP", { 13,13,14,14 });
	BroomHeadRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHTUP", { 15,15,16,16 });

	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFT", { 17,17,18,18 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFTDOWN", { 19,19,20,20 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_DOWN", {21,21,22,22});
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHT", { 23,23,24,24 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHTDOWN", { 25,25,26,26 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_LEFTUP", { 27,27,28,28 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_UP", { 29,29,30,30 });
	BroomBodyRendererHelper.CreateFrameInfo("Ellie_Basic_Riding_Boosting_RIGHTUP", { 31,31,32,32 });

#pragma endregion


#pragma region 채칩 및 수집

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_ButterflyNet_LEFT", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 7, 13, false);
		BodyRenderer->CreateAnimation("Ellie_Basic_ButterflyNet_LEFTDOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 7, 13, false);
		BodyRenderer->CreateAnimation("Ellie_Basic_ButterflyNet_DOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 21, 27, false);
		BodyRenderer->CreateAnimation("Ellie_Basic_ButterflyNet_RIGHT", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 35, 41, false);
		BodyRenderer->CreateAnimation("Ellie_Basic_ButterflyNet_RIGHTDOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 35, 41, false);
		BodyRenderer->CreateAnimation("Ellie_Basic_ButterflyNet_LEFTUP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 49, 55, false);
		BodyRenderer->CreateAnimation("Ellie_Basic_ButterflyNet_UP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 63, 69, false);
		BodyRenderer->CreateAnimation("Ellie_Basic_ButterflyNet_RIGHTUP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 77, 83, false);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_ButterflyNet_LEFT", { 91,92,92,93,94,94,94 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_ButterflyNet_LEFTDOWN", { 91,92,92,93,94,94,94 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_ButterflyNet_DOWN", { 99,0,0,100,101,101,101 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_ButterflyNet_RIGHT", {105,106,106,107,108,108,108 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_ButterflyNet_RIGHTDOWN", {105,106,106,107,108,108,108});
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_ButterflyNet_LEFTUP", { 113,114,114,115,116,116,116 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_ButterflyNet_UP", { });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_ButterflyNet_RIGHTUP", { 121,122,122,123,124,124,124});

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_RootUp_LEFT", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 13, 20);
		BodyRenderer->CreateAnimation("Ellie_Basic_RootUp_LEFTDOWN", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 13, 20);
		BodyRenderer->CreateAnimation("Ellie_Basic_RootUp_DOWN", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 25, 32);
		BodyRenderer->CreateAnimation("Ellie_Basic_RootUp_RIGHT", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 34, 41);
		BodyRenderer->CreateAnimation("Ellie_Basic_RootUp_RIGHTDOWN", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 34, 41);
		BodyRenderer->CreateAnimation("Ellie_Basic_RootUp_LEFTUP", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 43, 50);
		BodyRenderer->CreateAnimation("Ellie_Basic_RootUp_UP", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 43, 50);
		BodyRenderer->CreateAnimation("Ellie_Basic_RootUp_RIGHTUP", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 51, 58);

		const float AnimationInter5To7 = Ellie_RootUp_Inter * 2.0f;

		const std::vector<float> FrameInters =
		{
			Ellie_RootUp_Inter,
			Ellie_RootUp_Inter,
			Ellie_RootUp_Inter,
			Ellie_RootUp_Inter,
			AnimationInter5To7,
			AnimationInter5To7,
			AnimationInter5To7,
			AnimationInter5To7,
		};

		ChangeFrameAnimationInterAllDirection("Ellie_Basic_RootUp_", FrameInters);
	}


	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_RootUp_LEFT", { 59,60,61,62,63,64,64,64 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_RootUp_LEFTDOWN", { 59,60,61,62,63,64,64,64 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_RootUp_DOWN", { 65,66,67,68,69,70,70,70 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_RootUp_RIGHT", { 71,72,73,74,75,76,76,76 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_RootUp_RIGHTDOWN", { 71,72,73,74,75,76,76,76 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_RootUp_LEFTUP", { 77,78,79,80,81,82,82,82 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_RootUp_UP", { 77,78,79,80,81,82,82,82 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_RootUp_RIGHTUP", { 83,84,85,86,87,88,88,88 });

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Sit_LEFT", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 7, 12);
		BodyRenderer->CreateAnimation("Ellie_Basic_Sit_LEFTDOWN", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 7, 12);
		BodyRenderer->CreateAnimation("Ellie_Basic_Sit_DOWN", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 7, 12);
		BodyRenderer->CreateAnimation("Ellie_Basic_Sit_RIGHT", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 13, 18);
		BodyRenderer->CreateAnimation("Ellie_Basic_Sit_RIGHTDOWN", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 13, 18);
		BodyRenderer->CreateAnimation("Ellie_Basic_Sit_LEFTUP", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 19, 24);
		BodyRenderer->CreateAnimation("Ellie_Basic_Sit_UP", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 25, 30);
		BodyRenderer->CreateAnimation("Ellie_Basic_Sit_RIGHTUP", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 25, 30);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Sit_LEFT", { 31,32,33,34,35,33 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Sit_LEFTDOWN", { 31,32,33,34,35,33 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Sit_DOWN", { 31,32,33,34,35,33 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Sit_RIGHT", { 36,37,38,39,40,38 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Sit_RIGHTDOWN", { 36,37,38,39,40,38 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Sit_LEFTUP", { 41,42,43,44,44,43 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Sit_UP", { 45,46,47,48,48,47});
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Sit_RIGHTUP", { 45,46,47,48,48,47 });


	{
		BodyRenderer->CreateAnimation("Ellie_Basic_MongSiri_LEFT", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		BodyRenderer->CreateAnimation("Ellie_Basic_MongSiri_LEFTDOWN", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		BodyRenderer->CreateAnimation("Ellie_Basic_MongSiri_DOWN", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		BodyRenderer->CreateAnimation("Ellie_Basic_MongSiri_LEFTUP", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		BodyRenderer->CreateAnimation("Ellie_Basic_MongSiri_RIGHT", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		BodyRenderer->CreateAnimation("Ellie_Basic_MongSiri_RIGHTDOWN", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		BodyRenderer->CreateAnimation("Ellie_Basic_MongSiri_UP", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		BodyRenderer->CreateAnimation("Ellie_Basic_MongSiri_RIGHTUP", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);

		const std::vector<float> FrameInters =
		{
			Ellie_RootUp_Inter,
			Ellie_RootUp_Inter,
			Ellie_RootUp_Inter,
			1.0f,
			1.0f,
		};

		ChangeFrameAnimationInterAllDirection("Ellie_Basic_MongSiri_", FrameInters);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_MongSiri_LEFT", { 14,15,16,14,14 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_MongSiri_LEFTDOWN", { 14,15,16,14,14 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_MongSiri_DOWN", { 14,15,16,14,14 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_MongSiri_RIGHT", { 17,18,19,17,17 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_MongSiri_RIGHTDOWN", { 17,18,19,17,17 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_MongSiri_LEFTUP", { 17,18,19,17,17 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_MongSiri_UP", { 17,18,19,17,17 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_MongSiri_RIGHTUP", { 17,18,19,17,17 });

#pragma endregion

	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Cheer", "Ellie_Basic_Cheer.png", 0.1f, 4, 15);
		BodyRenderer->CreateAnimation("Ellie_Basic_Fail", "Ellie_Basic_Fail.png", 0.1f, 5, 14);
		BodyRenderer->FindAnimation("Ellie_Basic_Fail")->Inter = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.16f, 0.14f, 0.12f, 0.24f };
		BodyRenderer->CreateAnimation("Ellie_Basic_Drink", "Ellie_Basic_Drink.png", 0.1f, 3, 16);
	}

	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Cheer", { 16,17,18,19, 20,21,22,23, 24,25,26,27 });
	VirgilRendererHelper.CreateFrameInfo("Ellie_Basic_Fail", { 15,16,16,17,18, 18,19,20,20,20});

	VirgilSetting();
	BroomSetting();
}

void Ellie::ChangeFrameAnimationInterAllDirection(std::string_view _AnimationName, const std::vector<float>& _Inter)
{
	std::vector<std::string> DiectionStirng =
	{
		"LEFT",
		"LEFTDOWN",
		"DOWN",
		"RIGHT",
		"RIGHTDOWN",
		"LEFTUP",
		"UP",
		"RIGHTUP"
	};

	for (int i = 0; i < DiectionStirng.size(); i++)
	{
		const std::shared_ptr<GameEngineFrameAnimation>& Animation = BodyRenderer->FindAnimation(_AnimationName.data() + DiectionStirng[i]);
		if (nullptr == Animation)
		{
			MsgBoxAssert("애니메이션이 존재하지 않습니다.");
			return;
		}

		Animation->Inter = _Inter;
	}
}
