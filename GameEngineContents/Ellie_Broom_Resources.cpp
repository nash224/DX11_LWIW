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
}