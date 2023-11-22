#pragma once

// Ό³Έν :
class PixelCollision : public GameEngineComponent
{
public:
	// constrcuter destructer
	PixelCollision();
	~PixelCollision();

	// delete Function
	PixelCollision(const PixelCollision& _Other) = delete;
	PixelCollision(PixelCollision&& _Other) noexcept = delete;
	PixelCollision& operator=(const PixelCollision& _Other) = delete;
	PixelCollision& operator=(PixelCollision&& _Other) noexcept = delete;

	inline void SetPixelFileName(std::string_view _FileName)
	{
		PixelFileName = _FileName;
	}

	inline std::string GetPixelFileName() const
	{
		return PixelFileName;
	}

	GameEngineColor GetColor(const float4& _Position, const float4& _MyPosition, GameEngineColor _DefaultColor = GameEngineColor::WHITE);

private:
	std::string PixelFileName;

};

