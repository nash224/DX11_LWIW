#include "PreCompile.h"
#include "Prop.h"

#include "BackDrop_PlayLevel.h"

Prop::Prop()
{
}

Prop::~Prop()
{
}


void Prop::Start()
{

}

void Prop::Update(float _Delta)
{

}

void Prop::Release()
{
	m_Renderer = nullptr;
	m_DebugRenderer = nullptr;
}

void Prop::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Prop::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Prop::CreateRenderer(int _Order /*= 0*/)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�߸� ������� �������Դϴ�.");
		return;
	}
}


void Prop::SetSprite(std::string_view _SpriteName)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ��������Ʈ�� ������ �� �����ϴ�.");
		return;
	}

	m_Renderer->SetSprite(_SpriteName);
}

void Prop::SetRendererPivotType(PivotType _Direction/* = EDIRECTION::CENTER*/)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_Renderer->SetPivotType(_Direction);
}

void Prop::SetRendererImageScale(const float4& _Scale)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_Renderer->SetImageScale(_Scale);
}

// �÷��� �������� ZSort
void Prop::SetPositionAndDepth(const float4& _Position)
{
	const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetPlayLevelPtr()->GetBackDropPtr();
	if (nullptr == BackDropPtr)
	{
		MsgBoxAssert("��� �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	float Depth = DepthFunction::CalculateObjectDepth(BackDropPtr->GetBackGroundScale().Y, _Position.Y);
	Transform.SetLocalPosition({ _Position.X, _Position.Y, Depth });
}


#pragma region �ִϸ��̼� ����

void Prop::CreateAndSetAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/
)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_Renderer->CreateAnimation(_AnimationName, _SpriteName, _Inter);
	m_Renderer->ChangeAnimation(_AnimationName);
	m_Renderer->AutoSpriteSizeOn();
}

// �ڵ����� AutoSize�� ��û�մϴ�.
void Prop::SetAutoSpriteSize(float _Ratio, bool _Value /*= true*/)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����� �� �����ϴ�.");
	}

	_Value ? m_Renderer->AutoSpriteSizeOn() : m_Renderer->AutoSpriteSizeOff();
	m_Renderer->SetAutoScaleRatio(_Ratio);
}

#pragma endregion
