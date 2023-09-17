#pragma once

// Ό³Έν :
class EventManager
{
public:
	// constrcuter destructer
	EventManager();
	~EventManager();

	// delete Function
	EventManager(const EventManager& _Other) = delete;
	EventManager(EventManager&& _Other) noexcept = delete;
	EventManager& operator=(const EventManager& _Other) = delete;
	EventManager& operator=(EventManager&& _Other) noexcept = delete;

protected:

private:

};

