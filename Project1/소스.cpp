
#pragma comment(lib, "GameEngineBase.lib")


#include <iostream>
#include <Windows.h>
#include <GameEnginePlatform/GameEngineWindow.h>

//
// WIndows Api�� ����Ͽ� â �������̽��� �����ϴ� �ڵ忡���� ��Ŀ ���� �ý����� â���� �����ؾ� �Ѵ�.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineWindow::MessageLoop(hInstance, nullptr, nullptr, nullptr);
}