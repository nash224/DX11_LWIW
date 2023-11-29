#include "PreCompile.h"
#include "ProductRecipeData.h"

ProductRecipeData::ProductRecipeData()
{
}

ProductRecipeData::~ProductRecipeData()
{
}

ProductRecipeData::ProductRecipeData(
	const std::vector<MaterialInfo>& MaterialArray, 
	EBREWING_DIFFICULTY _Star, EBREWING_DIRECTION _Ladle, EBREWING_FIRE _Fire, 
	std::string_view _ProductName, std::string_view _KoreanName,
	const std::vector<ProduectDESC>& _DESCArray)
	:
	ProductName(_ProductName),
	KoreanName(_KoreanName),
	Star(_Star),
	Ladle(_Ladle),
	Fire(_Fire),
	Material(MaterialArray),
	DESC(_DESCArray)
{
}

unsigned int ProductRecipeData::GetNeedMaterialCount(std::string_view _ProductName, std::string_view _MaterialName)
{
	std::weak_ptr<ProductRecipeData> recipe = Find(_ProductName);
	if (recipe.expired())
	{
		MsgBoxAssert("��ϵ��� ���� �����Ǹ� �����Ϸ� �߽��ϴ�.");
		return 0;
	}

	for (const MaterialInfo& Info : recipe.lock()->Material)
	{
		if (Info.MaterialName == _MaterialName)
		{
			return Info.MaterialCount;
		}
	}

	return 0;
}
