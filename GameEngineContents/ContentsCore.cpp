#include "PreCompile.h"
#include "ContentsCore.h"


#include "MainMenu.h"
#include "LoadingLevel.h"
#include "PlayLevel.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineSpriteRenderer::SetDefaultSampler("POINT");

	GameEngineCore::CreateLevel<MainMenu>("MainMenu");
	GameEngineCore::CreateLevel<LoadingLevel>("LoadingLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::ChangeLevel("MainMenu");

	
	GlobalValue::SetWindowScale(GetStartWindowSize());
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}