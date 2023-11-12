#pragma once
#include "UI_ToggleActor.h"





class DispensationSlotInfo
{
public:
	std::shared_ptr<GameEngineUIRenderer> ItemImg = nullptr;
	std::string ItemName = "";
	unsigned int ItemCount = 0;

};




// 설명 :
class UI_Dispensation : public GameEngineActor
{
public:
	class AlchemyPot* AlchemyPotPtr = nullptr;
	static UI_Dispensation* MainDispensation;

public:
	// constrcuter destructer
	UI_Dispensation();
	~UI_Dispensation();

	// delete Function
	UI_Dispensation(const UI_Dispensation& _Other) = delete;
	UI_Dispensation(UI_Dispensation&& _Other) noexcept = delete;
	UI_Dispensation& operator=(const UI_Dispensation& _Other) = delete;
	UI_Dispensation& operator=(UI_Dispensation&& _Other) noexcept = delete;

	// 초기화
	void Init();
	void RendererSetting();

	// 열기 닫기
	void Open();
	void Close();

	void Reset();

	bool SelectThis(std::string_view _ItemName, int _ItemCount);
	int ReturnEmptySlot();
	DispensationSlotInfo* FindSlot(std::string_view _ItemName);

	bool UnSelectThis(std::string_view _ItemName);
	void ClearSlotInfo();

	void Dispensation();
	bool CheckDispensation(const class ProductRecipeData& _Data);

	void PopDispensationMaterial(std::string_view _ItemName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateKey();

	void LowHit();
	void HighHit();
	void PrevStirOption();
	void NextStirOption();
	void ChangeAllDirectionReset();


private:
	std::shared_ptr<GameEngineUIRenderer> m_Base = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Frame = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Empty_Slot = nullptr;
	std::shared_ptr<GameEngineUIRenderer> fire_icon_1 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> fire_icon_2 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Fire_Gauge = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Fire_Gauge_Pin = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Direction_None = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Direction_CounterClockwise = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Direction_Clockwise = nullptr;

	std::vector<DispensationSlotInfo> m_DispensationSlotInfo;

	std::string CreatedProductName = "";

	EBREWING_FIRE CurFire = EBREWING_FIRE::Three;
	EBREWING_DIRECTION CurStir = EBREWING_DIRECTION::StirNone;

};

