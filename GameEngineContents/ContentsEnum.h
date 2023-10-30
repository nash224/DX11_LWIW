#pragma once



enum class EUPDATEORDER
{
	Mouse,
	Player,
	Entity,
	Projectile,
	Objects,
	Sky,
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

enum class ERENDERDEPTH
{
	FadeObject = -450,
	illuminant = - 120,
	SkyBox = -110,
	Roof = -100,
	FX,
	Object = 0,
	RootedItem = 3000,
	ObjectShadow,
	Hole,
	Cliff,
	Grass,
	DeepDarkGrass,
	DarkGrass,
	Back_Paint,
};

enum class ETITLERENDERDEPTH
{
	Logo,
	UI,
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
	UnderBook,
	Chair,
	Sign,
	Rug,
	Wall,
	HouseComposition,
	BackWindow,
	BackPaint,
};

enum class EUI_RENDERORDERDEPTH
{
	Cursor = -400,
	CursorOutLine,
	Icon_Mask,
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


enum class ECOLLISION
{
	Player,
	Net,
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
