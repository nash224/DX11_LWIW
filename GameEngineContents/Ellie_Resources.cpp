#include "PreCompile.h"
#include "Ellie.h"




void Ellie::RendererSetting()
{
	static std::uint32_t EllieGroupOrder = 0;

	const float ShadowDepth = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow);


	m_Body = CreateComponent<GameEngineSpriteRenderer>(EllieGroupOrder);
	Shadow = CreateComponent<GameEngineSpriteRenderer>(EllieGroupOrder);
	EllieFx = CreateComponent<GameEngineSpriteRenderer>(EllieGroupOrder);
	Virgil = CreateComponent<GameEngineSpriteRenderer>(EllieGroupOrder);
	
	Shadow->Transform.SetLocalPosition(float4(0.0f, LWIW_Ellie_Y_Correction, ShadowDepth));
	EllieFx->Transform.SetLocalPosition(float4(0.0f, LWIW_Ellie_Y_Correction, -2.0f));
	Virgil->Transform.SetLocalPosition(float4(0.0f, LWIW_Ellie_Y_Correction, -1.0f));
	
	

	EllieFx->Off();

	if (nullptr == GameEngineSprite::Find("Ellie_Basic_Idle.png"))
	{
		// 기본조작
		GameEngineSprite::CreateCut("Ellie_Basic_Idle.png", 7, 6);
		GameEngineSprite::CreateCut("Ellie_Basic_Walk.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_Run.png", 9, 8);
		GameEngineSprite::CreateCut("Ellie_Basic_Throw.png", 8, 7);

		// 기본조작 - Riding
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Standing.png", 8, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Moving.png", 8, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Boosting.png", 8, 7);

		// 수집 
		GameEngineSprite::CreateCut("Ellie_Basic_ButterflyNet.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_RootUp.png", 10, 9);
		GameEngineSprite::CreateCut("Ellie_Basic_Sit.png", 7, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Mongsiri.png", 5, 4);

		// 단일 방향
		GameEngineSprite::CreateCut("Ellie_Basic_Cheer.png", 6, 6);
		GameEngineSprite::CreateCut("Ellie_Basic_Fail.png", 6, 5);
		GameEngineSprite::CreateCut("Ellie_Basic_Drink.png", 6, 5);

		// Ride Fx
		GameEngineSprite::CreateCut("Broom_Ride_Fx_Sample.png", 3, 3);
	}

#pragma region 기본 조작



	{
		m_Body->CreateAnimation("Ellie_Basic_Idle_LEFT", "Ellie_Basic_Idle.png", EllieIdleInter, 4, 7);
		m_Body->CreateAnimation("Ellie_Basic_Idle_LEFTDOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 4, 7);
		m_Body->CreateAnimation("Ellie_Basic_Idle_DOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 8, 11);
		m_Body->CreateAnimation("Ellie_Basic_Idle_RIGHT", "Ellie_Basic_Idle.png", EllieIdleInter, 12, 15);
		m_Body->CreateAnimation("Ellie_Basic_Idle_RIGHTDOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 12, 15);
		m_Body->CreateAnimation("Ellie_Basic_Idle_LEFTUP", "Ellie_Basic_Idle.png", EllieIdleInter, 16, 19);
		m_Body->CreateAnimation("Ellie_Basic_Idle_UP", "Ellie_Basic_Idle.png", EllieIdleInter, 20, 23);
		m_Body->CreateAnimation("Ellie_Basic_Idle_RIGHTUP", "Ellie_Basic_Idle.png", EllieIdleInter, 24, 27);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_Walk_LEFT", "Ellie_Basic_Walk.png", 0.1f, 34, 41);
		m_Body->CreateAnimation("Ellie_Basic_Walk_LEFTDOWN", "Ellie_Basic_Walk.png", 0.1f, 34, 41);
		m_Body->CreateAnimation("Ellie_Basic_Walk_DOWN", "Ellie_Basic_Walk.png", 0.1f, 42, 49);
		m_Body->CreateAnimation("Ellie_Basic_Walk_RIGHT", "Ellie_Basic_Walk.png", 0.1f, 54, 61);
		m_Body->CreateAnimation("Ellie_Basic_Walk_RIGHTDOWN", "Ellie_Basic_Walk.png", 0.1f, 54, 61);
		m_Body->CreateAnimation("Ellie_Basic_Walk_LEFTUP", "Ellie_Basic_Walk.png", 0.1f, 66, 73);
		m_Body->CreateAnimation("Ellie_Basic_Walk_UP", "Ellie_Basic_Walk.png", 0.1f, 78, 85);
		m_Body->CreateAnimation("Ellie_Basic_Walk_RIGHTUP", "Ellie_Basic_Walk.png", 0.1f, 91, 98);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_SlowWalk_LEFT", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 34, 41);
		m_Body->CreateAnimation("Ellie_Basic_SlowWalk_LEFTDOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 34, 41);
		m_Body->CreateAnimation("Ellie_Basic_SlowWalk_DOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 42, 49);
		m_Body->CreateAnimation("Ellie_Basic_SlowWalk_RIGHT", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 54, 61);
		m_Body->CreateAnimation("Ellie_Basic_SlowWalk_RIGHTDOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 54, 61);
		m_Body->CreateAnimation("Ellie_Basic_SlowWalk_LEFTUP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 66, 73);
		m_Body->CreateAnimation("Ellie_Basic_SlowWalk_UP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 78, 85);
		m_Body->CreateAnimation("Ellie_Basic_SlowWalk_RIGHTUP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 91, 98);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_Run_LEFT", "Ellie_Basic_Run.png", Ellie_Run_Inter, 4, 9);
		m_Body->CreateAnimation("Ellie_Basic_Run_LEFTDOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 4, 9);
		m_Body->CreateAnimation("Ellie_Basic_Run_DOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 10, 15);
		m_Body->CreateAnimation("Ellie_Basic_Run_RIGHT", "Ellie_Basic_Run.png", Ellie_Run_Inter, 17, 22);
		m_Body->CreateAnimation("Ellie_Basic_Run_RIGHTDOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 17, 22);
		m_Body->CreateAnimation("Ellie_Basic_Run_LEFTUP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 23, 28);
		m_Body->CreateAnimation("Ellie_Basic_Run_UP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 30, 35);
		m_Body->CreateAnimation("Ellie_Basic_Run_RIGHTUP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 36, 41);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_Throw_LEFT", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 4, 8);
		m_Body->CreateAnimation("Ellie_Basic_Throw_LEFTDOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 4, 8);
		m_Body->CreateAnimation("Ellie_Basic_Throw_DOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 9, 13);
		m_Body->CreateAnimation("Ellie_Basic_Throw_RIGHT", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 15, 19);
		m_Body->CreateAnimation("Ellie_Basic_Throw_RIGHTDOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 15, 19);
		m_Body->CreateAnimation("Ellie_Basic_Throw_LEFTUP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 20, 24);
		m_Body->CreateAnimation("Ellie_Basic_Throw_UP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 25, 29);
		m_Body->CreateAnimation("Ellie_Basic_Throw_RIGHTUP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 31, 35);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_Riding_Standing_LEFT", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 7, 10);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Standing_LEFTDOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 7, 10);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Standing_DOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 11, 14);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Standing_RIGHT", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 15, 18);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Standing_RIGHTDOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 15, 18);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Standing_LEFTUP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 23, 26);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Standing_UP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 27, 30);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Standing_RIGHTUP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 31, 34);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_Riding_Moving_LEFT", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 7, 10);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Moving_LEFTDOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 7, 10);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Moving_DOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 11, 14);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Moving_RIGHT", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 15, 18);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Moving_RIGHTDOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 15, 18);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Moving_LEFTUP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 23, 26);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Moving_UP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 27, 30);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Moving_RIGHTUP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 31, 34);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_Riding_Boosting_LEFT", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 7, 10);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Boosting_LEFTDOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 7, 10);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Boosting_DOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 11, 14);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Boosting_RIGHT", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 15, 18);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Boosting_RIGHTDOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 15, 18);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Boosting_LEFTUP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 23, 26);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Boosting_UP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 27, 30);
		m_Body->CreateAnimation("Ellie_Basic_Riding_Boosting_RIGHTUP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 31, 34);
	}

#pragma endregion


#pragma region 채칩 및 수집

	{
		m_Body->CreateAnimation("Ellie_Basic_ButterflyNet_LEFT", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 7, 13, false);
		m_Body->CreateAnimation("Ellie_Basic_ButterflyNet_LEFTDOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 7, 13, false);
		m_Body->CreateAnimation("Ellie_Basic_ButterflyNet_DOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 21, 27, false);
		m_Body->CreateAnimation("Ellie_Basic_ButterflyNet_RIGHT", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 35, 41, false);
		m_Body->CreateAnimation("Ellie_Basic_ButterflyNet_RIGHTDOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 35, 41, false);
		m_Body->CreateAnimation("Ellie_Basic_ButterflyNet_LEFTUP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 49, 55, false);
		m_Body->CreateAnimation("Ellie_Basic_ButterflyNet_UP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 63, 69, false);
		m_Body->CreateAnimation("Ellie_Basic_ButterflyNet_RIGHTUP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 77, 83, false);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_RootUp_LEFT", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 13, 20);
		m_Body->CreateAnimation("Ellie_Basic_RootUp_LEFTDOWN", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 13, 20);
		m_Body->CreateAnimation("Ellie_Basic_RootUp_DOWN", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 25, 32);
		m_Body->CreateAnimation("Ellie_Basic_RootUp_RIGHT", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 34, 41);
		m_Body->CreateAnimation("Ellie_Basic_RootUp_RIGHTDOWN", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 34, 41);
		m_Body->CreateAnimation("Ellie_Basic_RootUp_LEFTUP", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 43, 50);
		m_Body->CreateAnimation("Ellie_Basic_RootUp_UP", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 43, 50);
		m_Body->CreateAnimation("Ellie_Basic_RootUp_RIGHTUP", "Ellie_Basic_RootUp.png", Ellie_RootUp_Inter, 51, 58);

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

	{
		m_Body->CreateAnimation("Ellie_Basic_Sit_LEFT", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 7, 12);
		m_Body->CreateAnimation("Ellie_Basic_Sit_LEFTDOWN", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 7, 12);
		m_Body->CreateAnimation("Ellie_Basic_Sit_DOWN", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 7, 12);
		m_Body->CreateAnimation("Ellie_Basic_Sit_RIGHT", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 13, 18);
		m_Body->CreateAnimation("Ellie_Basic_Sit_RIGHTDOWN", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 13, 18);
		m_Body->CreateAnimation("Ellie_Basic_Sit_LEFTUP", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 19, 24);
		m_Body->CreateAnimation("Ellie_Basic_Sit_UP", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 25, 30);
		m_Body->CreateAnimation("Ellie_Basic_Sit_RIGHTUP", "Ellie_Basic_Sit.png", Ellie_Sit_Inter, 25, 30);
	}

	{
		m_Body->CreateAnimation("Ellie_Basic_MongSiri_LEFT", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		m_Body->CreateAnimation("Ellie_Basic_MongSiri_LEFTDOWN", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		m_Body->CreateAnimation("Ellie_Basic_MongSiri_DOWN", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		m_Body->CreateAnimation("Ellie_Basic_MongSiri_LEFTUP", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		m_Body->CreateAnimation("Ellie_Basic_MongSiri_RIGHT", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		m_Body->CreateAnimation("Ellie_Basic_MongSiri_RIGHTDOWN", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		m_Body->CreateAnimation("Ellie_Basic_MongSiri_UP", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		m_Body->CreateAnimation("Ellie_Basic_MongSiri_RIGHTUP", "Ellie_Basic_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);

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

#pragma endregion

	{
		m_Body->CreateAnimation("Ellie_Basic_Cheer", "Ellie_Basic_Cheer.png", 0.1f, 4, 15);
		m_Body->CreateAnimation("Ellie_Basic_Fail", "Ellie_Basic_Fail.png", 0.1f, 5, 14);
		m_Body->FindAnimation("Ellie_Basic_Fail")->Inter = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.16f, 0.14f, 0.12f, 0.24f };
		m_Body->CreateAnimation("Ellie_Basic_Drink", "Ellie_Basic_Drink.png", 0.1f, 3, 16);
	}

	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({ 0.0f , 30.0f });

	VirgilSetting();
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
		std::weak_ptr<GameEngineFrameAnimation> Animation = m_Body->FindAnimation(_AnimationName.data() + DiectionStirng[i]);
		if (true == Animation.expired())
		{
			MsgBoxAssert("애니메이션이 존재하지 않습니다.");
			return;
		}

		Animation.lock()->Inter = _Inter;
	}
}
