#pragma once
#include "ContentsResource.h"





// Ό³Έν :
class ProductRecipeData final : public ContentsResource<ProductRecipeData>
{
public:
	// constrcuter destructer
	ProductRecipeData();
	~ProductRecipeData();


	ProductRecipeData(
		std::string _ProductName = "",
		std::string _KoreanName = "",
		ESTARTYPE _Star = ESTARTYPE::None,
		ELADLETYPE _Ladle = ELADLETYPE::None,
		EFIRETYPE _Fire = EFIRETYPE::None,
		std::string _Material1 = "",
		unsigned int _Material1Count = 0,
		std::string _Material2 = "",
		unsigned int _Material2Count = 0,
		std::string _Material3 = "",
		unsigned int _Material3Count = 0
	)
		:
		ProductName(_ProductName),
		KoreanName(_KoreanName),
		Star(_Star),
		Ladle(_Ladle),
		Fire(_Fire),
		Material1(_Material1),
		Material1Count(_Material1Count),
		Material2(_Material2),
		Material2Count(_Material2Count),
		Material3(_Material3),
		Material3Count(_Material3Count)
	{

	}

	// delete Function
	//ProductRecipeData(const ProductRecipeData& _Other) = delete;
	//ProductRecipeData(ProductRecipeData&& _Other) noexcept = delete;
	//ProductRecipeData& operator=(const ProductRecipeData& _Other) = delete;
	//ProductRecipeData& operator=(ProductRecipeData&& _Other) noexcept = delete;

protected:

public:
	std::string ProductName;
	std::string KoreanName;
	ESTARTYPE Star = ESTARTYPE::None;
	ELADLETYPE Ladle = ELADLETYPE::None;
	EFIRETYPE Fire = EFIRETYPE::None;
	std::string Material1;
	unsigned int Material1Count;
	std::string Material2;
	unsigned int Material2Count;
	std::string Material3;
	unsigned int Material3Count;
};

