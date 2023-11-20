#pragma once
#include "UI_HoldingGauge.h"


// Ό³Έν :
class UI_ProcessB : public GameEngineActor
{
private:
	class ProcessBProductInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> ProductRenderer = nullptr;
		std::shared_ptr<GameEngineUIRenderer> NameRenderer = nullptr;
		std::string ProductName;
		std::string ProductKRName;


	};

	class ProcessBSourceInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> SourceRenderer = nullptr;
		std::shared_ptr<GameEngineUIRenderer> NameRenderer = nullptr;
		std::shared_ptr<GameEngineUIRenderer> SlashRenderer = nullptr;
		std::shared_ptr<GameEngineUIRenderer> SourceCntRenderer = nullptr;
		std::shared_ptr<GameEngineUIRenderer> NeedCntRenderer = nullptr;
		std::string ScrName;
		std::string ScrKRName;
		int NeedCount = 0;
		int ScrCount = 0;


	};

public:
	class UI_ProcessManager* ProcessManager = nullptr;

public:
	// constrcuter destructer
	UI_ProcessB();
	~UI_ProcessB();

	// delete Function
	UI_ProcessB(const UI_ProcessB& _Other) = delete;
	UI_ProcessB(UI_ProcessB&& _Other) noexcept = delete;
	UI_ProcessB& operator=(const UI_ProcessB& _Other) = delete;
	UI_ProcessB& operator=(UI_ProcessB&& _Other) noexcept = delete;

	void Init();

	void Open(std::string_view _ProductName, int _ScrCount);
	void Close();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void RendererSetting();
	void ProductInfoSetting(std::string_view _ProductName);
	void SourceInfoSetting(std::string_view _ProductName, int _ScrCount);


	void JuicyThis();
	void UpdateInput(float _Delta);
	void UpdateGauge(float _Delta);

private:
	std::shared_ptr<GameEngineUIRenderer> BaseRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> FrameRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PressFontRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PressButtonRenderer = nullptr;

	ProcessBProductInfo ProductInfo;
	ProcessBSourceInfo SourceInfo;

	bool IsJuicying = false;
	bool IsJustOpen = false;

	const float4 BlackColor = float4(0.1f, 0.1f, 0.1f, 1.0f);

	UI_HoldingGauge Gauge;
	float PressTime = 0.0f;
};

