#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayLevel.h"
#include "TitleTestLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleTestLevel>("TitleTestLevel");
	GameEngineCore::ChangeLevel("PlayLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}