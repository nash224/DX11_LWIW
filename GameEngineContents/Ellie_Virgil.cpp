#include "PreCompile.h"
#include "Ellie.h"


void Ellie::VirgilSetting()
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("앨리 바디 렌더러가 존재하지 않습니다.");
		return;
	}

#pragma region Virgil_Ellie_Idle

	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFT", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(28); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(30); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFTDOWN", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(28); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFTDOWN", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFTDOWN", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(30); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_DOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(31); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_DOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(32); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_DOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(33); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(34); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHT", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHT", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHT", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHT", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(37); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHTDOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHTDOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHTDOWN", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHTDOWN", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(37); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFTUP", 16, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFTUP", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFTUP", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_LEFTUP", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });

	BodyRenderer->SetStartEvent("Ellie_Basic_Idle_UP", [&](GameEngineSpriteRenderer* _Renderer) {Virgil->Off(); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHTUP", 24, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHTUP", 25, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(41); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHTUP", 26, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(41); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Idle_RIGHTUP", 27, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(40); });
#pragma endregion

#pragma region Virgil_Ellie_Walk

	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFT", 34, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFT", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(99); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFT", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFT", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(101); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFT", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFT", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(109); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFT", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFT", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 34, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(99); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(101); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(109); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_DOWN", 42, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(110); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_DOWN", 43, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(111); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_DOWN", 44, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_DOWN", 45, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_DOWN", 46, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(110); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_DOWN", 47, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(111); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_DOWN", 48, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_DOWN", 49, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });



	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 54, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 57, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 59, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 60, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 61, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 54, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 57, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 59, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 60, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 61, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 66, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(120); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 67, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 68, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(119); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 69, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(119); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 70, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(120); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 71, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 72, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 73, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });

	BodyRenderer->SetStartEvent("Ellie_Basic_Walk_UP", [&](GameEngineSpriteRenderer* _Renderer) {Virgil->Off(); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 91, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(126); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 92, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 93, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 94, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(128); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 95, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(126); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 96, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 97, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(128); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 98, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(128); });

#pragma endregion

#pragma region Virgil_Ellie_SlowWalk

	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 34, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(99); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(101); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(109); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 34, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(99); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(101); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(109); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 42, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(110); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 43, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(111); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 44, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 45, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 46, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(110); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 47, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(111); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 48, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 49, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 54, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 57, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 59, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 60, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 61, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 54, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 57, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 59, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 60, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 61, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 66, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(120); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 67, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 68, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(119); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 69, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(119); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 70, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(120); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 71, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 72, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 73, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });

	BodyRenderer->SetStartEvent("Ellie_Basic_SlowWalk_UP", [&](GameEngineSpriteRenderer* _Renderer) {Virgil->Off(); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 91, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(126); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 92, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 93, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 94, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(128); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 95, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(126); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 96, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 97, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(128); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 98, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(128); });

#pragma endregion

#pragma region Virgil_Ellie_Run

	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFT", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(43); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(44); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFT", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFT", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(43); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(44); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_DOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_DOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_DOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_DOWN", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(49); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_DOWN", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(49); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHT", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHT", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(52); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHT", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(53); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHT", 20, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHT", 21, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(54); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHT", 22, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(55); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(52); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(53); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 20, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 21, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(54); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 22, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(55); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 23, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(56); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 24, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(57); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 25, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(58); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 26, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(59); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 27, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(60); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 28, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(61); });

	BodyRenderer->SetStartEvent("Ellie_Basic_Run_UP", [&](GameEngineSpriteRenderer* _Renderer) {Virgil->Off(); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(62); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(63); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(64); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(65); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(66); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(67); });
#pragma endregion

#pragma region Virgil_Ellie_ButterflyNet

	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(91); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFT", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(92); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFT", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(92); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFT", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(93); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFT", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(94); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFT", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(94); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFT", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(94); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(91); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTDOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(92); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTDOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(92); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTDOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(93); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTDOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(94); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTDOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(94); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTDOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(94); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_DOWN", 21, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(99); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_DOWN", 22, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_DOWN", 23, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_DOWN", 24, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(100); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_DOWN", 25, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(101); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_DOWN", 26, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(101); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_DOWN", 27, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(101); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHT", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(105); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHT", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(106); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHT", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(106); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHT", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(107); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHT", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHT", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHT", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTDOWN", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(105); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTDOWN", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(106); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTDOWN", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(106); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTDOWN", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(107); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTDOWN", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTDOWN", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTDOWN", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTUP", 49, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(113); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTUP", 50, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTUP", 51, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTUP", 52, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(115); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTUP", 53, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTUP", 54, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_LEFTUP", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(116); });


	BodyRenderer->SetStartEvent("Ellie_Basic_ButterflyNet_UP", [&](GameEngineSpriteRenderer* _Renderer) {Virgil->Off(); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTUP", 77, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(121); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTUP", 78, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(122); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTUP", 79, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(122); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTUP", 80, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(123); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTUP", 81, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(124); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTUP", 82, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(124); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_ButterflyNet_RIGHTUP", 83, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(124); });

#pragma endregion

#pragma region Virgil_Ellie_RootUp

	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFT", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(59); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFT", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(60); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFT", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(61); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFT", 16, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(62); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFT", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(63); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFT", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(64); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFT", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(64); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFT", 20, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(64); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTDOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(59); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTDOWN", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(60); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTDOWN", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(61); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTDOWN", 16, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(62); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTDOWN", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(63); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTDOWN", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(64); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTDOWN", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(64); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTDOWN", 20, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(64); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_DOWN", 25, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(65); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_DOWN", 26, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(66); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_DOWN", 27, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(67); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_DOWN", 28, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(68); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_DOWN", 29, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(69); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_DOWN", 30, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(70); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_DOWN", 31, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(70); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_DOWN", 32, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(70); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHT", 34, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(71); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHT", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(72); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHT", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(73); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHT", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(74); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHT", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(75); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHT", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(76); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHT", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(76); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHT", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(76); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTDOWN", 34, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(71); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTDOWN", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(72); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTDOWN", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(73); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTDOWN", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(74); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTDOWN", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(75); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTDOWN", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(76); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTDOWN", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(76); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTDOWN", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(76); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTUP", 43, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(77); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTUP", 44, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(78); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTUP", 45, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(79); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTUP", 46, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(80); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTUP", 47, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(81); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTUP", 48, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(82); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTUP", 49, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(82); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_LEFTUP", 50, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(82); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_UP", 43, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(77); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_UP", 44, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(78); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_UP", 45, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(79); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_UP", 46, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(80); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_UP", 47, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(81); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_UP", 48, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(82); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_UP", 49, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(82); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_UP", 50, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(82); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTUP", 51, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(83); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTUP", 52, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(84); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTUP", 53, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(85); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTUP", 54, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(86); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTUP", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(87); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTUP", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(88); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTUP", 57, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(88); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_RootUp_RIGHTUP", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(88); });

#pragma endregion

#pragma region Virgil_Ellie_Sit

	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(31); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFT", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(32); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFT", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(33); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFT", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(34); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFT", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFT", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(33); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(31); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTDOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(32); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTDOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(33); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTDOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(34); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTDOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTDOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(33); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_DOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(31); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_DOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(32); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_DOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(33); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_DOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(34); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_DOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(33); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHT", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHT", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(37); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHT", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHT", 16, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHT", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHT", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTDOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTDOWN", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(37); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTDOWN", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTDOWN", 16, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTDOWN", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTDOWN", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTUP", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(41); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTUP", 20, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTUP", 21, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(43); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTUP", 22, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(44); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTUP", 23, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(44); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_LEFTUP", 24, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(43); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_UP", 25, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_UP", 26, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_UP", 27, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_UP", 28, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_UP", 29, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_UP", 30, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTUP", 25, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTUP", 26, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTUP", 27, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTUP", 28, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTUP", 29, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Sit_RIGHTUP", 30, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });


#pragma endregion

#pragma region Virgil_Ellie_MongSiri

	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFT", 3, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFT", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(15); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(16); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTDOWN", 3, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTDOWN", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(15); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTDOWN", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(16); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTDOWN", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_DOWN", 3, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_DOWN", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(15); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_DOWN", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(16); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_DOWN", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_DOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(14); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTUP", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTUP", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(18); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTUP", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(19); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTUP", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_LEFTUP", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHT", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHT", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(18); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHT", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(19); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHT", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHT", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTDOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTDOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(18); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTDOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(19); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTDOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTDOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_UP", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_UP", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(18); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_UP", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(19); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_UP", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_UP", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTUP", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTUP", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(18); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTUP", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(19); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTUP", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_MongSiri_RIGHTUP", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });

#pragma endregion

#pragma region Virgil_Ellie_Throw

	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFT", 3, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFT", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(37); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTDOWN", 3, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTDOWN", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(37); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTDOWN", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTDOWN", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_DOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_DOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(41); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_DOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_DOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHT", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(43); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHT", 16, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(44); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHT", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHT", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHT", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTDOWN", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(43); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTDOWN", 16, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(44); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTDOWN", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTDOWN", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTDOWN", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTUP", 20, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTUP", 21, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTUP", 22, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(49); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTUP", 23, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(50); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_LEFTUP", 24, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(50); });


	BodyRenderer->SetStartEvent("Ellie_Basic_Throw_UP", [&](GameEngineSpriteRenderer* _Renderer) {Virgil->Off(); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTUP", 31, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTUP", 32, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(52); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTUP", 33, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(53); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTUP", 34, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(54); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Throw_RIGHTUP", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(54); });

#pragma endregion

#pragma region Virgil_Ellie_Cheer

	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 4, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(16);
			Shadow->ChangeCurSprite(1);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 5, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(17);
			Shadow->ChangeCurSprite(2);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 6, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(18);
			Shadow->ChangeCurSprite(3);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 6, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(19);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 8, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(20);
			Shadow->ChangeCurSprite(2);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 9, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(21);
			Shadow->ChangeCurSprite(1);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 10, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(22);
			EllieFx->SetSprite("Ellie_Basic_Cheer.png", 28);
			EllieFx->On();
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 11, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(23);
			EllieFx->ChangeCurSprite(29);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 12, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(24);
			EllieFx->ChangeCurSprite(30);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 13, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(25);
			EllieFx->ChangeCurSprite(31);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 14, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(26);
			EllieFx->ChangeCurSprite(32);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 15, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(27);
			EllieFx->ChangeCurSprite(33);
		});
	BodyRenderer->SetEndEvent("Ellie_Basic_Cheer", [&](GameEngineSpriteRenderer* _Renderer)
		{
			EllieFx->Off();
		});

#pragma endregion

#pragma region Virgil_Ellie_Fail

	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(15); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(16); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(16); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(17); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 9, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(18);
			Shadow->SetSprite("Ellie_Basic_Fail.png", 1);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 10, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(18);
			EllieFx->SetSprite("Ellie_Basic_Fail.png", 21);
			EllieFx->On();
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 11, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(19);
			EllieFx->ChangeCurSprite(22);
			Shadow->ChangeCurSprite(3);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 12, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(20);
			EllieFx->ChangeCurSprite(23);
			Shadow->ChangeCurSprite(4);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 13, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(20);
			EllieFx->ChangeCurSprite(24);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 14, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->ChangeCurSprite(20);
			EllieFx->ChangeCurSprite(25);
		});
	BodyRenderer->SetEndEvent("Ellie_Basic_Fail", [&](GameEngineSpriteRenderer* _Renderer)
		{
			EllieFx->Off();
		});

#pragma endregion

}