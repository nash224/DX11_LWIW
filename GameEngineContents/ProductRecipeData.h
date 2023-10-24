#pragma once
#include "ContentsResource.h"

class MaterialInfo
{
public:
	std::string MaterialName;
	unsigned int MaterialCount;
};


// 설명 : 재료가공 레시피 데이터입니다.
class ProductRecipeData final : public ContentsResource<ProductRecipeData>
{
public:
	// constrcuter destructer
	ProductRecipeData();
	~ProductRecipeData();


	ProductRecipeData(
		std::string _ProductName = "",
		std::string _KoreanName = "",
		EBREWING_DIFFICULTY _Star = EBREWING_DIFFICULTY::Hard,
		EBREWING_DIRECTION _Ladle = EBREWING_DIRECTION::StirNone,
		EBREWING_FIRE _Fire = EBREWING_FIRE::Three,
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
		Fire(_Fire)
	{
		Material.resize(3);
		Material[0].MaterialName = _Material1;
		Material[0].MaterialCount = _Material1Count;
		Material[1].MaterialName = _Material2;
		Material[1].MaterialCount = _Material2Count;
		Material[2].MaterialName = _Material3;
		Material[2].MaterialCount = _Material3Count;
	}


	// 레시피가 오른쪽에 와야합니다.
	bool operator==(const ProductRecipeData* _Other) const
	{
		if (_Other->Ladle != Ladle)
		{
			return false;
		}

		if (_Other->Fire != Fire)
		{
			return false;
		}

		std::vector<MaterialInfo> CheckMaterial;
		CheckMaterial.resize(3);
		for (size_t i = 0; i < CheckMaterial.size(); i++)
		{
			CheckMaterial[i] = Material[i];
		}
		

		for (size_t MCount = 0; MCount < _Other->Material.size(); MCount++)
		{
			bool IsCollect = false;

			for (size_t RCount = 0; RCount < CheckMaterial.size(); RCount++)
			{
				if (CheckMaterial[RCount].MaterialName == _Other->Material[MCount].MaterialName)
				{
					if (CheckMaterial[RCount].MaterialCount >= _Other->Material[MCount].MaterialCount)
					{
						CheckMaterial.erase(CheckMaterial.begin() + RCount);
						IsCollect = true;
						break;
					}
				}
			}

			if (false == IsCollect)
			{
				return false;
			}
		}

		return true;
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
	EBREWING_DIFFICULTY Star = EBREWING_DIFFICULTY::Easy;
	EBREWING_DIRECTION Ladle = EBREWING_DIRECTION::StirNone;
	EBREWING_FIRE Fire = EBREWING_FIRE::Three;
	std::vector<MaterialInfo> Material;
};

