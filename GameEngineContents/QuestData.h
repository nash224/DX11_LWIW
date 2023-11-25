#pragma once
#include "ContentsResource.h"

enum class EQUEST
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
		std::string_view _Name,
		std::string_view _QuestName,
		std::string_view _Contents,
		EQUEST _QuestType = EQUEST::Main)
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
	std::string QuestName;
	std::string Contents;
	EQUEST QuestType = EQUEST::None;

};