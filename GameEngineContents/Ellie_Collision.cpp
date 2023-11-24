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
	EllieCol->Collision(ECOLLISION::Portal, [&](std::vector<GameEngineCollision*>& _Collision)
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
				OffControl();
			}
		});
}


void Ellie::UpdateInteractionCollsiion()
{
	IsHolding = false;

	if (false == IsControl || EELLIE_STATUS::Normal != g_Status)
	{
		return;
	}

	float4 ElliePosition = Transform.GetWorldPosition();

	float4 DirectionVector = GetDirectionVectorToDir(m_Dir);

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

	EllieCol->Collision(ECOLLISION::Entity, [&](std::vector<GameEngineCollision*>& _Collisions)
		{
			std::vector<float> vecDistance;

			size_t Amount = _Collisions.size();
			vecDistance.resize(Amount);

			for (size_t i = 0; i < Amount; i++)
			{
				GameEngineCollision* Collision = _Collisions[i];

				bool IsAngle = false;

				float4 OtherPosition = Collision->Transform.GetWorldPosition();
				float4 EllieVectorTowardObject = OtherPosition - ElliePosition;

				EllieVectorTowardObject.Z = 0.0f;
				float ObjectAngle = EllieVectorTowardObject.NormalizeReturn().Angle2DDeg();
				if (EllieVectorTowardObject.Y < 0.0f)
				{
					ObjectAngle = 360.0f - ObjectAngle;
				}

				if (EllieLeftFOVAngle - EllieRightFOVAngle > 0.0f)
				{
					if (EllieLeftFOVAngle >= ObjectAngle && EllieRightFOVAngle <= ObjectAngle)
					{
						IsAngle = true;
					}
				}
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

			int ShortestNumber = -1;
			float ShortestDistance = 1000.0f;

			for (size_t i = 0; i < Amount; i++)
			{
				float EntitySize = vecDistance[i];

				if (0.0f != vecDistance[i] && ShortestDistance > EntitySize)
				{
					ShortestNumber = static_cast<int>(i);
					ShortestDistance = EntitySize;
				}
			}

			if (-1 != ShortestNumber)
			{
				GameEngineCollision* Collision = _Collisions[ShortestNumber];

				GameEngineActor* Object = Collision->GetActor();
				if (true ==Object->IsDeath())
				{
					return;
				}

				InteractiveActor* Entity = dynamic_cast<InteractiveActor*>(Object);
				if (nullptr == Entity)
				{
					MsgBoxAssert("다운 캐스팅에 실패했습니다.");
					return;
				}

				if (EINTERACTION_BUTTONTYPE::None == Entity->GetInteractionButtonType())
				{
					return;
				}

				if (EINTERACTION_BUTTONTYPE::Gear == Entity->GetInteractionButtonType())
				{	
					if (true == GameEngineInput::IsDown('Z', this))
					{
						if (EINTERACTION_TYPE::Near == Entity->GetInteractionType())
						{
							OtherEntity = Entity;
							ChangeState(EELLIE_STATE::Approach);
						}
						if (EINTERACTION_TYPE::Far == Entity->GetInteractionType())
						{
							if (ECOLLECTION_METHOD::AlchemyPot == Entity->GetCollectionMethod())
							{
								OtherEntity = Entity;
								ChangeState(EELLIE_STATE::Wait);
							}
							else
							{
								Entity->IsReach = true;
							}
						}
					}
				}
				else if (UI_Hub_Tool::m_CurrentTool != ETOOLTYPE::Dragonfly && EINTERACTION_TYPE::None != Entity->GetInteractionType())
				{
					if (EINTERACTION_PRESSTYPE::Down == Entity->GetInteractionPressType())
					{
						if (true == GameEngineInput::IsDown('Z', this))
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
					}
					else if (EINTERACTION_PRESSTYPE::Press == Entity->GetInteractionPressType())
					{
						if (true == GameEngineInput::IsPress('Z', this))
						{
							if (EELLIE_STATE::Idle != State)
							{
								ChangeState(EELLIE_STATE::Idle);
							}
						
							Entity->IsReach = true;
							IsHolding = true;
						}
					}
				}

				if (nullptr != UI_InterativeMark::UI_Mark)
				{
					UI_InterativeMark::UI_Mark->PointThis(Entity);
				}
			}
		});
}



void Ellie::CheckNetCollision()
{
	NetCollision->Collision(ECOLLISION::Entity, [&](std::vector<GameEngineCollision*>& _OtherGroup)
		{
			for (size_t i = 0; i < _OtherGroup.size(); i++)
			{
				GameEngineCollision* Collision = _OtherGroup[i];
				GameEngineActor* Actor = Collision->GetActor();
				InteractiveActor* Entity = dynamic_cast<InteractiveActor*>(Actor);
				if (ETOOLTYPE::Dragonfly == Entity->GetCollectionToolType())
				{
					Entity->ReachThis();
				}
			}
		});
}