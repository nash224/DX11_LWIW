#pragma once
#include "GaugeRenderer.h"

// Ό³Έν :
class GaugeUIRenderer : public GaugeRenderer
{
public:
	// constrcuter destructer
	GaugeUIRenderer();
	~GaugeUIRenderer();

	// delete Function
	GaugeUIRenderer(const GaugeUIRenderer& _Other) = delete;
	GaugeUIRenderer(GaugeUIRenderer&& _Other) noexcept = delete;
	GaugeUIRenderer& operator=(const GaugeUIRenderer& _Other) = delete;
	GaugeUIRenderer& operator=(GaugeUIRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:


};

