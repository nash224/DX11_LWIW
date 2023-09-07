#pragma once
#include "Prop.h"

// Ό³Έν :
class PropSeries : public Prop
{
public:
	// constrcuter destructer
	PropSeries();
	~PropSeries();

	// delete Function
	PropSeries(const PropSeries& _Other) = delete;
	PropSeries(PropSeries&& _Other) noexcept = delete;
	PropSeries& operator=(const PropSeries& _Other) = delete;
	PropSeries& operator=(PropSeries&& _Other) noexcept = delete;

protected:

private:

};

