#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class Ellie;
class PortalObject;
class PlayLevel : public ContentsLevel
{
public:
	static bool PixelDebugMode;

public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	

private:


protected:
	void InitPlayLevel();

protected:
	std::shared_ptr<Ellie> m_Ellie = nullptr;


protected:
	bool LevelInitCheck = false;

	std::vector<std::shared_ptr<PortalObject> >vecPortalObject;
};