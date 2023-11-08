#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

	// Ό³Έν :
	class VirgilHat : public Effect
	{
	public:
		// constrcuter destructer
		VirgilHat();
		~VirgilHat();

		// delete Function
		VirgilHat(const VirgilHat& _Other) = delete;
		VirgilHat(VirgilHat&& _Other) noexcept = delete;
		VirgilHat& operator=(const VirgilHat& _Other) = delete;
		VirgilHat& operator=(VirgilHat&& _Other) noexcept = delete;

	protected:

	private:
		void Start() override;
		void EffectProcess(float _DeltaTime) override;


	};