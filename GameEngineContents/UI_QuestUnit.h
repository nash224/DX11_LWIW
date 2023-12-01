#pragma once
#include "QuestData.h"

// Ό³Έν :
class UI_QuestUnit : public GameEngineActor
{
	friend class UI_Hub_MainBoard;

private:
	class UIQuestUnitSturct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> SubjectBase;
		std::shared_ptr<GameEngineUIRenderer> Subject;

		std::shared_ptr<GameEngineUIRenderer> ContentBase;
		std::shared_ptr<GameEngineUIRenderer> QuestName;
		std::shared_ptr<GameEngineUIRenderer> QuestContent;
		std::shared_ptr<GameEngineUIRenderer> Dot;
	};

public:
	UI_QuestUnit();
	~UI_QuestUnit();

	// delete Function
	UI_QuestUnit(const UI_QuestUnit& _Other) = delete;
	UI_QuestUnit(UI_QuestUnit&& _Other) noexcept = delete;
	UI_QuestUnit& operator=(const UI_QuestUnit& _Other) = delete;
	UI_QuestUnit& operator=(UI_QuestUnit&& _Other) noexcept = delete;

	void Init(std::string_view _Data);
	void SetLocalPosition(const float4& _Position);
	void AddLocalPosition(const float4& _Position);

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	std::string GetSubjectTextToType(EQUEST _Type);
	float GetRenderYSize(int _ContentLineCount);

private:
	UIQuestUnitSturct QuestUnit;
	std::weak_ptr<QuestData> Data;
	class UI_Hub_MainBoard* MaibBoardPointer = nullptr;

	float RenderYScale = 0.0f;

};

