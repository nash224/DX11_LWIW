#pragma once
#include "Dust.h"

// Ό³Έν :
class Dust_Extractor : public Dust
{
public:
	// constrcuter destructer
	Dust_Extractor();
	~Dust_Extractor();

	// delete Function
	Dust_Extractor(const Dust_Extractor& _Other) = delete;
	Dust_Extractor(Dust_Extractor&& _Other) noexcept = delete;
	Dust_Extractor& operator=(const Dust_Extractor& _Other) = delete;
	Dust_Extractor& operator=(Dust_Extractor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void SetTopic();
	void QuestAccept();


};

