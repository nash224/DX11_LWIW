#include "PreCompile.h"
#include "Prop.h"

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

}

void Prop::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Prop::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Prop::CreateRenderer(int _Order)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("잘못 만들어진 렌더러입니다.");
		return;
	}
}

void Prop::SetSprite(std::string_view _SpriteName)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 스프라이트를 세팅할 수 없습니다.");
		return;
	}

	m_Renderer->SetSprite(_SpriteName);
}

void Prop::SetPosition(const float4& _Position, PivotType _Direction/* = EDIRECTION::CENTER*/)
{
	Transform.SetLocalPosition(_Position);

	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 애니메이션을 생성하려고 했습니다.");
		return;
	}

	m_Renderer->SetPivotType(_Direction);

	//float4 HScale = m_TextureScale.Half();
	//Transform.SetLocalPosition(HScale);
}

void Prop::SetRendererImageScale(const float4& _Scale)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 애니메이션을 생성하려고 했습니다.");
		return;
	}

	m_Renderer->SetImageScale(_Scale);
}


void Prop::SetSpriteRenderer(std::string_view _FileName, const float4& _Position /*= float4::ZERO*/, PivotType _Type /*= PivotType::Center*/)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 스프라이트를 세팅할 수 없습니다.");
		return;
	}

	m_Renderer->SetSprite(_FileName);
	Transform.SetLocalPosition(_Position);
	m_Renderer->SetPivotType(_Type);
}


void Prop::SetSpriteRenderer(const PropParameter& _Parameter)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 스프라이트를 세팅할 수 없습니다.");
		return;
	}

	m_Renderer->SetSprite(_Parameter.FileName);
	Transform.SetLocalPosition(_Parameter.TransformLocalPosition);
	m_Renderer->SetPivotType(_Parameter.ImagePivotType);
}



#pragma region 애니메이션 생성

void Prop::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	int _Start /*= -1*/,
	int _End /*= -1*/,
	bool _Loop /*= true*/
)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 애니메이션을 생성하려고 했습니다.");
		return;
	}

 	m_Renderer->CreateAnimation(_AnimationName, _SpriteName, _Inter, _Start, _End, _Loop);
}


void Prop::ChangeAnimation(std::string_view _AnimationName)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 애니메이션을 생성하려고 했습니다.");
		return;
	}

	m_Renderer->ChangeAnimation(_AnimationName);
	m_Renderer->AutoSpriteSizeOn();
}

// 자동으로 AutoSize를 요청합니다.
void Prop::SetAutoSpriteSize(float _Ratio, bool _Value /*= true*/)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 사용할 수 없습니다.");
	}

	_Value ? m_Renderer->AutoSpriteSizeOn() : m_Renderer->AutoSpriteSizeOff();
	m_Renderer->SetAutoScaleRatio(_Ratio);
}

// 애니메이션을 만듭니다.
void Prop::CreateAutomatedAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	int _Start /*= -1*/,
	int _End /*= -1*/,
	bool _Loop /*= true*/,
	float _Raito /*= 1.0f*/
)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 사용할 수 없습니다.");
	}

	m_Renderer->CreateAnimation(_AnimationName, _SpriteName, _Inter, _Start, _End, _Loop);
	m_Renderer->ChangeAnimation(_AnimationName);
	m_Renderer->AutoSpriteSizeOn();
	m_Renderer->SetAutoScaleRatio(_Raito);
}

#pragma endregion

#pragma region 픽셀충돌

// 픽셀 충돌 맵을 만듭니다.
void Prop::CreatePixelCollisionRenderer()
{
	m_DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Back_);
	if (nullptr == m_DebugRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_DebugRenderer->Off();

	PixelRendererCheck = true;
}

void Prop::SetPixelSprite(std::string_view _FileName)
{
	if (nullptr == m_DebugRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 스프라이트를 지정해줄 수 없습니다.");
		return;
	}

	m_DebugRenderer->SetSprite(_FileName);

	m_PixelFileName = _FileName;

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_FileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	m_PixelTextureScale = Texture->GetScale();
}


// 조정된* 위치에 픽셀 데이터를 반환해줍니다.
// * : GameEngineTexture::GetColor는 텍스처에게 내가 원하는 위치의 픽셀 데이터를 달라고 요구합니다.
//		이러한 특성 때문에 텍스처를 사용하는 객체의 위치가 이동해도 GetColor에서 주는 데이터 위치는 항상 같습니다.
//		따라서 객체가 이동한 거리만큼 빼줄 필요가 있습니다.
GameEngineColor Prop::GetColor(const float4& _Position, GameEngineColor _DefaultColor /*= { 255, 255, 255, 255 }*/)
{
	GameEngineColor ReturnValue;

	if ("" == m_PixelFileName)
	{
		MsgBoxAssert("지정해둔 파일이 없습니다.");
		return ReturnValue;
	}

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(m_PixelFileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return ReturnValue;
	}

	// 텍스처의 좌상단 원점과 NDC좌표의 원점의 거리를 구해야합니다.
	// 그리고 구한 거리를 얻어오고 싶은 위치에 빼줍니다.
	float4 HalfTexturePos = m_PixelTextureScale.Half();
	HalfTexturePos.X *= -1.0f;

	float4 MoveCheckPos = Transform.GetWorldPosition() + HalfTexturePos;


	float4 CheckPos =  _Position - MoveCheckPos;
	CheckPos.Y *= -1.0f;

	return Texture->GetColor(CheckPos, _DefaultColor);
}

#pragma endregion

void Prop::EnableDebugMode(bool _Value)
{
	if (_Value)
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->Off();
		}
		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->On();
		}
	}
	else
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->On();
		}
		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->Off();
		}
	}
}



void Prop::ActorRelease()
{
	m_Renderer = nullptr;
	m_DebugRenderer = nullptr;

	Death();
}