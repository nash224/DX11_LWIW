#pragma once



enum class EUPDATEORDER
{
	Map,
	Mouse,
	Player,
	Back,
	Entity,
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
	Light,
	AlphaLight,
	Fade = 100,
};

enum class ERENDERDEPTH
{
	FadeObject = -450,
	illuminant = -120,
	SkyBox = -110,
	Roof = -100,
	Gauge_Bar,
	Gauge_Base,
	Emoticon_Emotion,
	Emoticon_Base,
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
	Scenery_Ground = 3500,
	Scenery_Sky,
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
	Cloud_blur_2,
	Cloud_blur_1,
	Water,
	Cloud_4 = 400,
	Cloud_3,
	Cloud_2,
	Cloud_1,
	Cloud_0,
	Moon = 500,
	Comet = 550,
	Star = 600,
	Back_ = 700,
};

enum class EHOUSEDEPTH
{
	FRAME = -1,
	Lift_Floor,
	Object,
	GroundDust = 2000,
	LiftPattern,
	Lift,
	Lift_Wall,
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
	Window_Font = -400,
	Window_Cursor,
	Window_Frame,
	Window_Base,
	Font,
	Cursor,
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
	Alert_Font,
	Alert_Img,
	Alert_Stamp,
	Alert_Base,
	Alert_Shadow,
	UIArrow,
	HUB_Font,
	HUB_Icon,
	HUB_Indicator,
	HUB_Gauge2,
	HUB_Gauge1,
	HUB_Frame,
	HUB_Base,
	Mark,
	PlayUI_Guage,
	PlayUI_Base,
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

enum class EDEUBGORDER
{
	Player,
	Pixel = 0,
};