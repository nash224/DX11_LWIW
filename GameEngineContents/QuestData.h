#pragma once
#include "ContentsResource.h"

enum  class EQUESTTYPE
{
	Main,
	Side,
	Repeat,
	None,
};


// Ό³Έν :
class QuestData : public ContentsResource<QuestData>
{
public:
	// constrcuter destructer
	QuestData();
	~QuestData();


	QuestData(
		std::string _Name,
		std::string _QuestName,
		std::string _Contents,
		EQUESTTYPE _QuestType = EQUESTTYPE::Main
	)
		:
		Name(_Name),
		QuestName(_QuestName),
		Contents(_Contents),
		QuestType(_QuestType)
	{
		
	}

	// delete Function
	//QuestData(const QuestData& _Other) = delete;
	//QuestData(QuestData&& _Other) noexcept = delete;
	//QuestData& operator=(const QuestData& _Other) = delete;
	//QuestData& operator=(QuestData&& _Other) noexcept = delete;


public:
	std::string Name;
	EQUESTTYPE QuestType = EQUESTTYPE::None;
	std::string QuestName;
	std::string Contents;

};