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

// unordered_map 자료구조를 선택하지 않은 이유
// unordered_map은 순서가 정렬되지 않고 검색, 삽입, 제거 비용이 상수시간으로 빠르다.
// 하지만 해시충돌 문제로 해시 함수를 따로 만들어 줘야하는데
// 여기서 std::hash가 지원하지않는 객체를 커스텀 class로 만들어 재정의한다면 프로그램의 취약성이 나타난다고 한다.
// 아래의 클래스는 키를 입력하는 함수를 줄이고 싶어 만들었지만, Input의 순서도 중요하기 때문에 잘못만들었다고 판단했다.
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