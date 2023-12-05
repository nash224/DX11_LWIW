#pragma once


struct FrameAnimationHelper
{
public:
	void CreateFrameInfo(std::string_view _AnimationName, const std::vector<int>& _Indexs)
	{
		FrameIndexData.insert(std::make_pair(_AnimationName, _Indexs));
	}

	int GetIndex(std::string_view _AnimationName, int _CurIndex);
	void UpdateHelper(const std::shared_ptr<GameEngineSpriteRenderer>& _BodyRenderer, const std::shared_ptr<GameEngineSpriteRenderer>& _ChaseRenderer);
	void SetSameAnimation(const std::shared_ptr<GameEngineSpriteRenderer>& _BodyRenderer, const std::shared_ptr<GameEngineSpriteRenderer>& _ChaseRenderer);

private:
	bool IsCurFrame(std::string_view _AnimationName, int _CurIndex);

	const std::vector<int>& Find(std::string_view _AnimationName)
	{
		std::map<std::string, std::vector<int>>::iterator FindIter = FrameIndexData.find(_AnimationName.data());
		if (FindIter == FrameIndexData.end())
		{
			static std::vector<int> ReturnValue = std::vector<int>();
			return ReturnValue;
		}

		return FindIter->second;
	}

private:
	std::map<std::string, std::vector<int>> FrameIndexData;
	std::string CurAnimationName;
	int CurIndex = 0;
	int RenderIndex = 0;

};