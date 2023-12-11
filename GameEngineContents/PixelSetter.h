#pragma once

struct PixelSetter
{
	static std::shared_ptr<GameEngineSpriteRenderer> SetPixelCollision(GameEngineActor* _Actor, std::string_view _FileName)
	{
		if (nullptr == _Actor)
		{
			MsgBoxAssert("�������� �ʴ� ������Ʈ�� �����Ϸ��߽��ϴ�.");
			return nullptr;
		}

		std::shared_ptr<GameEngineSpriteRenderer> PixelRenderer = _Actor->CreateComponent<GameEngineSpriteRenderer>();
		PixelRenderer->SetSprite(_FileName);
		PixelRenderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainPrev));
		PixelRenderer->RenderBaseInfoValue.Target1 = 1;
		PixelRenderer->On();

		return PixelRenderer;
	}
};

