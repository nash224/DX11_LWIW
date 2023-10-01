#pragma once

// 설명 : Bool자료형의 이벤트 변수를 전역으로 제공합니다. 
class EventData
{
public:
	static void Init();
	
public:
	static std::vector<bool> ToolData;


private:
	// constrcuter destructer
	EventData();
	~EventData();

	// delete Function
	EventData(const EventData& _Other) = delete;
	EventData(EventData&& _Other) noexcept = delete;
	EventData& operator=(const EventData& _Other) = delete;
	EventData& operator=(EventData&& _Other) noexcept = delete;


protected:


};

