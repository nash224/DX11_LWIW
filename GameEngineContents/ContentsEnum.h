#pragma once



enum class EUPDATEORDER
{
	Player,
	Entity,
	Projectile,
	Objects,
	Portal,
	CameraControler,
	UIMagnaer,
	UIComponent,
	Fade,
};


enum class ERENDERORDER
{
	Back_,
	Ellie = 100,
	Object,
	UI,
	FadeObject,
};

enum class ETITLERENDERORDER
{
	Back_,
	Star,
	Moon,
	Water,
	Mountain_blur,
	Bridge_Down,
	Bridge_blur,
	Train_blur,
	Train_Light_blur,
	Water_blur,
	Cloud_0,
	Cloud_1,
	Cloud_2,
	Cloud_3,
	Cloud_4,
	Props_0,
	Props_1,
	TrainSmoke_Big,
	TrainSmoke_Mid,
	TrainSmoke_Small,
	Trains,
	Trains_Light,
	Bridge,
	Shadow,
	Tree,
	Logo,
};

enum class EWITCHHOUSEUPPERFLOOR
{
	BackPaint = 10,
	HouseComposition,
	HouseShadow,
	FirstObjects,
	SecondObjects,
	ThirdObjects,
	ForthObjects,
	FifthObjects,
	HouseFrame,
};


enum class EDOWNFLOORRENDERORDER
{
	BackPaint = 10,
	HouseComposition,
	HouseShadow,
	Objects,
	HouseFrame,
};


enum class EUI_RENDERORDERORDER
{
	Base = 100,
	Frame,
	Attachment,
	Component,
	Arrow,
};

enum class ECOLLISION
{
	Player,
	Entity,
	Portal,
};


enum class EDIRECTION
{
	CENTER,
	UP,
	RIGHTUP,
	RIGHT,
	RIGHTDOWN,
	DOWN,
	LEFTDOWN,
	LEFT,
	LEFTUP,
};
