#include "PreCompile.h"
#include "Ellie.h"

#include "InteractiveActor.h"
#include "PortalObject.h"
#include "UI_InterativeMark.h"
#include "UI_Hub_Tool.h"


void Ellie::UpdateCollision()
{
	UpdatePortalCollsiion();
	UpdateInteractionCollsiion();
}

void Ellie::UpdatePortalCollsiion()
{
	m_EllieCol->Collision(ECOLLISION::Portal, [](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
		{
			for (size_t i = 0; i < _Collision.size(); i++)
			{
				GameEngineActor* Object = _Collision[i]->GetActor();
				if (nullptr == Object)
				{
					MsgBoxAssert("존재하지 않는 액터를 참조하려 했습니다.");
					return;
				}

				PortalObject* PortalActor = dynamic_cast<PortalObject*>(Object);
				if (nullptr == PortalActor)
				{
					MsgBoxAssert("다운캐스팅에 실패했습니다.");
					return;
				}

				PortalActor->SetCollisionFlag(true);
			}
		});
}


void Ellie::UpdateInteractionCollsiion()
{
	if (false == IsControl || EELLIE_STATUS::Normal != g_Status)
	{
		return;
	}

	// 앨리가 바라보는 사물만 상호작용할 수 있습니다.
	// 기준은 양옆으로 45도 각도입니다.
	float4 ElliePosition = Transform.GetWorldPosition();

	float4 DirectionVector = CalculateDirectionVectorToDir(m_Dir);

	float EllieFOVAngle = DirectionVector.Angle2DDeg();
	if (DirectionVector.Y < 0.0f)
	{
		EllieFOVAngle = 360.0f - EllieFOVAngle;
	}

	float EllieLeftFOVAngle = EllieFOVAngle + FOVAngle;
	float EllieRightFOVAngle = EllieFOVAngle - FOVAngle;

	if (EllieLeftFOVAngle >= 360.0f)
	{
		EllieLeftFOVAngle -= 360.0f;
	}

	if (EllieRightFOVAngle < 0.0f)
	{
		EllieRightFOVAngle += 360.0f;
	}

	m_EllieCol->Collision(ECOLLISION::Entity, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)
		{
			// 가장 가까운 객체만 참조하겠습니다.
			std::vector<float> vecDistance;

			size_t Amount = _Collisions.size();
			vecDistance.resize(Amount);

			for (size_t i = 0; i < Amount; i++)
			{
				// 1. 각도 캐릭터 기준 양 옆 45도
				// 2. 거리 가까운 액터 기준

				std::shared_ptr<GameEngineCollision>& Collision = _Collisions[i];
				if (nullptr == Collision)
				{
					MsgBoxAssert("충돌 정보를 불러오지 못했습니다.");
					return;
				}

				bool IsAngle = false;

				float4 OtherPosition = Collision->Transform.GetWorldPosition();
				float4 EllieVectorTowardObject = OtherPosition - ElliePosition;
				float ObjectAngle = EllieVectorTowardObject.NormalizeReturn().Angle2DDeg();
				if (EllieVectorTowardObject.Y < 0.0f)
				{
					ObjectAngle = 360.0f - ObjectAngle;
				}

				// 왼쪽 각이 더 크다면
				if (EllieLeftFOVAngle - EllieRightFOVAngle > 0.0f)
				{
					if (EllieLeftFOVAngle >= ObjectAngle && EllieRightFOVAngle <= ObjectAngle)
					{
						IsAngle = true;
					}
				}
				// 오른쪽 각이 더 크다면
				else
				{
					if (EllieLeftFOVAngle >= ObjectAngle && 0.0f <= ObjectAngle)
					{
						IsAngle = true;
					}
					else if (EllieRightFOVAngle <= ObjectAngle && 360.0f >= ObjectAngle)
					{
						IsAngle = true;
					}
				}
				
				// 주인공 앵글에 들어오지 않은 객체는 검사 대상에서 빼겠습니다.
				if (false == IsAngle)
				{
					vecDistance[i] = 0.0f;
				}
				else
				{
					EllieVectorTowardObject.Size();

					vecDistance[i] = EllieVectorTowardObject.Size();
				}
			}

			int MostLongestNumber = -1;
			float MostLongestDistance = 0.0f;

			for (size_t i = 0; i < Amount; i++)
			{
				float CurrentDistance = vecDistance[i];
				if (0.0f != vecDistance[i] && MostLongestDistance < CurrentDistance)
				{
					MostLongestNumber = static_cast<int>(i);
					MostLongestDistance = CurrentDistance;
				}
			}

			if (-1 != MostLongestNumber)
			{
				std::shared_ptr<GameEngineCollision>& Collision = _Collisions[MostLongestNumber];

				GameEngineActor* Object = Collision->GetActor();
				if (nullptr == Object)
				{
					MsgBoxAssert("액터를 불러오지 못했습니다.");
					return;
				}

				InteractiveActor* Entity = dynamic_cast<InteractiveActor*>(Object);
				if (nullptr == Entity)
				{
					MsgBoxAssert("다운 캐스팅에 실패했습니다.");
					return;
				}

				if (EINTERACTION_BUTTONTYPE::Gathering == Entity->GetInteractionButtonType())
				{
					if (ETOOLTYPE::None == Entity->m_CollectionTool)
					{
						// Pass
					}
					else if (UI_Hub_Tool::m_CurrentTool != Entity->m_CollectionTool)
					{
						return;
					}
				}

				// 닿았습니다.
				if (true == GameEngineInput::IsDown('Z'))
				{
					if (EINTERACTION_TYPE::Near == Entity->GetInteractionType())
					{
						OtherEntity = Entity;
						ChangeState(EELLIE_STATE::Approach);
					}

					if (EINTERACTION_TYPE::Far == Entity->GetInteractionType())
					{
						Entity->IsReach = true;
					}
				}

				// UI에게 이걸 띄워달라고 요청합니다.
				if (nullptr == UI_InterativeMark::UI_Mark)
				{
					MsgBoxAssert("UI Mark가 생성되지 않았습니다.");
					return;
				}

				UI_InterativeMark::UI_Mark->PointThis(Entity);
			}
		});
}

