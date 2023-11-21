#pragma once

// Ό³Έν :
class GlobalLoad
{
public:
	// constrcuter destructer
	GlobalLoad();
	~GlobalLoad();

	// delete Function
	GlobalLoad(const GlobalLoad& _Other) = delete;
	GlobalLoad(GlobalLoad&& _Other) noexcept = delete;
	GlobalLoad& operator=(const GlobalLoad& _Other) = delete;
	GlobalLoad& operator=(GlobalLoad&& _Other) noexcept = delete;

	static void LoadGlobalResource();

protected:
	static void LoadGlobalTexture();
	static void LoadGlobalSprite();

};

