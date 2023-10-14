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
	NonAlphaBlend,
	AlphaBlend,
	Shadow,
	Effect,
};


enum class ERENDERDEPTH
{
	FadeObject = -1000,
	Roof = -1,
	Object = 0,
	RootedItem = 5000,
	ObjectShadow,
	Back_,
	Back_Paint,
};

enum class ETITLERENDERDEPTH
{
	Logo,
	Shadow,
	Tree = 100,
	Bridge = 200,
	Trains_Light,
	Trains,
	TrainSmoke_Small,
	TrainSmoke_Mid,
	TrainSmoke_Big,
	Props_0,
	Props_1,
	Water_blur,
	Train_Light_blur,
	Train_blur,
	Bridge_blur,
	Bridge_Down,
	Mountain_blur,
	Water,
	Cloud_4 = 400,
	Cloud_3,
	Cloud_2,
	Cloud_1,
	Cloud_0,
	Moon = 500,
	Star = 600,
	Back_ = 700,
};

enum class EHOUSEDEPTH
{
	FRAME = -1,
	Object,
	Shadow = 100,
	Rug,
	HouseComposition,
	BackPaint,
};

enum class EUI_RENDERORDERDEPTH
{
	Cursor = -100,
	CursorOutLine,
	Icon,
	Component,
	Attachment,
	Frame,
	Base,
	UIArrow,
	HUB_Icon,
	HUB_Indicator,
	HUB_Gauge2,
	HUB_Gauge1,
	HUB_Frame,
	Mark,
};
//Mark,
//HUB_Frame,
//HUB_Gauge1,
//HUB_Gauge2,
//HUB_Indicator,
//HUB_Icon,
//UIArrow,
//Base,
//Frame,
//Attachment,
//Component,
//Icon,
//CursorOutLine,
//Cursor,


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
