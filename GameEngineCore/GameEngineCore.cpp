#include "PreCompile.h"
#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}


void GameEngineCore::EngineStart(HINSTANCE _Inst) 
{
	GameEngineWindow::MainWindow.Open("TestWindow", _Inst);
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });

	GameEngineWindow::MessageLoop(_Inst, nullptr, nullptr, nullptr);
}