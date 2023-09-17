#pragma once



enum class EUPDATEORDER
{
	Player,
	Npc,
	Enemy,
	Projectile,
	Objects,
	CameraControler,
	UI,
};


enum class ERENDERORDER
{
	Back_,
	Ellie,
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


enum class EUI_RENDERORDER
{

};

enum class ECOLLISION
{
	Potal,
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
	UP,
	LEFTUP,
	LEFT,
	LEFTDOWN,
	RIGHTUP,
	RIGHT,
	RIGHTDOWN,
	DOWN,
};
