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
	Source,
	Ingredient,
	RepairMaterial,
	Potion,
	Food,
	Recipe,
	Quest,
	Tool,
	None,
};


enum class EINTERACTIONTYPE
{
	Sit,
	RootUp,
	MongSiri,
	Juicy,
	AlchemyPot,
	Lift,
	None,
};

enum class EMACHINETYPE
{
	Juicy,
	AlchemyPot,
	Roaster,

};



enum class ECONVERSATIONENTITY
{
	NPC,
	Ellie,
	Virgil,
	None,
};