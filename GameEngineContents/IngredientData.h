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

	// delete Function
	//IngredientData(const IngredientData& _Other) = delete;
	//IngredientData(IngredientData&& _Other) noexcept = delete;
	//IngredientData& operator=(const IngredientData& _Other) = delete;
	//IngredientData& operator=(IngredientData&& _Other) noexcept = delete;

protected:

private:
	std::string Name;
	std::string KoreanName;
	std::string SourceName;
	EBrewingMachineType BrewingMachine;
	unsigned int SourceCount;

};

