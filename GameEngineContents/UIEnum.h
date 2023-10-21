#pragma once


enum class ETOOLTYPE						// 도구 타입
{
	Gloves,
	Dragonfly,
	FeaturePan,
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

enum class EBREWING_DIRECTION
{
	StirRight,
	StirNone,
	StirLeft,
};


enum class EBREWING_FIRE
{
	One,
	Two,
	Three,
	Four,
	Five,
};

enum class EBREWING_DIFFICULTY					// 레시피 옵션
{
	Easy,
	Normal,
	Hard,
};