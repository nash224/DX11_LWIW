#include "PreCompile.h"
#include "ProductRecipeData.h"

ProductRecipeData::ProductRecipeData()
{
}

ProductRecipeData::~ProductRecipeData()
{
}

ProductRecipeData::ProductRecipeData(const std::vector<MaterialInfo>& MaterialArray, EBREWING_DIFFICULTY _Star, EBREWING_DIRECTION _Ladle, EBREWING_FIRE _Fire, std::string_view _ProductName, std::string_view _KoreanName)
	:
	ProductName(_ProductName),
	KoreanName(_KoreanName),
	Star(_Star),
	Ladle(_Ladle),
	Fire(_Fire),
	Material(MaterialArray)
{
}
