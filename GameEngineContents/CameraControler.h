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

public:
	void Reset();

public:
	float4 GetCameraMoveDistance() const;
	float4 GetCameraCurrentPostion() const;
	bool IsCameraMove() const;

private:
	void RenewCameraPosition();

private:
	void UpdateCameraMode(float _Delta);
	void UpdateCameraPlayMode(float _Delta);
	void UpdateCameraEditorMode(float _Delta);


private:
	float4 m_WinScale = float4::ZERO;	
	
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



};

