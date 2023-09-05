#pragma once

// Ό³Έν :
class MainActorControl
{
public:
	// constrcuter destructer
	MainActorControl();
	~MainActorControl();

	// delete Function
	MainActorControl(const MainActorControl& _Other) = delete;
	MainActorControl(MainActorControl&& _Other) noexcept = delete;
	MainActorControl& operator=(const MainActorControl& _Other) = delete;
	MainActorControl& operator=(MainActorControl&& _Other) noexcept = delete;

protected:

private:

};

