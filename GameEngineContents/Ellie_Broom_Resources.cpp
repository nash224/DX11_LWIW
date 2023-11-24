#include "PreCompile.h"
#include "Ellie.h"


void Ellie::BroomSetting()
{
	static constexpr const int RenderOrder = 0;

	Broom.BroomRenderer.resize(static_cast<int>(EllieBroom::EBROOMSTRUCT::Max));
	for (int i = 0; i < static_cast<int>(EllieBroom::EBROOMSTRUCT::Max); i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> BroomRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
		Broom.BroomRenderer[i] = BroomRenderer;
	}

	float4 HeadPos = float4(0.0f, LWIW_Ellie_Y_Correction * 2.0f, 0.01f);
	float4 BodyPos = float4(0.0f, LWIW_Ellie_Y_Correction * 2.0f, -0.01f);

	Broom.BroomRenderer[static_cast<int>(EllieBroom::EBROOMSTRUCT::Head)]->Transform.SetLocalPosition(HeadPos);
	Broom.BroomRenderer[static_cast<int>(EllieBroom::EBROOMSTRUCT::Body)]->Transform.SetLocalPosition(BodyPos);



#pragma region Ellie_Broom_Boosting

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFT", 3, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(1, 17, 35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFT", 4, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(1, 17, 35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(2, 18, 36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(2, 18, 36); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(3, 19, 38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFTDOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(3, 19, 38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFTDOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(4, 20, 39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFTDOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(4, 20, 39); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(5, 21, 40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_DOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(5, 21, 40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_DOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(6, 22, 41); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_DOWN", 14, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(6, 22, 41); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHTDOWN", 19, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(9, 25, 45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHTDOWN", 20, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(9, 25, 45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHTDOWN", 21, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(10, 26, 46); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHTDOWN", 22, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(10, 26, 46); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHT", 15, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(7, 23, 42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHT", 16, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(7, 23, 42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHT", 17, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(8, 24, 43); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHT", 18, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(8, 24, 43); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFTUP", 23, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(11, 27, 47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFTUP", 24, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(11, 27, 47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFTUP", 25, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(12, 28, 48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_LEFTUP", 26, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(12, 28, 48); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_UP", 27, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(13, 29, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_UP", 28, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(13, 29, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_UP", 29, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(14, 30, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_UP", 30, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(14, 30, 0); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHTUP", 31, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(15, 31, 49); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHTUP", 32, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(15, 31, 49); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHTUP", 33, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(16, 32, 50); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Boosting_RIGHTUP", 34, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(16, 32, 50); });
#pragma endregion

#pragma region Ellie_Broom_Standing

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFT", 3, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(2, 18, 35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFT", 4, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(1, 17, 36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(1, 17, 36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(2, 18, 37); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(4, 20, 38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFTDOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(3, 19, 39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFTDOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(3, 19, 39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFTDOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(4, 20, 38); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(6, 22, 40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_DOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(5, 21, 41); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_DOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(5, 21, 41); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_DOWN", 14, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(6, 22, 42); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHTDOWN", 15, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(10, 26, 43); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHTDOWN", 16, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(9, 25, 44); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHTDOWN", 17, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(9, 25, 44); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHTDOWN", 18, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(10, 26, 43); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHT", 19, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(8, 24, 45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHT", 20, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(7, 23, 46); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHT", 21, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(7, 23, 46); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHT", 22, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(8, 24, 45); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFTUP", 31, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(12, 28, 47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFTUP", 32, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(11, 27, 48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFTUP", 33, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(11, 27, 48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_LEFTUP", 34, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(12, 28, 47); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_UP", 27, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(14, 30, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_UP", 28, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(13, 29, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_UP", 29, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(13, 29, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_UP", 30, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(14, 30, 0); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHTUP", 23, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(16, 32, 49); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHTUP", 24, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(15, 31, 50); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHTUP", 25, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(15, 31, 50); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Standing_RIGHTUP", 26, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(16, 32, 49); });
#pragma endregion

#pragma region Ellie_Broom_Moving

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFT", 3, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(1, 17, 35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFT", 4, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(1, 17, 35); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFT", 5, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(2, 18, 36); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFT", 6, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(2, 18, 37); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFTDOWN", 7, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(3, 19, 38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFTDOWN", 8, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(3, 19, 38); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFTDOWN", 9, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(4, 20, 39); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFTDOWN", 10, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(4, 20, 39); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_DOWN", 11, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(5, 21, 40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_DOWN", 12, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(5, 21, 40); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_DOWN", 13, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(6, 22, 41); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_DOWN", 14, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(6, 22, 41); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHTDOWN", 19, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(9, 25, 45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHTDOWN", 20, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(9, 25, 45); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHTDOWN", 21, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(10, 26, 46); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHTDOWN", 22, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(10, 26, 46); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHT", 15, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(7, 23, 42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHT", 16, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(7, 23, 42); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHT", 17, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(8, 24, 43); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHT", 18, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(8, 24, 44); });


	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFTUP", 23, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(11, 27, 47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFTUP", 24, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(11, 27, 47); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFTUP", 25, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(12, 28, 48); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_LEFTUP", 26, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(12, 28, 48); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_UP", 27, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(13, 29, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_UP", 28, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(13, 29, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_UP", 29, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(14, 30, 0); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_UP", 30, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(14, 30, 0); });

	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHTUP", 31, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(15, 31, 49); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHTUP", 32, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(15, 31, 49); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHTUP", 33, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(16, 32, 50); });
	BodyRenderer->SetFrameEvent("Ellie_Basic_Riding_Moving_RIGHTUP", 34, [&](GameEngineSpriteRenderer* _Renderer) {ChangeBroomAndVirgilIndexToRidingMode(16, 32, 50); });
#pragma endregion

}

void Ellie::ChangeBroomAndVirgilIndexToRidingMode(int _HeadIndex, int _BodyIndex, int _VirgilIndex)
{
	if (true == Broom.BroomRenderer.empty() && nullptr == VirgilRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Broom.BroomRenderer[static_cast<int>(EllieBroom::EBROOMSTRUCT::Head)]->ChangeCurSprite(_HeadIndex);
	Broom.BroomRenderer[static_cast<int>(EllieBroom::EBROOMSTRUCT::Body)]->ChangeCurSprite(_BodyIndex);
	VirgilRenderer->ChangeCurSprite(_VirgilIndex);
}