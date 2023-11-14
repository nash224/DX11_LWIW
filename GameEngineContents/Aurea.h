#pragma once
#include "NPCEntity.h"


enum class EAUREASTATE
{
	Curse,
	Normal,
};


// Ό³Έν :
class Aurea : public NPCEntity
{
private:
	enum class EAUREATOPICTYPE
	{
		Curse,
		CurseAfter,
		CursedNatural,
		CurseCure,
		Normal,
	};

private:
	static EAUREASTATE CurState;

public:
	// constrcuter destructer
	Aurea();
	~Aurea();

	// delete Function
	Aurea(const Aurea& _Other) = delete;
	Aurea(Aurea&& _Other) noexcept = delete;
	Aurea& operator=(const Aurea& _Other) = delete;
	Aurea& operator=(Aurea&& _Other) noexcept = delete;

	void Init();
	void RendererSetting();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void ConversationSetting();
	void StateSetting();

	void StartCurse(GameEngineState* _Parent);
	void StartNormal(GameEngineState* _Parent);

	void UpdateCurse(float _Delta, GameEngineState* _Parent);
	void UpdateNormal(float _Delta, GameEngineState* _Parent);

	void CheckAureaCurseEvent();
	void ShowFindAureaEvent();

	void CheckAureaCurseConversation();

private:
	std::shared_ptr<GameEngineSpriteRenderer> AureaRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	GameEngineState State;


	static constexpr const float RendererCorrection = 30.0f;

};