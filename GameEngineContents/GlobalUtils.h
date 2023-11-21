#pragma once

struct FileLoadFunction
{
public:
	static void LoadAllFileInPath(std::string_view _Path);
	static void LoadAllDirFile(std::string_view _Path);
	static void ReleaseAllTextureInPath(std::string_view _Path);
	static std::vector<GameEngineFile> GetAllFileInPath(std::string_view _Path);
	static std::vector<GameEngineDirectory> GetAllDirInPath(std::string_view _Path);

private:
	static std::string GetParentString(std::string_view _ChildPath);

};

struct DepthFunction
{
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
};

struct SFXFunction
{
public:
	static GameEngineSoundPlayer PlaySFX(std::string_view _SoundFileName);

};
