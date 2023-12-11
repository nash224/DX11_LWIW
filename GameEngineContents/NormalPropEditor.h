#pragma once
#include "NormalProp.h"

// Ό³Έν :
class NormalPropEditor : public NormalProp
{
public:
	// constrcuter destructer
	NormalPropEditor();
	~NormalPropEditor();

	// delete Function
	NormalPropEditor(const NormalPropEditor& _Other) = delete;
	NormalPropEditor(NormalPropEditor&& _Other) noexcept = delete;
	NormalPropEditor& operator=(const NormalPropEditor& _Other) = delete;
	NormalPropEditor& operator=(NormalPropEditor&& _Other) noexcept = delete;

	void SetPixelCollision(std::string_view _FileName) override;

protected:
	void Release() override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

