#pragma once
#include "ContentsResource.h"

// Ό³Έν :
class IngredientData : public ContentsResource<IngredientData>
{
public:
	// constrcuter destructer
	IngredientData();
	~IngredientData();

	IngredientData(
		std::string _Name,
		std::string _KoreanName,
		std::string _SourceName,
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

	//bool operator==(const IngredientData& _Other) const
	//{
	//	if (true)
	//	{

	//	}

	//	return ReturnValue;
	//}


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

