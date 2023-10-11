#pragma once

enum class ERENDERPIVOTPOS
{
	Center,
	LeftTop,
	RightBottom,
};


// 설명 :
class GlobalUtils
{
public:
	// constrcuter destructer
	GlobalUtils();
	~GlobalUtils();



public:
	// 리소스 로드
	static void LoadAllFileInPath(std::string_view _Path);
	static void LoadAllDirFile(std::string_view _Path);
	static void ReleaseAllTextureInPath(std::string_view _Path);
	static std::string GetParentString(std::string_view _ChildPath);


public:
	template<typename OrderType>
	static float CalculateDepth(OrderType _Order)
	{
		return CalculateDepth(static_cast<float>(_Order));
	}

	static float CalculateDepth(int _Order)
	{
		return CalculateDepth(static_cast<float>(_Order));
	}

	static float CalculateDepth(const float _Value);
	static float4 CalculateActorPivot(const float4& _Scale, ERENDERPIVOTPOS _Pivot);

protected:

private:
	// delete Function
	GlobalUtils(const GlobalUtils& _Other) = delete;
	GlobalUtils(GlobalUtils&& _Other) noexcept = delete;
	GlobalUtils& operator=(const GlobalUtils& _Other) = delete;
	GlobalUtils& operator=(GlobalUtils&& _Other) noexcept = delete;

};

