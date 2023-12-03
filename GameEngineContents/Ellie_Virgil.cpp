#include "PreCompile.h"
#include "Ellie.h"

#include "CheerFx.h"


void Ellie::VirgilSetting()
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("앨리 바디 렌더러가 존재하지 않습니다.");
		return;
	}


	// BodyRenderer->CreateAnimation("Ellie_Basic_Cheer", "Ellie_Basic_Cheer.png", 0.1f, 4, 15);
	ShadowRendererHelper.CreateFrameInfo("Ellie_Basic_Cheer", { 1,2,3,3,2, 1,1,1,1,1, 1,1 });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Cheer", 10, [&](GameEngineSpriteRenderer* _Renderer)
		{
			std::shared_ptr<CheerFx> Fx = GetLevel()->CreateActor<CheerFx>();
			Fx->Transform.SetLocalPosition(Transform.GetLocalPosition());
		});



	// BodyRenderer->CreateAnimation("Ellie_Basic_Fail", "Ellie_Basic_Fail.png", 0.1f, 5, 14);
	ShadowRendererHelper.CreateFrameInfo("Ellie_Basic_Fail", { 1,1,1,1,1, 2,3,4,4,4  });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 10, [&](GameEngineSpriteRenderer* _Renderer)
		{
			EllieFxRenderer->SetSprite("Ellie_Basic_Fail.png", 21);
			EllieFxRenderer->On();
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 11, [&](GameEngineSpriteRenderer* _Renderer)
		{
			EllieFxRenderer->ChangeCurSprite(22);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 12, [&](GameEngineSpriteRenderer* _Renderer)
		{
			EllieFxRenderer->ChangeCurSprite(23);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 13, [&](GameEngineSpriteRenderer* _Renderer)
		{
			EllieFxRenderer->ChangeCurSprite(24);
		});
	BodyRenderer->SetFrameEvent("Ellie_Basic_Fail", 14, [&](GameEngineSpriteRenderer* _Renderer)
		{
			EllieFxRenderer->ChangeCurSprite(25);
		});
	BodyRenderer->SetEndEvent("Ellie_Basic_Fail", [&](GameEngineSpriteRenderer* _Renderer)
		{
			EllieFxRenderer->Off();
		});


}