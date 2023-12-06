#pragma once
#include "SkyLerp.h"

#include <GameEngineCore/GameEngineGUI.h>


class SkyGUI : public GameEngineGUIWindow
{
	friend class HouseSkyLerp;

private:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;

	void GUIStart();

private:
	HouseSkyLerp* SkyPtr = nullptr;

	std::vector<std::string> Items;
	std::vector<float> PlotData;

	int Curidx = 0;
	

};


// Ό³Έν :
class HouseSkyLerp : public SkyLerp
{
private:
	friend class SkyGUI;

public:
	// constrcuter destructer
	HouseSkyLerp();
	~HouseSkyLerp();

	// delete Function
	HouseSkyLerp(const HouseSkyLerp& _Other) = delete;
	HouseSkyLerp(HouseSkyLerp&& _Other) noexcept = delete;
	HouseSkyLerp& operator=(const HouseSkyLerp& _Other) = delete;
	HouseSkyLerp& operator=(HouseSkyLerp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void SetSkyData() override;
	void LoadData();

private:
	std::shared_ptr<SkyGUI> SkyGUIWindow;

};

