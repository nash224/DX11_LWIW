#pragma once
#include "BackDrop.h"

// ���� :
class BackDrop_PlayLevel : public BackDrop
{
	friend class Ellie;

public:
	static BackDrop_PlayLevel* MainBackDrop;

public:
	// constrcuter destructer
	BackDrop_PlayLevel();
	~BackDrop_PlayLevel();

	// delete Function
	BackDrop_PlayLevel(const BackDrop_PlayLevel& _Other) = delete;
	BackDrop_PlayLevel(BackDrop_PlayLevel&& _Other) noexcept = delete;
	BackDrop_PlayLevel& operator=(const BackDrop_PlayLevel& _Other) = delete;
	BackDrop_PlayLevel& operator=(BackDrop_PlayLevel&& _Other) noexcept = delete;

	void EnableDebugMode(bool _Value);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


protected:
	void Init();

protected:
	// Scenery, Prop �ؽ�ó �ܿ� �ڽĿ��� ���ְ� ���� �۾��� ������
	virtual void EnableBackDropElemnetDebugMode(bool _Value) {}

private:
	// Ž��
	bool IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

public:
	void CreateItem(std::string_view _ItemName, const float4& _Position = float4::ZERO, const int _Stack = 1);


public:
	// �ʱ�ȭ
	void ActorRelease() override;

protected:
	std::vector<std::shared_ptr<class Prop>> vecPixelProps;
	std::vector<std::shared_ptr<class StaticEntity>> vecStaticEntity;
	std::vector<std::shared_ptr<class PortalObject>> vecPortalObject;
	std::list<std::shared_ptr<class LootedItem>> LootedItemList;

};

