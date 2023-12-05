#include "PreCompile.h"
#include "AnimationHelper.h"


int FrameAnimationHelper::GetIndex(std::string_view _AnimationName, int _CurIndex)
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

void FrameAnimationHelper::UpdateHelper(const std::shared_ptr<GameEngineSpriteRenderer>& _BodyRenderer, const std::shared_ptr<GameEngineSpriteRenderer>& _ChaseRenderer)
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

void FrameAnimationHelper::SetSameAnimation(const std::shared_ptr<GameEngineSpriteRenderer>& _BodyRenderer, const std::shared_ptr<GameEngineSpriteRenderer>& _ChaseRenderer)
{
	if (nullptr == _BodyRenderer || nullptr == _ChaseRenderer)
	{
		return;
	}

	_ChaseRenderer->SetSprite(_BodyRenderer->GetCurSprite().Texture->GetName());
}

bool FrameAnimationHelper::IsCurFrame(std::string_view _AnimationName, int _CurIndex)
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