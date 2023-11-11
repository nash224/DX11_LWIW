#pragma once
#include "ContentsSpriteRenderer.h"

// Ό³Έν :
class ContentsUIRenderer : public ContentsSpriteRenderer
{
public:
	// constrcuter destructer
	ContentsUIRenderer();
	~ContentsUIRenderer();

	// delete Function
	ContentsUIRenderer(const ContentsUIRenderer& _Other) = delete;
	ContentsUIRenderer(ContentsUIRenderer&& _Other) noexcept = delete;
	ContentsUIRenderer& operator=(const ContentsUIRenderer& _Other) = delete;
	ContentsUIRenderer& operator=(ContentsUIRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};