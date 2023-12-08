#pragma once

// 기능 : 카메라의 이동하면 배경도 일정 비율로 움직입니다.
// 설명 : 배경을 맡고 있습니다. 하나의 스프라이트만 사용해야합니다.
class Scenery : public GameEngineActor
{
public:
	// constrcuter destructer
	Scenery();
	~Scenery();

	// delete Function
	Scenery(const Scenery& _Other) = delete;
	Scenery(Scenery&& _Other) noexcept = delete;
	Scenery& operator=(const Scenery& _Other) = delete;
	Scenery& operator=(Scenery&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	// 세팅
	template<typename RenderOrder>
	void SetRenderOrder(RenderOrder _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}

	void SetSprite(std::string_view _SpriteName);
	void SetRenderOrder(int _Order);
	void SetWorldPosition(const float4& _Position);
	void SetMoveDirection(const float4& _Direction);
	void SetMoveRatio(float _Ratio);


private:
	// 배경 Update => 카메라 이동거리의 일정비율로 위치가 변합니다.
	void MoveSceneryLocation(float _Delta);

private:
	std::shared_ptr<GameEngineSpriteRenderer> SpriteRenderer;
	float4 TextureSize;
	float4 Direction;
	float MoveRatio;

private:
	
};

