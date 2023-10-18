#pragma once
#include "Prop.h"


class ExPropParameter
{
public:
	int Order;
	std::string_view FileName;
	float4& RendererLocalPosition;

	ExPropParameter(int _Order, std::string_view _FileName, float4& _LocalPosition)
		:
		Order(_Order),
		FileName(_FileName),
		RendererLocalPosition(_LocalPosition)
	{

	}
};



// 설명 : 하나의 렌더러를 사용하는 Prop는 제약이 많아서 생성했습니다.
class ExProp : public Prop
{
public:
	// constrcuter destructer
	ExProp();
	~ExProp();

	// delete Function
	ExProp(const ExProp& _Other) = delete;
	ExProp(ExProp&& _Other) noexcept = delete;
	ExProp& operator=(const ExProp& _Other) = delete;
	ExProp& operator=(ExProp&& _Other) noexcept = delete;

	void CreateExProp(std::vector<ExPropParameter>& _Parameter);
	void ChangeExPropImageScale(unsigned int _Order, const float4& _ImageScale);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	void ActorRelease();


private:
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> vecRenderer;

};

