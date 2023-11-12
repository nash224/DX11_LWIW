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
	static std::vector<GameEngineFile> GetAllFileInPath(std::string_view _Path);
	static std::vector<GameEngineDirectory> GetAllDirInPath(std::string_view _Path);

	static std::string GetParentString(std::string_view _ChildPath);


public:
	static float CalculateObjectDepth(float _BackScale, float _PositionY, bool _isHill = false);

	template<typename OrderType>
	static float CalculateFixDepth(OrderType _Order)
	{
		return CalculateFixDepth(static_cast<float>(_Order));
	}

	static float CalculateFixDepth(int _Order)
	{
		return CalculateFixDepth(static_cast<float>(_Order));
	}

	static float CalculateFixDepth(const float _Value);

	static void PlaySFX(std::string_view _SoundFileName);

protected:

private:
	// delete Function
	GlobalUtils(const GlobalUtils& _Other) = delete;
	GlobalUtils(GlobalUtils&& _Other) noexcept = delete;
	GlobalUtils& operator=(const GlobalUtils& _Other) = delete;
	GlobalUtils& operator=(GlobalUtils&& _Other) noexcept = delete;

};

