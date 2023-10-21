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
	// 앨리가 지속타입 상호작용 객체와 작업을하고 있을때 
	IsHolding = false;

	if (false == IsControl || EELLIE_STATUS::Normal != g_Status)
	{
		return;
	}

	// 앨리가 바라보는 사물만 상호작용할 수 있습니다.
	// 기준은 양옆으로 FOVAngle 각도입니다.
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

	m_EllieCol->Collision(ECOLLISION::Entity, [&](std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)
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
				EllieVectorTowardObject.Z = 0.0f;
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
					// 아니면 거리저장
					EllieVectorTowardObject.Size();

					vecDistance[i] = EllieVectorTowardObject.Size();
				}
			}

			int ShortestNumber = -1;
			float ShortestDistance = 1000.0f;

			// 플레이어와 거리가 가장 짧은 객체 선별
			for (size_t i = 0; i < Amount; i++)
			{
				float EntitySize = vecDistance[i];

				if (0.0f != vecDistance[i] && ShortestDistance > EntitySize)
				{
					ShortestNumber = static_cast<int>(i);
					ShortestDistance = EntitySize;
				}
			}

			// 콜리전이 켜져있지만 버튼이 없는 경우 상호작용할 수 없는 버그가 생김
			if (-1 != ShortestNumber)
			{
				std::shared_ptr<GameEngineCollision>& Collision = _Collisions[ShortestNumber];

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

				// 버튼 타입이 없으면 상호작용 X
				if (EINTERACTION_BUTTONTYPE::None == Entity->GetInteractionButtonType())
				{
					return;
				}

				if (UI_Hub_Tool::m_CurrentTool != ETOOLTYPE::Dragonfly)
				{
					// 한번 누르면 되는 타입
					if (EINTERACTION_PRESSTYPE::Down == Entity->GetInteractionPressType())
					{
						// 닿았습니다.
						if (true == GameEngineInput::IsDown('Z', this))
						{
							// 상호작용이 가까이면 
							if (EINTERACTION_TYPE::Near == Entity->GetInteractionType())
							{
								// 수집타입이 몽시리일때
								if (ECOLLECTION_METHOD::MongSiri == Entity->GetCollectionMethod())
								{
									// 멈추게 함
									Entity->GetCaught();
								}

								OtherEntity = Entity;
								ChangeState(EELLIE_STATE::Approach);
							}

							// 멀리있으면 무조건 통과
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
							if (EELLIE_STATE::Idle != m_State)
							{
								ChangeState(EELLIE_STATE::Idle);
							}
						
							Entity->IsReach = true;
							IsHolding = true;
						}
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

