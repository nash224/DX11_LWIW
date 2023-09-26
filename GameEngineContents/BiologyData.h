#pragma once
#include "ContentsResource.h"






// Ό³Έν :
class BiologyData : public ContentsResource<BiologyData>
{
public:
	// constrcuter destructer
	BiologyData();
	~BiologyData();

	BiologyData(
		std::string _BiologyName = "",
		std::string _KoreanName = "",
		std::string _ItemName = "",
		ETOOLTYPE _GatherTool = ETOOLTYPE::Max,
		EECOLOGYTYPE _EcologicalGroup = EECOLOGYTYPE::None,
		EECOLOGYTYPE _Habitat = EECOLOGYTYPE::None,
		EECOLOGYTYPE _AppearanceTime = EECOLOGYTYPE::None
	)
		:
		BiologyName(_BiologyName),
		KoreanName(_KoreanName),
		ItemName(_ItemName),
		GatherTool(_GatherTool),
		EcologicalGroup(_EcologicalGroup),
		Habitat(_Habitat),
		AppearanceTime(_AppearanceTime)
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
	ETOOLTYPE GatherTool;
	EECOLOGYTYPE EcologicalGroup;
	EECOLOGYTYPE Habitat = EECOLOGYTYPE::None;
	EECOLOGYTYPE AppearanceTime = EECOLOGYTYPE::None;

};

