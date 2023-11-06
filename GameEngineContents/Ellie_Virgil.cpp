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


	m_Body->SetStartEvent("Ellie_Basic_Idle_LEFT", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Virgil->On();
			Virgil->SetSprite("Ellie_Basic_Idle.png", 28); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(29); });
	m_Body->SetFrameEvent("Ellie_Basic_Idle_LEFT", 7, [&](GameEngineSpriteRenderer* _Renderer) {Virgil->ChangeCurSprite(30); });

	//m_Body->CreateAnimation("Ellie_Basic_Walk_LEFT", "Ellie_Basic_Walk.png", 0.1f, 34, 41);
	//m_Body->CreateAnimation("Ellie_Basic_Walk_LEFTDOWN", "Ellie_Basic_Walk.png", 0.1f, 34, 41);
	//m_Body->CreateAnimation("Ellie_Basic_Walk_DOWN", "Ellie_Basic_Walk.png", 0.1f, 42, 49);
	//m_Body->CreateAnimation("Ellie_Basic_Walk_RIGHT", "Ellie_Basic_Walk.png", 0.1f, 54, 61);
	//m_Body->CreateAnimation("Ellie_Basic_Walk_RIGHTDOWN", "Ellie_Basic_Walk.png", 0.1f, 54, 61);
	//m_Body->CreateAnimation("Ellie_Basic_Walk_LEFTUP", "Ellie_Basic_Walk.png", 0.1f, 66, 73);
	//m_Body->CreateAnimation("Ellie_Basic_Walk_UP", "Ellie_Basic_Walk.png", 0.1f, 78, 85);
	//m_Body->CreateAnimation("Ellie_Basic_Walk_RIGHTUP", "Ellie_Basic_Walk.png", 0.1f, 91, 98);
}