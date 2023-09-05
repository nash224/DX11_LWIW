#pragma once

// Ό³Έν :
class MouseObject
{
public:
	// constrcuter destructer
	MouseObject();
	~MouseObject();

	// delete Function
	MouseObject(const MouseObject& _Other) = delete;
	MouseObject(MouseObject&& _Other) noexcept = delete;
	MouseObject& operator=(const MouseObject& _Other) = delete;
	MouseObject& operator=(MouseObject&& _Other) noexcept = delete;

protected:

private:

};