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

	// 재료가 왼쪽에 
	bool operator==(const ProductRecipeData* _Recipe) const
	{
		if (nullptr == _Recipe)
		{
			MsgBoxAssert("레시피가 존재하지 않습니다.");
			return false;
		}

		if (_Recipe->Ladle != Ladle)
		{
			return false;
		}

		if (_Recipe->Fire != Fire)
		{
			return false;
		}

		if (_Recipe->Material.size() != Material.size())
		{
			return false;
		}

		std::vector<MaterialInfo> CheckMaterial;
		CheckMaterial.resize(Material.size());
		for (int i = 0; i < CheckMaterial.size(); i++)
		{
			CheckMaterial[i] = Material[i];
		}


		for (int MCount = 0; MCount < _Recipe->Material.size(); MCount++)
		{
			bool IsCollect = false;

			for (int RCount = 0; RCount < CheckMaterial.size(); RCount++)
			{
				if (CheckMaterial[RCount].MaterialName == _Recipe->Material[MCount].MaterialName)
				{
					if (CheckMaterial[RCount].MaterialCount >= _Recipe->Material[MCount].MaterialCount)
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

