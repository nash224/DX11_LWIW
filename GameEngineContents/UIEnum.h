#pragma once


enum class ETOOLTYPE						// 도구 타입
{
	Gloves,
	FeaturePan,
	Dragonfly,
	Nothing,
	None
};


enum class EBrewingMachineType			// 추출기 타입
{
	Extractor,
	Roaster,
	Pot,
	None,
};

enum class EECOLOGYTYPE						// 생태계타입
{
	None,
	GreenForest,
	ForestPlains,
	ForestPlateau,
	ForestWaterfall,
	TopTree,
	Day,
	Night,
	AllDay,
};



enum class EDICTIONARYCATEGORY				// 사전
{
	None,
	CreaturePage,
	PlantPage,
	PotionPage,
	CandyPage,
};


enum class EBREWINGOPTION					// 레시피 옵션
{
	None,
	Easy,
	Normal,
	Hard,
	StirNone,
	StirRight,
	StirLeft,
	One,
	Two,
	Three,
	Four,
	Five,
};