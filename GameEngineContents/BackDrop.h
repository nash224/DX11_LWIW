#pragma once



// ���� :
class Scenery;
class Prop;
class BackDrop : public GameEngineActor
{
public:
	// constrcuter destructer
	BackDrop();
	~BackDrop();

	// delete Function
	BackDrop(const BackDrop& _Other) = delete;
	BackDrop(BackDrop&& _Other) noexcept = delete;
	BackDrop& operator=(const BackDrop& _Other) = delete;
	BackDrop& operator=(BackDrop&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:


protected:
	// BackDrop�� ���
	// 1. Scenery(���)
	// 2. Tile(�ٴ�)
	// 3. Prop(��ǰ : �ǹ�, ������, ���, �ù� ��)
	// 4. ��Ʈ �浹��
	std::vector<std::shared_ptr<Scenery>> vecScenery;
	std::vector<std::shared_ptr<Prop>> vecProps;

	float4 m_BackScale;

private:

};

