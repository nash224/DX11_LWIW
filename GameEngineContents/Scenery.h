#pragma once

// ��� : ī�޶��� �̵��ϸ� ��浵 ���� ������ �����Դϴ�.
// ���� : ����� �ð� �ֽ��ϴ�. �ϳ��� ��������Ʈ�� ����ؾ��մϴ�.
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
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	template<typename RenderOrder>
	void SetRenderOrder(RenderOrder _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}

	void SetSprite(std::string_view _SpriteName);
	void SetRenderOrder(int _Order);
	void SetWorldPosition(const float4& _Position);
	void SetWorldPosition(const float4& _Position, ERENDER_PIVOT_LOCATION _Location);
	void SetMoveDirection(const float4& _Direction);
	void SetMoveRatio(float _Ratio);

private:
	void MoveSceneryLocation(float _Delta);


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_SpriteRenderer;
	float4 m_TextureSize;
	float4 m_Direction;
	float m_MoveRatio;

};

