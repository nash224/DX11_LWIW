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
	Object,
	AlphaBlend,
	Shadow,
	Effect,
	UI_AlphaBlend,
	Fade = 100,
};

enum class ETITLERENDERORDER
{
	Back_ ,
	Star ,
	Moon ,
	Cloud_0,
	Cloud_1,
	Cloud_2,
	Cloud_3,
	Cloud_4 ,
	Water,
	Mountain_blur,
	Bridge_Down,
	Bridge_blur,
	Train_blur,
	Train_Light_blur,
	Water_blur,
	Props_1,
	Props_0,
	TrainSmoke_Big,
	TrainSmoke_Mid,
	TrainSmoke_Small,
	Trains,
	Trains_Light,
	Bridge ,
	Tree,
	Shadow,
	Logo,
};


enum class ERENDERDEPTH
{
	FadeObject = -1000,
	Roof = -2,
	FX = -1,
	Object = 0,
	RootedItem = 3000,
	ObjectShadow,
	Hole,
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
	Shadow = 3000,
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
