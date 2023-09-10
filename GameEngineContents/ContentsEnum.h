#pragma once



enum class EUPDATEORDER
{
	Player,
	Npc,
	Enemy,
	Projectile,
	Objects,
	CameraControler,
};


enum class ERENDERORDER
{
	Back_,
	Scenery_0,
	Scenery_1,
	Scenery_2,
	Scenery_3,
	Scenery_4,
	Scenery_5,
	Scenery_6,
	Ground_Layer,
	Prop_1,
	Prop_2,
	Prop_3,
	Prop_4,
	Back_Shader,
	FX_Pre,
	Object,
	FX_Post,
	Lighting_Shader,
	Foreground_Ceiling,
	Tone_Shader,
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


enum class EUI_RENDERORDER
{

};

enum class ECOLLISION
{

};



enum class ELEVELTYPE
{
	None,
	MainMenu,
	Misson0_Part1,
	Max,
};

enum class EDIRECTION
{
	CENTER,
	TOP,
	LEFTTOP,
	LEFT,
	LEFTBOT,
	BOT,
	RIGHTBOT,
	RIGHT,
	RIGHTTOP,
};
