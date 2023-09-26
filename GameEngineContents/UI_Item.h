#pragma once
#include "UIEnum.h"

struct ItemInfo
{
public:
	std::string Name = "";
	ETOOLTYPE GatherTool = ETOOLTYPE::None;
	EECOLOGYTYPE AppearanceTime = EECOLOGYTYPE::None;
	std::string ImgFileName = "";
};


// Ό³Έν :
class UI_Item : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Item();
	~UI_Item();

	// delete Function
	UI_Item(const UI_Item& _Other) = delete;
	UI_Item(UI_Item&& _Other) noexcept = delete;
	UI_Item& operator=(const UI_Item& _Other) = delete;
	UI_Item& operator=(UI_Item&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::map<std::string, ItemInfo> ItemInfo;

};

