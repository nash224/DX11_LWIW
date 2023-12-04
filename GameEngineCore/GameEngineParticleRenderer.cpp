#include "PreCompile.h"
#include "GameEngineParticleRenderer.h"
#include "GameEngineStructuredBuffer.h"

GameEngineParticleRenderer::GameEngineParticleRenderer()
{
}

GameEngineParticleRenderer::~GameEngineParticleRenderer()
{

}

void GameEngineParticleRenderer::Start()
{
	GameEngineRenderer::Start();

	UpdateUnit.GroupX = 128;

	std::vector<ParticleInfoData> Data;

	Data.resize(ParticleUpdateInfoValue.ParticleMaxCount);

	for (size_t i = 0; i < ParticleUpdateInfoValue.ParticleMaxCount; i++)
	{
		Data[i].CurTime = 0.0f;
		Data[i].MaxTime = 1.0f;
		Data[i].Dir = float4::ZERO;
		Data[i].RelativePos = float4::ZERO;
		Data[i].Speed = 100.0f;
		Data[i].iActive = 0;
	}

	UpdateUnit.SetComputeShader("ParticleUpdate_CS");

	UpdateUnit.ShaderResHelper.SetTexture("EngineNoise", "noise_03.jpg");
	UpdateUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	UpdateUnit.ShaderResHelper.SetConstantBufferLink("ParticleUpdateInfo", ParticleUpdateInfoValue);


	ParticleUpdateInfoValue.SpawnRange = 500.0f;

	// �����쿡 �ִ� �Լ��Դϴ�.
	// InterlockedAnd
	// ��ƼŬ������ ���� ���۴� �� ��ƼŬ ���������� ������ �־�� �Ѵٰ� ����
	// New�� ��������ϴ�.
	std::list<std::shared_ptr<GameEngineStructuredBuffer>> ParitcleInfoBuffers =
		UpdateUnit.ShaderResHelper.SetStructedNew("ParticleinfoBuffer", StructuredBufferType::UAV_INC, Data);
	std::list<std::shared_ptr<GameEngineStructuredBuffer>> ParticleShareBuffers =
		UpdateUnit.ShaderResHelper.SetStructedNew("ParticleShareBuffer", StructuredBufferType::UAV_INC, nullptr, sizeof(ParticleShareData), 1);

	// ���� ����Ʈ�� �˾Ƽ� �������� �ϴ°̴ϴ�
	GameEngineRenderer::SetMesh("PointMesh");
	GameEngineRenderer::SetMaterial("ParticleRender");

	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);

	Unit->SetRenderMode(RenderMode::Instancing);
	Unit->SetInstancingCount(ParticleUpdateInfoValue.ParticleMaxCount);
	Unit->ShaderResHelper.SetConstantBufferLink("ParticleUpdateInfo", ParticleUpdateInfoValue);
	Unit->ShaderResHelper.SetStructedBufferChange("ParticleInfoRenderBuffer", ParitcleInfoBuffers.front());
	ParticleShareBuffer = ParticleShareBuffers.front();

}

void GameEngineParticleRenderer::Update(float _DeltaTime)
{
	GameEngineRenderer::Update(_DeltaTime);

	TransformData Data = Transform.GetConstTransformDataRef();

	RenderBaseInfoValue;


	float fAliveTime = 1.f / Frequency;

	// �츰 RenderBaseValue���� �̹� ����ϰ� �����Ƿ� �ʿ䰡 ����. �����ð�
	// m_fAccTime += _DeltaTime;

	ParticleUpdateInfoValue.ObjectWorldPos = Transform.GetWorldPosition();

	// �����ð��� ��ƼŬ ���� �ð��� �Ѿ��
	if (fAliveTime < RenderBaseInfoValue.AccDeltaTime)
	{
		float f = (RenderBaseInfoValue.AccDeltaTime / fAliveTime);
		UINT iAliveCount = (UINT)f;
		RenderBaseInfoValue.AccDeltaTime = f - floorf(f);

		ParticleShareData share = { 10, };
		ParticleShareBuffer->SetData(&share, 1);
	}
	else
	{
		ParticleShareData share = {};
		ParticleShareBuffer->SetData(&share, 1);
	}


	UpdateUnit.GroupX = 128;

	// ������ ��ƼŬ �����͸� ��ǻƮ���̴��� ����ϰ�
	UpdateUnit.Excute();
}

void GameEngineParticleRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	GameEngineRenderer::Render(_Camera, _Delta);
}