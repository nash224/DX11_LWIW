#pragma once

enum class ECAMERAMODE
{
	None,
	Play,
	Fix,
	Editor,
};


// 설명 :
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

	float4 GetCameraWorldPosition() const;

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
	void LockCamera(float4& _pCameraMovePos, const float4& _CurCameraPos);

	void UpdateCameraFixMode();
	void UpdateCameraEditorMode(float _Delta);



private:
	void RenewCameraPosition();

private:
	float4 m_WinScale = float4::ZERO;				// 디폴트 값
	float4 m_BackScale = float4::ZERO;				// 카메라 이동 배경 값
	
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


	float m_EditorModeSpeed = 200.0f;

	const float m_SmoothingRatio = 0.035f;
	const float CameraDepth = -500.0f;


};

