#pragma once




// 설명 :
class UI_ProcessB : public GameEngineActor
{
private:
	class ProcessBProductInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> ProductRenderer = nullptr;
		std::string ProductName;
		std::string ProductKRName;


	};

	class ProcessBSourceInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> SourceRenderer = nullptr;
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
	void RendererSetting();

	// Open 기능
	void Open(std::string_view _ProductName, int _ScrCount);
	void ProductInfoSetting(std::string_view _ProductName);
	void SourceInfoSetting(std::string_view _ProductName, int _ScrCount);

	// Close 기능
	void Close();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void JuicyThis();

private:
	void UpdateInput();

private:
	std::shared_ptr<GameEngineUIRenderer> BaseRenderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> FrameRenderer = nullptr;

	ProcessBProductInfo ProductInfo;
	ProcessBSourceInfo SourceInfo;

	bool IsJuicying = false;
	bool IsJustOpen = false;


};

