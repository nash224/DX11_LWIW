#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class MapEditorLevel : public ContentsLevel
{
public:
	std::shared_ptr<class MouseManager> m_MouseManager = nullptr;

public:
	// constrcuter destructer
	MapEditorLevel();
	~MapEditorLevel();

	// delete Function
	MapEditorLevel(const MapEditorLevel& _Other) = delete;
	MapEditorLevel(MapEditorLevel&& _Other) noexcept = delete;
	MapEditorLevel& operator=(const MapEditorLevel& _Other) = delete;
	MapEditorLevel& operator=(MapEditorLevel&& _Other) noexcept = delete;

	std::string _SelcetSprite = "";
	float _RendererDepth = 0.0f;

	float4 m_BaseScale = float4::ZERO;


	std::shared_ptr<GameEngineActor> m_MapBaseActor;
	std::shared_ptr<GameEngineSpriteRenderer> m_MapBaseRenderer;


	float CalculateDepth(const float _PositionY) const;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateMapEditor(float _Delta);



};

