#pragma once

enum class ERENDERPIVOTPOS
{
	Center,
	LeftTop,
	RightBottom,
};


// Ό³Έν :
class GlobalUtils
{
public:
	// constrcuter destructer
	GlobalUtils();
	~GlobalUtils();



public:
	static void LoadAllFileInPath(std::string_view _Path);
	static void LoadAllDirFile(std::string_view _Path);
	static void ReleaseAllTextureInPath(std::string_view _Path);
	static std::string GetParentString(std::string_view _ChildPath);


public:
	static float4 CalculateActorPivot(const float4& _Scale, ERENDERPIVOTPOS _Pivot);

protected:

private:
	// delete Function
	GlobalUtils(const GlobalUtils& _Other) = delete;
	GlobalUtils(GlobalUtils&& _Other) noexcept = delete;
	GlobalUtils& operator=(const GlobalUtils& _Other) = delete;
	GlobalUtils& operator=(GlobalUtils&& _Other) noexcept = delete;

};

