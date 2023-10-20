#pragma once
#include "BackDrop.h"

enum class DayStatus
{
	Day,
	Night,
	None,
};


// ���� :
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

	// ��ü ����
	void CreatePropInCurBackDrop(ERENDERDEPTH _RenderDepth, std::string_view _SpriteName, const float4& _Position, const float _Depth = 0.0f);

	// �����
	void EnableDebugMode(bool _Value);

	// Ž��
	bool IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor);

	// ZOrder
	float ZSort(const float _PositionY) const;

	// ������
	void CreateItem(std::string_view _ItemName, const float4& _Position = float4::ZERO, const int _Stack = 1, const float _FallYPosition = 0.0f);

	std::list<std::shared_ptr<class LootedItem>>& GetLootedItemList();
	std::list<std::shared_ptr<class StaticEntity>>& GetStaticEntityList();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	// Scenery, Prop �ؽ�ó �ܿ� �ڽĿ��� ���ְ� ���� �۾��� ������
	virtual void EnableBackDropElemnetDebugMode(bool _Value) {}

protected:
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> m_BackProp;
	std::vector<std::shared_ptr<class Prop>> vecPixelProps;
	std::vector<std::shared_ptr<class Props>> PixelVec;
	std::list<std::shared_ptr<class StaticEntity>> StaticEntityList;
	std::list<std::shared_ptr<class LootedItem>> LootedItemList;
	std::vector<std::shared_ptr<class PortalObject>> vecPortalObject;

protected:
	DayStatus m_UpdateDayTime = DayStatus::None;

};

