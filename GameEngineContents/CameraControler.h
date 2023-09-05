#pragma once

enum class ECAMERAMODE
{
	None,
	Movie,
	Cinematic,
	Play,
	Setting,
	Editor,
};


// Ό³Έν :
class CameraControler : public GameEngineActor
{
public:
	GameEngineCamera* m_MainCamera;
	GameEngineActor* m_FocusActor;


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

public:
	const float4& GetCameraMoveDistance() const;
	const float4& GetCameraCurrentPostion() const;

private:
	void RenewCameraPosition();

private:
	void UpdateCameraMode(float _Delta);
	void UpdateCameraEditorMode(float _Delta);


public:
	struct CameraInfo
	{
	public:
		float4 PrevPosition;
		float4 CurPosition;
		float4 MoveDistance;
	};

	
private:
	CameraInfo m_CameraInfo;
	ECAMERAMODE m_Mode;
	float m_CameraSpeed;



};

