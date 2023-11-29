#pragma once
#include "ContentsResource.h"


enum class EBIOLOGYDESCTYPE
{
	Observation,
	Method,
	Extra,
	None,
};

struct BiologyDESC
{
public:
	EBIOLOGYDESCTYPE DESCType;
	std::string DESC;
};

// Ό³Έν :
class BiologyData final : public ContentsResource<BiologyData>
{
private:
	struct BiologyDESC
	{
	public:
		EBIOLOGYDESCTYPE DESCType;
		std::string DESC;
	};

public:
	// constrcuter destructer
	BiologyData();
	~BiologyData();

	BiologyData(
		std::string_view _BiologyName,
		std::string_view _KoreanName,
		std::string_view _ItemName,
		ETOOLTYPE _GatherTool,
		EECOLOGYTYPE _EcologicalGroup,
		EECOLOGYTYPE _Habitat,
		EECOLOGYTYPE _AppearanceTime,
		const std::vector<BiologyDESC>& _DESCArray = {})
		:
		BiologyName(_BiologyName),
		KoreanName(_KoreanName),
		ItemName(_ItemName),
		GatherTool(_GatherTool),
		EcologicalGroup(_EcologicalGroup),
		Habitat(_Habitat),
		AppearanceTime(_AppearanceTime),
		DESCArray(_DESCArray)
	{

	}

	// delete Function
	/*BiologyData(const BiologyData& _Other) = delete;
	BiologyData(BiologyData&& _Other) noexcept = delete;
	BiologyData& operator=(const BiologyData& _Other) = delete;
	BiologyData& operator=(BiologyData&& _Other) noexcept = delete;*/

protected:

private:


public:
	std::string BiologyName;
	std::string KoreanName;
	std::string ItemName;
	ETOOLTYPE GatherTool = ETOOLTYPE::None;
	EECOLOGYTYPE EcologicalGroup = EECOLOGYTYPE::None;
	EECOLOGYTYPE Habitat = EECOLOGYTYPE::None;
	EECOLOGYTYPE AppearanceTime = EECOLOGYTYPE::None;
	std::vector<BiologyDESC> DESCArray;

};

