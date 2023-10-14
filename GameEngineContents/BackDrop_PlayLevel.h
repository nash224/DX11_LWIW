#pragma once
#include "BackDrop.h"

enum class DayStatus
{
	Day,
	Night,
	None,
};


// 설명 :
class BackDrop_PlayLevel : public BackDrop
{
	friend class Ellie;

public:
	static BackDrop_PlayLevel* MainBackDrop;

protected:
	static DayStatus  TimeOfDay;

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

	// 탐색
	bool IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor);
	float ZSort(const float _PositionY) const;

	void CreateItem(std::string_view _ItemName, const float4& _Position = float4::ZERO, const int _Stack = 1);

	std::list<std::shared_ptr<class LootedItem>>& GetLootedItemList();
	std::list<std::shared_ptr<class StaticEntity>>& GetStaticEntityList();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


protected:
	void Init();

protected:
	// Scenery, Prop 텍스처 외에 자식에서 해주고 싶은 작업이 있을때
	virtual void EnableBackDropElemnetDebugMode(bool _Value) {}

public:
	// 초기화
	void ActorRelease() override;

protected:
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> FlooringVec;
	std::vector<std::shared_ptr<class Prop>> vecPixelProps;
	std::vector<std::shared_ptr<class PortalObject>> vecPortalObject;
	std::list<std::shared_ptr<class StaticEntity>> StaticEntityList;
	std::list<std::shared_ptr<class LootedItem>> LootedItemList;

protected:
	DayStatus  m_UpdateDayTime = DayStatus::None;

};

