#pragma once



// 설명 :
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
	// BackDrop의 요소
	// 1. Scenery(배경)
	// 2. Tile(바닥)
	// 3. Prop(소품 : 건물, 구조물, 깃발, 시민 등)
	// 4. 비트 충돌맵
	std::vector<std::shared_ptr<Scenery>> vecScenery;
	std::vector<std::shared_ptr<Prop>> vecProps;

	float4 m_BackScale;

private:

};

