#include "PreCompile.h"
#include "NormalPropEditor.h"

NormalPropEditor::NormalPropEditor() 
{
}

NormalPropEditor::~NormalPropEditor() 
{
}


void NormalPropEditor::Release()
{
	NormalProp::Release();
}

void NormalPropEditor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	NormalProp::LevelEnd(_NextLevel);
}


void NormalPropEditor::SetPixelCollision(std::string_view _FileName) 
{
	DebugRenderer = CreateComponent<GameEngineSpriteRenderer>();
	DebugRenderer->SetSprite(_FileName);
}