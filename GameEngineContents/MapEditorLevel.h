#pragma once
#include "ContentsLevel.h"

#define OneQuater 90.0f


// Ό³Έν :
class MapEditorLevel : public ContentsLevel
{
public:
	std::shared_ptr<class MouseManager> m_MouseManager = nullptr;
	class RendererActor* SelectActor = nullptr;


public:
	// constrcuter destructer
	MapEditorLevel();
	~MapEditorLevel();

	// delete Function
	MapEditorLevel(const MapEditorLevel& _Other) = delete;
	MapEditorLevel(MapEditorLevel&& _Other) noexcept = delete;
	MapEditorLevel& operator=(const MapEditorLevel& _Other) = delete;
	MapEditorLevel& operator=(MapEditorLevel&& _Other) noexcept = delete;


	bool IsFlip = false;
	int _SelectDepth = 0;
	float _RendererHeight = 0.0f;

	std::string _SelcetSprite = "";
	std::string _SelcetPixelSprite = "";

	float4 m_BaseScale = float4::ZERO;
	float4 m_SaveLocation = float4::ZERO;


	std::shared_ptr<GameEngineActor> m_MapBaseActor;
	std::shared_ptr<GameEngineSpriteRenderer> m_MapBaseRenderer;


	void CenterFieldMapSetting();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void LoadResouces();
	void ReleaseResouces();


private:
	void UpdateMapEditor(float _Delta);


	bool ClickCreateActor();
	bool ClickForSelectActor();

	bool MoveSelectActor();
	bool RotateSelectActor();
	bool EraseSelectActor();
	bool PlaceThis();


};

