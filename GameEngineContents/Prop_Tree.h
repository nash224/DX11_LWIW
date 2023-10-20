#pragma once
#include "Props.h"

enum class ETREETYPE
{
	Tree0,
	Tree1,
	Tree2,
	Tree3,
	Tree4,
	Tree5,
};


// Ό³Έν :
class Prop_Tree : public Props
{
public:
	// constrcuter destructer
	Prop_Tree();
	~Prop_Tree();

	// delete Function
	Prop_Tree(const Prop_Tree& _Other) = delete;
	Prop_Tree(Prop_Tree&& _Other) noexcept = delete;
	Prop_Tree& operator=(const Prop_Tree& _Other) = delete;
	Prop_Tree& operator=(Prop_Tree&& _Other) noexcept = delete;

	void SelectTreeType(ETREETYPE _Type);
	void Init();

	void RendererSetting(std::string_view _FileName);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	


private:
	ETREETYPE m_TreeType = ETREETYPE::Tree0;


	float m_TreeRendererBias = 114.0f;

};

