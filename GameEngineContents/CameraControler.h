#pragma once


enum class ECAMERAMODE
{
	None,
	Play,
	Fix,
	Cinematic,
	Editor,
};


// Ό³Έν :
class CameraControler : public GameEngineActor
{
	friend class ContentsLevel;

private:
	struct CameraInfo
	{
	public:
		float4 PrevPosition;
		float4 CurPosition;
		float4 MoveDistance;
	};

private:
	GameEngineActor* FocusActorPointer = nullptr;
	GameEngineCamera* MainCameraPointer = nullptr;

public:
	// constrcuter destructer
	CameraControler();
	~CameraControler();

	// delete Function
	CameraControler(const CameraControler& _Other) = delete;
	CameraControler(CameraControler&& _Other) noexcept = delete;
	CameraControler& operator=(const CameraControler& _Other) = delete;
	CameraControler& operator=(CameraControler&& _Other) noexcept = delete;


	void SetCameraMode(ECAMERAMODE _Mode);
	void SetLocalPostion(const float4& _Position);
	void SetFocusActor(GameEngineActor* _Actor);
	void SetBackDropScale(const float4& _Scale);

	void AddCameraPos(const float4& _Position);
	void SetCameraPos(const float4& _Position);

	float4 GetCameraWorldPosition() const;

	void Reset();
	float4 AdjustCameraInitialPosition(const float4& _ActorPos);
	void SetAutoInitialPosition(const float4& _ActorPos);

	float4 GetCameraMoveDistance() const;
	float4 GetCameraCurrentPostion() const;
	bool IsCameraMove() const;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void UpdateCameraMode(float _Delta);
	void UpdatePlayMode(float _Delta);
	void UpdateCinematicMode(float _Delta);
	void LockCamera(float4& _pCameraMovePos, const float4& _CurCameraPos) const;

	void UpdateFixMode();
	void UpdateEditorMode(float _Delta);
	void RenewCameraPosition();


private:
	float4 BackScale = float4::ZERO;

	CameraInfo CameraPosInfo;
	ECAMERAMODE CameraMode;

};

