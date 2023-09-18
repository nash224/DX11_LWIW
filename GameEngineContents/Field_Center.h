#pragma once
#include "PlayLevel.h"

// Ό³Έν :
class BackDrop_CenterField;
class Ellie;
class PortalObject;
class Field_Center : public PlayLevel
{
public:
	// constrcuter destructer
	Field_Center();
	~Field_Center();

	// delete Function
	Field_Center(const Field_Center& _Other) = delete;
	Field_Center(Field_Center&& _Other) noexcept = delete;
	Field_Center& operator=(const Field_Center& _Other) = delete;
	Field_Center& operator=(Field_Center&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


private:
	void LoadTexture();
	void LoadSprite();
	void LoadActor();
	void LoadGlobalUnit();
	void LoadPortalActor();

	void CameraSetting();

private:
	void UpdateLevelChange();
	void UpdatePortalObject();


private:
	void LevelActorRelease();
	void ReleaseSprite();
	void ReleaseTexture();


public:

private:
	std::shared_ptr<BackDrop_CenterField> m_BackDrop = nullptr;
	std::shared_ptr<Ellie> m_Ellie = nullptr;
	std::vector<std::shared_ptr<PortalObject>> vecPortalObject;

};

