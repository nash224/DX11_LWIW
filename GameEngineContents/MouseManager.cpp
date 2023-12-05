#include "PreCompile.h"
#include "MouseManager.h"

MouseManager::MouseManager() 
{
}

MouseManager::~MouseManager() 
{
}


void MouseManager::Update(float _Delta)
{
	MousePosition = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	RenewMousePos();
}

void MouseManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void MouseManager::RenewMousePos()
{
	m_MouseInfo.CurPos = MousePosition;
	m_MouseInfo.MovePos = m_MouseInfo.CurPos - m_MouseInfo.PrevPos;
	m_MouseInfo.PrevPos = m_MouseInfo.CurPos;
}