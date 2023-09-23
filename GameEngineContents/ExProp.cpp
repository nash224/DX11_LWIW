#include "PreCompile.h"
#include "ExProp.h"

ExProp::ExProp() 
{
}

ExProp::~ExProp() 
{
}


void ExProp::Start()
{
	Prop::Start();
}

void ExProp::Update(float _Delta)
{
	Prop::Update(_Delta);
}

void ExProp::LevelStart(class GameEngineLevel* _NextLevel)
{
	Prop::LevelStart(_NextLevel);
}

void ExProp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Prop::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void ExProp::CreateExProp(std::vector<ExPropParameter>& _Parameter)
{
	for (size_t i = 0; i < _Parameter.size(); i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(_Parameter[i].Order);
		if (nullptr == Renderer)
		{
			MsgBoxAssert("�������� �������� ���߽��ϴ�.");
			return;
		}

		Renderer->SetSprite(_Parameter[i].FileName);
		Renderer->Transform.SetLocalPosition(_Parameter[i].RendererLocalPosition);
	}
}

void ExProp::ChangeExPropImageScale(unsigned int _Order, const float4& _ImageScale)
{
	if (nullptr == vecRenderer[_Order])
	{
		MsgBoxAssert("���� �迭�� ��ü�� �������� �ʽ��ϴ�.");
		return;
	}

	vecRenderer[_Order]->SetImageScale(_ImageScale);
}


void ExProp::ActorRelease()
{
	Prop::ActorRelease();

	vecRenderer.clear();
}