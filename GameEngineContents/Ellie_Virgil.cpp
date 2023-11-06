#include "PreCompile.h"
#include "Ellie.h"


void Ellie::VirgilSetting()
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("앨리 바디 렌더러가 존재하지 않습니다.");
		return;
	}

#pragma region Virgil_Ellie_Idle

	m_Body->SetStartEvent("Ellie_Basic_Idle_LEFT", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Idle.png", 28); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(30); });

	m_Body->SetStartEvent("Ellie_Basic_Idle_LEFTDOWN", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Idle.png", 28); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFTDOWN", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFTDOWN", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(30); });

	m_Body->SetStartEvent("Ellie_Basic_Idle_DOWN", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Idle.png", 31); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_DOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(32); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_DOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(33); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(34); });

	m_Body->SetStartEvent("Ellie_Basic_Idle_RIGHT", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Idle.png", 35); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_RIGHT", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_RIGHT", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(36); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_RIGHT", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(37); });

	m_Body->SetStartEvent("Ellie_Basic_Idle_LEFTUP", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Idle.png", 38); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFTUP", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFTUP", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(39); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFTUP", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(38); });

	m_Body->SetStartEvent("Ellie_Basic_Idle_RIGHTUP", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Idle.png", 40); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_RIGHTUP", 25, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(41); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_RIGHTUP", 26, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(41); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_RIGHTUP", 27, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(40); });
#pragma endregion

#pragma region Virgil_Ellie_Walk

	m_Body->SetStartEvent("Ellie_Basic_Walk_LEFT", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 108); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFT", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(102); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFT", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFT", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(102); });

	m_Body->SetStartEvent("Ellie_Basic_Walk_LEFTDOWN", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 108); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(102); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFTDOWN", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(102); });

	m_Body->SetStartEvent("Ellie_Basic_Walk_DOWN", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 107); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_DOWN", 43, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(105); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_DOWN", 44, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(106); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_DOWN", 46, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(107); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_DOWN", 47, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(105); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_DOWN", 48, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(106); });

	m_Body->SetStartEvent("Ellie_Basic_Walk_RIGHT", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 116); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHT", 59, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });

	m_Body->SetStartEvent("Ellie_Basic_Walk_RIGHTDOWN", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 116); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHTDOWN", 59, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });

	m_Body->SetStartEvent("Ellie_Basic_Walk_LEFTUP", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 120); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 67, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(119); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 70, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(120); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_LEFTUP", 71, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(118); });

	m_Body->SetStartEvent("Ellie_Basic_Walk_UP", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 122); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_UP", 79, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(123); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_UP", 80, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(122); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_UP", 83, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(123); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_UP", 84, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(122); });

	m_Body->SetStartEvent("Ellie_Basic_Walk_RIGHTUP", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 126); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 92, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 95, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(126); });
	m_Body->SetFrameEvent("Ellie_Basic_Walk_RIGHTUP", 96, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });

#pragma endregion

#pragma region Virgil_Ellie_SlowWalk

	m_Body->SetStartEvent("Ellie_Basic_SlowWalk_LEFT", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 108); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(102); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFT", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(102); });

	m_Body->SetStartEvent("Ellie_Basic_SlowWalk_LEFTDOWN", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 108); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 35, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(102); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(108); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTDOWN", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(102); });

	m_Body->SetStartEvent("Ellie_Basic_SlowWalk_DOWN", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 107); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 43, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(105); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 44, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(106); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 46, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(107); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 47, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(105); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_DOWN", 48, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(106); });

	m_Body->SetStartEvent("Ellie_Basic_SlowWalk_RIGHT", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 116); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHT", 59, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });

	m_Body->SetStartEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 116); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 55, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 56, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 58, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(117); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTDOWN", 59, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(114); });

	m_Body->SetStartEvent("Ellie_Basic_SlowWalk_LEFTUP", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 120); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 67, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(119); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 70, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(120); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_LEFTUP", 71, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(118); });

	m_Body->SetStartEvent("Ellie_Basic_SlowWalk_UP", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 122); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_UP", 79, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(123); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_UP", 80, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(122); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_UP", 83, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(123); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_UP", 84, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(122); });

	m_Body->SetStartEvent("Ellie_Basic_SlowWalk_RIGHTUP", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Walk.png", 126); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 92, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 95, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(126); });
	m_Body->SetFrameEvent("Ellie_Basic_SlowWalk_RIGHTUP", 96, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(127); });

#pragma endregion


	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFT", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(43); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(44); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFT", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(45); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFT", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });

	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 4, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(43); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(44); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(42); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(45); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTDOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(46); });

	m_Body->SetFrameEvent("Ellie_Basic_Run_DOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_DOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(48); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_DOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(47); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_DOWN", 14, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(49); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_DOWN", 15, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(49); });

	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHT", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHT", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(52); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHT", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(53); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHT", 20, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHT", 21, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(54); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHT", 22, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(55); });

	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 17, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 18, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(52); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 19, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(53); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 20, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(51); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 21, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(54); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTDOWN", 22, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(55); });

	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 23, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(56); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 24, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(57); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 25, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(58); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 26, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(59); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 27, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(60); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_LEFTUP", 28, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(61); });

	m_Body->SetStartEvent("Ellie_Basic_Run_UP", [&](GameEngineSpriteRenderer* _Renderer) {Virgil->Off(); });

	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 36, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(62); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 37, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(63); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 38, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(64); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 39, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(65); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 40, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(66); });
	m_Body->SetFrameEvent("Ellie_Basic_Run_RIGHTUP", 41, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(67); });



	//m_Body->CreateAnimation("Ellie_Basic_Run_LEFT", "Ellie_Basic_Run.png", Ellie_Run_Inter, 4, 9);
	//m_Body->CreateAnimation("Ellie_Basic_Run_LEFTDOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 4, 9);
	//m_Body->CreateAnimation("Ellie_Basic_Run_DOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 10, 15);
	//m_Body->CreateAnimation("Ellie_Basic_Run_RIGHT", "Ellie_Basic_Run.png", Ellie_Run_Inter, 17, 22);
	//m_Body->CreateAnimation("Ellie_Basic_Run_RIGHTDOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 17, 22);
	//m_Body->CreateAnimation("Ellie_Basic_Run_LEFTUP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 23, 28);
	//m_Body->CreateAnimation("Ellie_Basic_Run_UP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 30, 35);
	//m_Body->CreateAnimation("Ellie_Basic_Run_RIGHTUP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 36, 41);

}