#pragma once

enum class ECAMERAMODE
{
	None,
	Play,
	Fix,
	Editor,
};


// Ό³Έν :
class CameraControler : public GameEngineActor
{
	friend class ContentsLevel;

public:
	GameEngineActor* m_FocusActor;

private:
	GameEngineCamera* m_MainCamera;

public:
	// constrcuter destructer
	CameraControler();
	~CameraControler();

	// delete Function
	CameraControler(const CameraControler& _Other) = delete;
	CameraControler(CameraControler&& _Other) noexcept = delete;
	CameraControler& operator=(const CameraControler& _Other) = delete;
	CameraControler& operator=(CameraControler&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


public:
	void SetCameraMode(ECAMERAMODE _Mode);
	void SetLocalPostion(const float4& _Position);
	void SetFocusActor(GameEngineActor* _Actor);
	void SetBackDropScale(const float4& _Scale);

public:
	void Reset();

	void SetAutoInitialPosition(const float4& _Location);

public:
	float4 GetCameraMoveDistance() const;
	float4 GetCameraCurrentPostion() const;
	bool IsCameraMove() const;


private:
	void UpdateCameraMode(float _Delta);
	void UpdateCameraPlayMode(float _Delta);
	void UpdateCameraFixMode();
	void UpdateCameraEditorMode(float _Delta);


	void LockCamera(float4& _pCameraMovePos, const float4& _CurCameraPos);

private:
	void RenewCameraPosition();

private:
	float4 m_WinScale = float4::ZERO;	
	float4 m_BackScale = float4::ZERO;
	
private:
	struct CameraInfo
	{
	public:
		float4 PrevPosition;
		float4 CurPosition;
		float4 MoveDistance;
	};

	CameraInfo m_CameraInfo;
	ECAMERAMODE m_Mode;


	float m_EditorModeSpeed = 500.0f;

	const float m_SmoothingRatio = 0.035f;


};

