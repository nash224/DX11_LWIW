#pragma once
#include "ContentsResource.h"

// ���� :
class IngredientData : public ContentsResource<IngredientData>
{
public:
	// constrcuter destructer
	IngredientData();
	~IngredientData();

	IngredientData(
		std::string_view _Name,
		std::string_view _KoreanName,
		std::string_view _SourceName,
		EBrewingMachineType _BrewingMachine = EBrewingMachineType::None,
		unsigned int _SourceCount = 0
	)
		:
		Name(_Name),
		KoreanName(_KoreanName),
		SourceName(_SourceName),
		BrewingMachine(_BrewingMachine),
		SourceCount(_SourceCount)
	{

	}

	// delete Function
	//IngredientData(const IngredientData& _Other) = delete;
	//IngredientData(IngredientData&& _Other) noexcept = delete;
	//IngredientData& operator=(const IngredientData& _Other) = delete;
	//IngredientData& operator=(IngredientData&& _Other) noexcept = delete;

public:
	std::string Name;
	std::string KoreanName;
	std::string SourceName;
	EBrewingMachineType BrewingMachine = EBrewingMachineType::None;
	unsigned int SourceCount = 0;

};

