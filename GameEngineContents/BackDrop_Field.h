#pragma once
#include "BackDrop_PlayLevel.h"

#include "TimeManager.h"
#include "Bush.h"


// 설명 :
class BackDrop_Field : public BackDrop_PlayLevel
{
public:
	// constrcuter destructer
	BackDrop_Field();
	~BackDrop_Field();

	// delete Function
	BackDrop_Field(const BackDrop_Field& _Other) = delete;
	BackDrop_Field(BackDrop_Field&& _Other) noexcept = delete;
	BackDrop_Field& operator=(const BackDrop_Field& _Other) = delete;
	BackDrop_Field& operator=(BackDrop_Field&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	
	void CreateBush(const float4& _Position, EBUSHTYPE _Type);
	void CreateWitchFlower(const float4& _Position);
	void CreateSilverStarFlower(const float4& _Position);
	void CreateBranchTree(const float4& _Position);
	void CreateMongSiriPopulation(int _MongsiriCount, const float4& _HolePosition, const float4& _MongsiriPosition);
	void CreateFlowerBird(const float4& _Position);
	void CreatePumpkinTerrier(const float4& _Position);


	void LeavePopulation();
	void LeaveFlowerBird();


	template<typename EntityType>
	void ReleaseEntity()
	{
		const std::vector<std::shared_ptr<EntityType>>& EntityGroup = GetLevel()->GetObjectGroupConvert<EntityType>(EUPDATEORDER::Entity);
		for (const std::shared_ptr<EntityType>& Entity : EntityGroup)
		{
			if (nullptr == Entity)
			{
				MsgBoxAssert("아무것도 들어있지 않습니다");
				return;
			}

			Entity->Death();
		}
	}

	void ReleaseItemDrop();
	void ReleaseMongSiriPopulation();

	virtual void DisappearDayCreature() = 0;
	virtual void AppearNightCreature() = 0;
	virtual void ReleaseAllCreature() = 0;
	virtual void CreateCreatureWhenDayChange() = 0;

private:
	void StateSetting();

	void StartDay(GameEngineState* _Parent);
	void StartNight(GameEngineState* _Parent);
	void StartDayChange(GameEngineState* _Parent);

	void UpdateDay(float _Delta, GameEngineState* _Parent);
	void UpdateNight(float _Delta, GameEngineState* _Parent);

	void EndDay(GameEngineState* _Parent);
	void EndNight(GameEngineState* _Parent);

	void DetectNight();

private:
	GameEngineState FieldState;
	bool isNight = false;

	int FieldDay = -1;

};

