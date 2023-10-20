#include "PreCompile.h"
#include "Props.h"

Props::Props() 
{
}

Props::~Props() 
{
}


void Props::Start()
{
}

void Props::Update(float _Delta)
{
}

void Props::Release()
{
}

void Props::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void Props::LevelEnd(class GameEngineLevel* _NextLevel)
{
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void Props::UpdateDebug()
{
	if (true == IsRendererOn && true == PlayLevel::PixelDebugMode)
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->Off();
		}

		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->On();
		}

		IsRendererOn = false;
	}

	if (false == IsRendererOn && false == PlayLevel::PixelDebugMode)
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->On();
		}

		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->Off();
		}

		IsRendererOn = true;
	}
}



bool Props::GetPixelCheck()
{
	return PixelRendererCheck;
}

void Props::SetPixelCollision(std::string_view _FileName)
{
	m_DebugRenderer = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_DebugRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_DebugRenderer->Off();
	m_DebugRenderer->SetSprite(_FileName);
	m_PixelFileName = _FileName;

	PixelRendererCheck = true;
}


// 조정된* 위치에 픽셀 데이터를 반환해줍니다.
// * : GameEngineTexture::GetColor는 텍스처에게 내가 원하는 위치의 픽셀 데이터를 달라고 요구합니다.
//		이러한 특성 때문에 텍스처를 사용하는 객체의 위치가 이동해도 GetColor에서 주는 데이터 위치는 항상 같습니다.
//		따라서 객체가 이동한 거리만큼 빼줄 필요가 있습니다.
GameEngineColor Props::GetColor(const float4& _Position, GameEngineColor _DefaultColor /*= GameEngineColor::WHITE*/)
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
	float4 HalfTexturePos = Texture->GetScale().Half();
	HalfTexturePos.X *= -1.0f;

	float4 MoveCheckPos = Transform.GetLocalPosition() + HalfTexturePos;


	float4 CheckPos = _Position - MoveCheckPos;
	CheckPos.Y *= -1.0f;

	return Texture->GetColor(CheckPos, _DefaultColor);
}