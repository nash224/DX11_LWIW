#pragma once


struct FrameAnimationHelper
{
public:
	void CreateFrameInfo(std::string_view _AnimationName, const std::vector<int>& _Indexs)
	{
		FrameIndexData.insert(std::make_pair(_AnimationName, _Indexs));
	}

	bool IsCurFrame(std::string_view _AnimationName, int _CurIndex)
	{
		if (CurAnimationName != _AnimationName.data())
		{
			CurAnimationName = _AnimationName;
			CurIndex = _CurIndex;
			return false;
		}

		if (CurIndex != _CurIndex)
		{
			CurIndex = _CurIndex;
			return false;
		}

		return true;
	}

	int GetIndex(std::string_view _AnimationName, int _CurIndex)
	{
		if (true == IsCurFrame(_AnimationName, _CurIndex))
		{
			return CurIndex;
		}

		return Find(_AnimationName).at(CurIndex);
	}

	const std::vector<int>& Find(std::string_view _AnimationName)
	{
		std::map<std::string, std::vector<int>>::iterator FindIter = FrameIndexData.find(_AnimationName.data());
		if (FindIter == FrameIndexData.end())
		{
			MsgBoxAssert("존재하지 않는 데이터를 참조하려 했습니다.");
			return std::vector<int>();
		}

		return FindIter->second;
	}

private:
	std::map<std::string, std::vector<int>> FrameIndexData;
	std::string CurAnimationName;
	int CurIndex = 0;

};