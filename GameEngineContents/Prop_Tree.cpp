#include "PreCompile.h"
#include "Prop_Tree.h"

Prop_Tree::Prop_Tree() 
{
}

Prop_Tree::~Prop_Tree() 
{
}


void Prop_Tree::Start()
{

}

void Prop_Tree::Update(float _Delta)
{

}

void Prop_Tree::Release()
{
	m_Renderer = nullptr;
}

void Prop_Tree::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void Prop_Tree::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Prop_Tree::SelectTreeType(ETREETYPE _Type)
{
	m_TreeType = _Type;
}

void Prop_Tree::Init()
{
	std::string FileName = "";

	switch (m_TreeType)
	{
	case ETREETYPE::Tree0:
		FileName = "Tree_0.png";
		break;
	case ETREETYPE::Tree1:
		FileName = "Tree_1.png";
		break;
	case ETREETYPE::Tree2:
		FileName = "Tree_2.png";
		break;
	case ETREETYPE::Tree3:
		FileName = "Tree_3.png";
		break;
	case ETREETYPE::Tree4:
		FileName = "Tree_4.png";
		break;
	case ETREETYPE::Tree5:
		FileName = "Tree_5.png";
		break;
	default:
		break;
	}

	RendererSetting(FileName);
}

void Prop_Tree::RendererSetting(std::string_view _FileName)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);

	m_Renderer->SetSprite(_FileName);
	m_Renderer->Transform.SetLocalPosition({ 0.0f , m_TreeRendererBias });
}