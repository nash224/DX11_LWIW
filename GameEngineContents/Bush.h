#pragma once
#include "StaticEntity.h"

enum class EBUSHTYPE
{
	Bush,
	BushBug,
	BushApple,
	None,
};


enum class EBUSHSTATE
{
	Normal,				// 평상시
	Apple,				// 사과
	Shake,				// 사과 흔들기
	Rustle,				// 부시럭거림
	AppearBug,			// 벌레 등장
	None,
};



// 설명 :
class Bush : public StaticEntity
{
public:
	// constrcuter destructer
	Bush();
	~Bush();

	// delete Function
	Bush(const Bush& _Other) = delete;
	Bush(Bush&& _Other) noexcept = delete;
	Bush& operator=(const Bush& _Other) = delete;
	Bush& operator=(Bush&& _Other) noexcept = delete;


	void SetBushType(EBUSHTYPE _Type);
	void Init();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateBushAnimation();
	void InteractiveOptionSetting();
	void BushStateSetting();

private:
	void UpdateState(float _Delta);
	void ChangeState(EBUSHSTATE _State);
	void ChangeBushAnimation(std::string_view _Name);

	void StartNormal();
	void UpdateNormal(float _Delta);

	void StartApple();
	void UpdateApple(float _Delta);

	void StartShake();
	void UpdateShake(float _Delta);

	void StartRustle();
	void UpdateRustle(float _Delta);

	void StartAppearBug();
	void UpdateAppearBug(float _Delta);
	void CreateBushBug();



private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Bush = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_Bush_FX = nullptr;

private:
	EBUSHTYPE m_BushType = EBUSHTYPE::None;
	EBUSHSTATE m_State = EBUSHSTATE::None;
	
};

