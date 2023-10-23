#pragma once

// 방향키 및 조작
enum class ERENDER_PIVOT_LOCATION
{
	LeftTop,
	Center,
	RightBottom,
};


enum class EHORIZONTAL_KEY_STATE
{
	Left,
	Center,
	Right,
};


enum class EVERTICAL_KEY_STATE
{
	Up,
	Center,
	Down,
};



enum class EENTITY_TYPE
{
	Entity,
	Item,
	None,
};



enum class EITEM_TYPE
{
	Ingredient,
	RepairMaterial,
	Potion,
	Food,
	Recipe,
	Quest,
	None,
};


enum class ECOLLECTION_METHOD
{
	Sit,
	RootUp,
	MongSiri,
	Juicy,
	AlchemyPot,
	None,
};

enum class EMACHINETYPE
{
	Juicy,
	AlchemyPot,
	Roaster,

};