#pragma once
#include "SkyLerp.h"

// Ό³Έν :
class WorkSpaceSkyLerp : public SkyLerp
{
public:
	// constrcuter destructer
	WorkSpaceSkyLerp();
	~WorkSpaceSkyLerp();

	// delete Function
	WorkSpaceSkyLerp(const WorkSpaceSkyLerp& _Other) = delete;
	WorkSpaceSkyLerp(WorkSpaceSkyLerp&& _Other) noexcept = delete;
	WorkSpaceSkyLerp& operator=(const WorkSpaceSkyLerp& _Other) = delete;
	WorkSpaceSkyLerp& operator=(WorkSpaceSkyLerp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;

	void SetSkyData()override;

private:


};

