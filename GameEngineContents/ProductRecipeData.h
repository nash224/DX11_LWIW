#pragma once
#include "ContentsResource.h"

class MaterialInfo
{
public:
	std::string MaterialName;
	unsigned int MaterialCount = 0;
};


// 설명 : 재료가공 레시피 데이터입니다.
class ProductRecipeData final : public ContentsResource<ProductRecipeData>
{
public:
	struct MaterialInfo
	{
		std::string MaterialName;
		unsigned int MaterialCount = 0;
	};

public:
	// constrcuter destructer
	ProductRecipeData();
	~ProductRecipeData();


	ProductRecipeData(
		const std::vector<MaterialInfo>& _MaterialArray,
		EBREWING_DIFFICULTY _Star,
		EBREWING_DIRECTION _Ladle,
		EBREWING_FIRE _Fire, 
		std::string_view _ProductName = "", 
		std::string_view _KoreanName = "",
		std::string_view _Content = ""
	);

	ProductRecipeData(const ProductRecipeData& _Other) = default;
	ProductRecipeData(ProductRecipeData&& _Other) noexcept = default;
	ProductRecipeData& operator=(const ProductRecipeData& _Other) = default;
	ProductRecipeData& operator=(ProductRecipeData&& _Other) noexcept = default;


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
		for (int i = 0; i < CheckMaterial.size(); i++)
		{
			CheckMaterial[i] = Material[i];
		}


		for (int MCount = 0; MCount < _Other->Material.size(); MCount++)
		{
			bool IsCollect = false;

			for (int RCount = 0; RCount < CheckMaterial.size(); RCount++)
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

	static unsigned int GetNeedMaterialCount(std::string_view _ProductName, std::string_view _MaterialName);

protected:

public:
	std::string ProductName;
	std::string KoreanName;
	EBREWING_DIFFICULTY Star = EBREWING_DIFFICULTY::Easy;
	EBREWING_DIRECTION Ladle = EBREWING_DIRECTION::StirNone;
	EBREWING_FIRE Fire = EBREWING_FIRE::Three;
	std::vector<MaterialInfo> Material;
	std::string Content;
};

