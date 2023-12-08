#pragma once
#include "RendererActor.h"

// Ό³Έν :
class GroundRenderUnit : public RendererActor, public GameEngineSerializerObject
{
public:
	// constrcuter destructer
	GroundRenderUnit();
	~GroundRenderUnit();

	// delete Function
	GroundRenderUnit(const GroundRenderUnit& _Other) = delete;
	GroundRenderUnit(GroundRenderUnit&& _Other) noexcept = delete;
	GroundRenderUnit& operator=(const GroundRenderUnit& _Other) = delete;
	GroundRenderUnit& operator=(GroundRenderUnit&& _Other) noexcept = delete;



	void Serializer(GameEngineSerializer& _Data) override;
	void DeSerializer(GameEngineSerializer& _Data) override;

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

