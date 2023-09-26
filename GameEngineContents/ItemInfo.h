#pragma once
#include "UIEnum.h"
#include <string>
#include <map>




struct BiologyData
{
public:
	std::string BiologyName;
	std::string KoreanName;
	std::string ItemName;
	ETOOLTYPE GatherTool;
	EECOLOGYTYPE EcologicalGroup ;
	EECOLOGYTYPE Habitat = EECOLOGYTYPE::None;
	EECOLOGYTYPE AppearanceTime = EECOLOGYTYPE::None;

	BiologyData(
		std::string _BiologyName = "",
		std::string _KoreanName = "",
		std::string _ItemName ="",
		ETOOLTYPE _GatherTool = ETOOLTYPE::Max,
		EECOLOGYTYPE _EcologicalGroup = EECOLOGYTYPE::None,
		EECOLOGYTYPE _Habitat = EECOLOGYTYPE::None,
		EECOLOGYTYPE _AppearanceTime = EECOLOGYTYPE::None
	)
		: 
		BiologyName(_BiologyName),
		KoreanName(_KoreanName),
		ItemName(_ItemName),
		GatherTool(_GatherTool),
		EcologicalGroup(_EcologicalGroup),
		Habitat(_Habitat),
		AppearanceTime(_AppearanceTime)
	{

	}
};


struct ProductData
{
public:
	std::string BiologyName;
	std::string KoreanName;
	std::string ItemName;
	ETOOLTYPE GatherTool;
	EECOLOGYTYPE EcologicalGroup;
	EECOLOGYTYPE Habitat = EECOLOGYTYPE::None;
	EECOLOGYTYPE AppearanceTime = EECOLOGYTYPE::None;

	ProductData(
		std::string _BiologyName = "",
		std::string _KoreanName = "",
		std::string _ItemName = "",
		ETOOLTYPE _GatherTool = ETOOLTYPE::Max,
		EECOLOGYTYPE _EcologicalGroup = EECOLOGYTYPE::None,
		EECOLOGYTYPE _Habitat = EECOLOGYTYPE::None,
		EECOLOGYTYPE _AppearanceTime = EECOLOGYTYPE::None
	)
		:
		BiologyName(_BiologyName),
		KoreanName(_KoreanName),
		ItemName(_ItemName),
		GatherTool(_GatherTool),
		EcologicalGroup(_EcologicalGroup),
		Habitat(_Habitat),
		AppearanceTime(_AppearanceTime)
	{

	}
};


// Ό³Έν :
class ItemInfo
{
public:
	// constrcuter destructer
	ItemInfo();
	~ItemInfo();

	// delete Function
	ItemInfo(const ItemInfo& _Other) = delete;
	ItemInfo(ItemInfo&& _Other) noexcept = delete;
	ItemInfo& operator=(const ItemInfo& _Other) = delete;
	ItemInfo& operator=(ItemInfo&& _Other) noexcept = delete;

	//std::string BiologyName = "";
	//std::string ImgFileName = "";
	//std::string ItemName = "";
	//ETOOLTYPE GatherTool = ETOOLTYPE::None;
	//EECOLOGYTYPE EcologicalGroup = EECOLOGYTYPE::WitchPlace;
	//EECOLOGYTYPE Habitat = EECOLOGYTYPE::None;
	//EECOLOGYTYPE AppearanceTime = EECOLOGYTYPE::None;
	static void CreateData(const BiologyData& _Info);
	static const std::shared_ptr<BiologyData>& GetBiologyInfo(std::string_view _BiologyName);

private:
	static const std::shared_ptr<BiologyData>& FindBiologyInfo(std::string_view _BiologyName);


private:
	static std::map<std::string, std::shared_ptr<BiologyData>> BiologyInfo;
	static std::map<std::string, ProductData> ProductInfo;

};

