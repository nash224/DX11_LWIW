#pragma once

// Ό³Έν :
class GlobalUtils
{
public:
	// constrcuter destructer
	GlobalUtils();
	~GlobalUtils();



	static void LoadAllFileInPath(std::string_view _Path);
	static std::string GetParentString(std::string_view _ChildPath);

protected:

private:
	// delete Function
	GlobalUtils(const GlobalUtils& _Other) = delete;
	GlobalUtils(GlobalUtils&& _Other) noexcept = delete;
	GlobalUtils& operator=(const GlobalUtils& _Other) = delete;
	GlobalUtils& operator=(GlobalUtils&& _Other) noexcept = delete;

};

