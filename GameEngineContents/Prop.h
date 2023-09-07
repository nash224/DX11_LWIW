#pragma once


// ��ȣ�ۿ��� ������ Prop�� ��ȣ�ۿ��� �Ұ����� Prop�� ������.
// 

// ���� : 
class Prop : public GameEngineActor
{
public:
	// constrcuter destructer
	Prop();
	~Prop();

	// delete Function
	Prop(const Prop& _Other) = delete;
	Prop(Prop&& _Other) noexcept = delete;
	Prop& operator=(const Prop& _Other) = delete;
	Prop& operator=(Prop&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


public:
	template<typename RenderOrder>
	void CreateRenderer(RenderOrder _Order)
	{
		CreateRenderer(static_cast<int>(_Order));
	}

	void CreateRenderer(int _Order);

	void SetSprite(std::string_view _SpriteName);
	void SetWorldPosition(const float4& _Position);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f,
		unsigned int _Start = -1,
		unsigned int _End = -1,
		bool _Loop = true
	);

	void ChangeAnimation(std::string_view _AnimationName);
	
	
public:
	void ActorRelease();


protected:
	
	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer;

	float4 m_Position;

};

