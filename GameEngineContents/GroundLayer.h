#pragma once

// Ό³Έν :
class GroundLayer
{
public:
	// constrcuter destructer
	GroundLayer();
	~GroundLayer();

	// delete Function
	GroundLayer(const GroundLayer& _Other) = delete;
	GroundLayer(GroundLayer&& _Other) noexcept = delete;
	GroundLayer& operator=(const GroundLayer& _Other) = delete;
	GroundLayer& operator=(GroundLayer&& _Other) noexcept = delete;

protected:

private:

};

