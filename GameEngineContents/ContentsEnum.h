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


enum class ERENDERDEPTH
{
	FadeObject = -1000,
	Object = 0,
	RootedItem = 1000,
	ObjectShadow,
	Back_,
};

enum class ETITLERENDERDEPTH
{
	Logo,
	Tree,
	Shadow,
	Bridge,
	Trains_Light,
	Trains,
	TrainSmoke_Small,
	TrainSmoke_Mid,
	TrainSmoke_Big,
	Props_0,
	Props_1,
	Cloud_4,
	Cloud_3,
	Cloud_2,
	Cloud_1,
	Cloud_0,
	Water_blur,
	Train_Light_blur,
	Train_blur,
	Bridge_blur,
	Bridge_Down,
	Mountain_blur,
	Water,
	Moon,
	Star,
	Back_,
};

enum class EHOUSEDEPTH
{
	FRAME,
	Object,
	Shadow = 1000,
	Rug,
	HouseComposition,
	BackPaint,
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


enum class EUI_RENDERORDERDEPTH
{
	Frame = -100,
	Attachment,
	Component,
	Icon,
	CursorOutLine,
	Cursor,
	Base,
	Mark,
	HUB_Frame,
	HUB_Gauge1,
	HUB_Gauge2,
	HUB_Indicator,
	HUB_Icon,
	UIArrow = -1,
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
