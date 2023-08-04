#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::ChangeLevel("PlayLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}