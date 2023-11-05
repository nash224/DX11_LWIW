#pragma once
#include "RendererActor.h"
#include "PixelCollision.h"



// ���� : Props ����� �����޴� �Ϲ� ��ǰ�Դϴ�.
class NormalProp : public RendererActor, public GameEngineSerializerObject
{
public:
	// constrcuter destructer
	NormalProp();
	~NormalProp();

	// delete Function
	NormalProp(const NormalProp& _Other) = delete;
	NormalProp(NormalProp&& _Other) noexcept = delete;
	NormalProp& operator=(const NormalProp& _Other) = delete;
	NormalProp& operator=(NormalProp&& _Other) noexcept = delete;



	void Serializer(GameEngineSerializer& _Data) override;
	void DeSerializer(GameEngineSerializer& _Data) override;


	void SetPixelCollision(std::string_view _FileName);
	void ChangePixeldata(std::string_view _PixelName);

	bool GetPixelCheck();
	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = GameEngineColor::WHITE);

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void UpdateDebug();


protected:
	PixelCollision PixelCol;

	std::shared_ptr<GameEngineSpriteRenderer> m_DebugRenderer = nullptr;

	bool IsRendererOn = true;
	bool PixelRendererCheck = false;

};