#pragma once



enum class EUPDATEORDER
{
	Mouse,
	Player,
	Entity,
	Projectile,
	Objects,
	Event,
	Portal,
	CameraControler,
	UIMagnaer,
	UIComponent,
	Sky,
	Fade,
};

enum class ERENDERORDER
{
	NonAlphaBlend,
	Effect,
	SkyLight,
	Fade = 100,
};

enum class ERENDERDEPTH
{
	FadeObject = -450,
	illuminant = -120,
	SkyBox = -110,
	Roof = -100,
	FX,
	Hill_Object = -1,
	Object = 0,
	RootedItem = 1500,
	ObjectShadow,
	Hole = 3000,
	Cliff,
	Grass,
	DeepDarkGrass,
	DarkGrass,
	Back_Paint = 3400,
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
	Light_,
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
	GroundDust = 2000,
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
	Alert_Font = -400,
	Alert_Img,
	Alert_Stamp,
	Alert_Base,
	Alert_Shadow,
	Cursor ,
	CursorOutLine,
	Icon_Mask,
	Icon,
	Component,
	Attachment,
	Frame,
	Base,
	Conversation_Message,
	Conversation_Arrow,
	Conversation_Tail,
	Conversation_Frame,
	Conversation_Portrait,
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
