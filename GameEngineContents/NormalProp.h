#pragma once
#include "RendererActor.h"

// 설명 : Props 기능을 물려받는 일반 소품입니다.
class NormalProp : public RendererActor, public GameEngineSerializerObject
{
	friend class PlayLevel;

public:
	// constrcuter destructer
	NormalProp();
	~NormalProp();

	// delete Function
	NormalProp(const NormalProp& _Other) = delete;
	NormalProp(NormalProp&& _Other) noexcept = delete;
	NormalProp& operator=(const NormalProp& _Other) = delete;
	NormalProp& operator=(NormalProp&& _Other) noexcept = delete;

	void Init(int _Order = 0) override;

	void Serializer(GameEngineSerializer& _Data) override;
	void DeSerializer(GameEngineSerializer& _Data) override;


	void SetPixelCollision(std::string_view _FileName);

	void ChangePixeldata(std::string_view _PixelName);

	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer = nullptr;

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

};