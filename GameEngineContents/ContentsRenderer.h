#pragma once

class ContentsFrameAnimation
{
	friend class ContentsRenderer;

public:
	ContentsRenderer* Parent = nullptr;

	std::string AnimationName;
	std::string SpriteName;

	std::shared_ptr<GameEngineSprite> Sprite = nullptr;

	// float Inter;
	bool Loop = false;
	bool IsEnd = false;

	bool EventCheck = false;

	int Start = -1;
	int End = -1;
	int InterIndex = 0;
	int CurIndex = 0;
	float CurTime = 0.0f;

	std::vector<int> Index;

	void Reset();

	std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> FrameChangeFunction;

	std::map<int, std::function<void(ContentsRenderer*)>> FrameEventFunction;

	std::function<void(ContentsRenderer*)> EndEvent;

	SpriteData Update(float _DeltaTime);

	void EventCall(int _Frame);

public:
	std::vector<float> Inter;
};

// 설명 :
class ContentsRenderer : public GameEngineRenderer
{
	friend ContentsFrameAnimation;

public:
	// constrcuter destructer
	ContentsRenderer();
	~ContentsRenderer();

	// delete Function
	ContentsRenderer(const ContentsRenderer& _Other) = delete;
	ContentsRenderer(ContentsRenderer&& _Other) noexcept = delete;
	ContentsRenderer& operator=(const ContentsRenderer& _Other) = delete;
	ContentsRenderer& operator=(ContentsRenderer&& _Other) noexcept = delete;

	// 스프라이트는 기본적으로 
	// 강제로 애니메이션을 정지한다는 뜻으로 받아들이겠다.
	void SetSprite(std::string_view _Name, unsigned int index = 0);
	void ChangeCurSprite(int _Index);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f,
		unsigned int _Start = -1,
		unsigned int _End = -1,
		bool _Loop = true
	);

	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false, unsigned int _FrameIndex = 0);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	inline void SetAutoScaleRatio(float _Ratio)
	{
		AutoScaleRatio.X = _Ratio;
		AutoScaleRatio.Y = _Ratio;
	}

	inline void SetAutoScaleRatio(float4 _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}

	bool IsRight()
	{
		return 0 < AutoScaleRatio.X;
	}

	void RightFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 0;
	}

	void LeftFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 1;
	}

	void UpFlip()
	{
		SpriteRendererInfoValue.FlipUp = 1;
	}

	void DownFlip()
	{
		SpriteRendererInfoValue.FlipUp = 0;
	}

	bool IsCurAnimationEnd()
	{
		return CurFrameAnimations->IsEnd;
	}

	bool IsCurAnimation(std::string_view _AnimationName)
	{
		return CurFrameAnimations->AnimationName == _AnimationName;
	}

	std::shared_ptr<ContentsFrameAnimation> FindAnimation(std::string_view _AnimationName)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

		if (false == FrameAnimations.contains(UpperName))
		{
			return nullptr;
		}

		return FrameAnimations[UpperName];
	}

	void AnimationPauseSwitch();
	void AnimationPauseOn();
	void AnimationPauseOff();

	void SetStartEvent(std::string_view _AnimationName, std::function<void(ContentsRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(ContentsRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(ContentsRenderer*)> _Function);

	void SetFrameChangeFunction(std::string_view _AnimationName, std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> _Function);

	// "EngineBaseWRAPSampler"
	void SetSampler(std::string_view _Name);

	void SetPivotValue(const float4& _Value)
	{
		Pivot = _Value;
	}
	float4 GetPivotValue()
	{
		return Pivot;
	}

	void SetPivotType(PivotType _Type);
	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);

	std::shared_ptr<GameEngineSprite> GetSprite()
	{
		return Sprite;
	}

	const SpriteData& GetCurSprite()
	{
		return CurSprite;
	}

	inline unsigned int GetCurIndex() const
	{
		return CurFrameAnimations->CurIndex;
	}

	std::shared_ptr<ContentsFrameAnimation> CurAnimation()
	{
		return CurFrameAnimations;
	}

	inline GameEngineTransform& GetImageTransform()
	{
		return ImageTransform;
	}

	inline ColorData& GetColorData()
	{
		return ColorDataValue;
	}

	void SetMaskTexture(std::string_view _Texture, MaskMode _Mask = MaskMode::StaticMask);

	void SetText(const std::string& _Font, const std::string& _Text, float _Scale = 20.0f, float4 Color = float4::RED, FW1_TEXT_FLAG Flag = FW1_LEFT);
	void SetTextColor(const float4& _Color = float4::RED, unsigned int _Index = 0);
	void SetTextAlpha(float _AlphaValue = 1.0f, unsigned int _Index = 0);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
	void SetMaterialEvent(std::string_view _Name, int _Index) override;

	int Index = 0;

private:
	// 부모인 actor를 기준으로한

	std::map<std::string, std::shared_ptr<ContentsFrameAnimation>> FrameAnimations;

	std::shared_ptr<ContentsFrameAnimation> CurFrameAnimations;

	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;
	SpriteRendererInfo SpriteRendererInfoValue;

	std::shared_ptr<class GameEngineSampler> Sampler;

	bool IsImageSize = false;
	float4 AutoScaleRatio = { 1.0f,1.0f,1.0f };
	bool IsPause = false;

	float4 Pivot = { 0.5f, 0.5f };

	ColorData ColorDataValue;

	GameEngineTransform ImageTransform;

	bool IsUserSampler = true;
};
