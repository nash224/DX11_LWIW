#pragma once

struct FileLoadFunction
{
public:
	static void LoadAllFileInPath(std::string_view _Path);
	static void LoadTextureAndCreateSingleSpriteInPath(std::string_view _Path);
	static void LoadAllDirFile(std::string_view _Path);
	static void ReleaseAllTextureInPath(std::string_view _Path);
	static void ReleaseAllTextureAndSpriteInPath(std::string_view _Path);
	static std::vector<GameEngineFile> GetAllFileInPath(std::string_view _Path);
	static std::vector<GameEngineDirectory> GetAllDirInPath(std::string_view _Path);

private:
	static std::string GetParentString(std::string_view _ChildPath);

};

// unordered_map �ڷᱸ���� �������� ���� ����
// unordered_map�� ������ ���ĵ��� �ʰ� �˻�, ����, ���� ����� ����ð����� ������.
// ������ �ؽ��浹 ������ �ؽ� �Լ��� ���� ����� ����ϴµ�
// ���⼭ std::hash�� ���������ʴ� ��ü�� Ŀ���� class�� ����� �������Ѵٸ� ���α׷��� ��༺�� ��Ÿ���ٰ� �Ѵ�.
// �Ʒ��� Ŭ������ Ű�� �Է��ϴ� �Լ��� ���̰� �;� ���������, Input�� ������ �߿��ϱ� ������ �߸�������ٰ� �Ǵ��ߴ�.
//struct InputFunction
//{
//public:
//	bool InputRegister(char _Key, std::function<void()> _Func);
//	void Update();
//
//private:
//	std::unordered_map<const char, std::function<void()>> InputEvents;
//
//};

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
	static void LoadSoundFile(const std::vector<GameEngineFile>& _Files);

};

struct StringFunction
{
public:
	static int GetNewLineCount(std::string_view _Text);
	static std::string InsertNewLineBTWWord(std::string_view _Text, int _NumCharPerLine);

};

struct RandomFunction
{
public:
	static float GetRandomfValue(float _Min, float _Max);

};


class ArrangementHelper
{
public:
	static void RegisterInput(void* _Ptr);
	static void InputUpdate(GameEngineObject* _Target, void* _Ptr);

private:
	static bool ArrangeRendererOnePixel(GameEngineObject* _Target, char _Character, void* _Ptr, const float4& _MoveVector);
	static float Speed;

};