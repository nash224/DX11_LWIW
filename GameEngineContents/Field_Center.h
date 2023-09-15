#pragma once
#include "PlayLevel.h"

// ���� :
class BackDrop_CenterField;
class Ellie;
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

private:
	void ActorRelease();
	void ReleaseSprite();
	void ReleaseTexture();


public:

private:
	std::shared_ptr<BackDrop_CenterField> m_BackDrop = nullptr;
	std::shared_ptr<Ellie> m_Ellie = nullptr;

};
