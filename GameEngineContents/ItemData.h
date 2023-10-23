#pragma once
#include "ContentsResource.h"

// Ό³Έν :
class ItemData : public ContentsResource<ItemData>
{
public:
	std::string Name;
	std::string KoreanName;
	EITEM_TYPE ItemType;



public:
	// constrcuter destructer
	ItemData();
	~ItemData();

	ItemData(std::string_view _Name, std::string_view _KoreanName, EITEM_TYPE _ItemType = EITEM_TYPE::None)
		: 
		Name(_Name),
		KoreanName(_KoreanName),
		ItemType(_ItemType)
	{

	}

	// delete Function
	//ItemData(const ItemData& _Other) = delete;
	//ItemData(ItemData&& _Other) noexcept = delete;
	//ItemData& operator=(const ItemData& _Other) = delete;
	//ItemData& operator=(ItemData&& _Other) noexcept = delete;

protected:

private:

};

