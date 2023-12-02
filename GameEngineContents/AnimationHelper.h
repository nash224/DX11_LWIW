#pragma once


struct FrameAnimationHelper
{
public:
	void CreateFrameInfo(std::string_view _AnimationName, const std::vector<int>& _Indexs)
	{
		FrameIndexData.insert(std::make_pair(_AnimationName, _Indexs));
	}

	int GetIndex(std::string_view _AnimationName, int _CurIndex)
	{
		if (true == IsCurFrame(_AnimationName, _CurIndex))
		{
			return RenderIndex;
		}

		std::vector<int> Indexs = Find(_AnimationName);
		if (0 == Indexs.size())
		{
			const int NotFound = -1;
			RenderIndex = NotFound;
			return NotFound;
		}

		RenderIndex = Indexs.at(CurIndex);

		return RenderIndex;
	}

	void UpdateHelper(const std::shared_ptr<GameEngineSpriteRenderer>& _BodyRenderer, const std::shared_ptr<GameEngineSpriteRenderer>& _ChaseRenderer)
	{
		if (nullptr == _BodyRenderer)
		{
			return;
		}

		std::string_view AniName = _BodyRenderer->CurAnimation()->AnimationName;
		const int Index = _BodyRenderer->GetCurIndex();
		const int FrameIndex = GetIndex(AniName, Index);

		if (nullptr != _ChaseRenderer)
		{
			bool NotFound = (-1 == FrameIndex);
			if (NotFound)
			{
				_ChaseRenderer->Off();
			}
			else
			{
				_ChaseRenderer->ChangeCurSprite(FrameIndex);
			}
		}
	}

private:
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