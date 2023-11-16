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
	m_EllieCol->Collision(ECOLLISION::Portal, [&](std::vector<GameEngineCollision*>& _Collision)
		{
			for (size_t i = 0; i < _Collision.size(); i++)
			{
				GameEngineActor* Object = _Collision[i]->GetActor();
				if (nullptr == Object)
				{
					MsgBoxAssert("�������� �ʴ� ���͸� �����Ϸ� �߽��ϴ�.");
					return;
				}

				PortalObject* PortalActor = dynamic_cast<PortalObject*>(Object);
				if (nullptr == PortalActor)
				{
					MsgBoxAssert("�ٿ�ĳ���ÿ� �����߽��ϴ�.");
					return;
				}

				PortalActor->SetCollisionFlag(true);
				OffControl();
			}
		});
}


void Ellie::UpdateInteractionCollsiion()
{
	// �ٸ��� ����Ÿ�� ��ȣ�ۿ� ��ü�� �۾����ϰ� ������ 
	IsHolding = false;

	if (false == IsControl || EELLIE_STATUS::Normal != g_Status)
	{
		return;
	}

	// �ٸ��� �ٶ󺸴� �繰�� ��ȣ�ۿ��� �� �ֽ��ϴ�.
	// ������ �翷���� FOVAngle �����Դϴ�.
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

	m_EllieCol->Collision(ECOLLISION::Entity, [&](std::vector<GameEngineCollision*>& _Collisions)
		{
			// ���� ����� ��ü�� �����ϰڽ��ϴ�.
			std::vector<float> vecDistance;

			size_t Amount = _Collisions.size();
			vecDistance.resize(Amount);

			for (size_t i = 0; i < Amount; i++)
			{
				// 1. ���� ĳ���� ���� �� �� Ư�� ����
				// 2. �Ÿ� ����� ���� ����

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

				// ���� ���� �� ũ�ٸ�
				if (EllieLeftFOVAngle - EllieRightFOVAngle > 0.0f)
				{
					if (EllieLeftFOVAngle >= ObjectAngle && EllieRightFOVAngle <= ObjectAngle)
					{
						IsAngle = true;
					}
				}
				// ������ ���� �� ũ�ٸ�
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
				
				// ���ΰ� �ޱۿ� ������ ���� ��ü�� �˻� ��󿡼� ���ڽ��ϴ�.
				if (false == IsAngle)
				{
					vecDistance[i] = 0.0f;
				}
				else
				{
					// �ƴϸ� �Ÿ�����
					EllieVectorTowardObject.Size();

					vecDistance[i] = EllieVectorTowardObject.Size();
				}
			}

			int ShortestNumber = -1;
			float ShortestDistance = 1000.0f;

			// �÷��̾�� �Ÿ��� ���� ª�� ��ü ����
			for (size_t i = 0; i < Amount; i++)
			{
				float EntitySize = vecDistance[i];

				if (0.0f != vecDistance[i] && ShortestDistance > EntitySize)
				{
					ShortestNumber = static_cast<int>(i);
					ShortestDistance = EntitySize;
				}
			}

			// �ݸ����� ���������� ��ư�� ���� ��� ��ȣ�ۿ��� �� ���� ���װ� ����
			if (-1 != ShortestNumber)
			{
				GameEngineCollision* Collision = _Collisions[ShortestNumber];

				GameEngineActor* Object = Collision->GetActor();

				InteractiveActor* Entity = dynamic_cast<InteractiveActor*>(Object);
				if (nullptr == Entity)
				{
					MsgBoxAssert("�ٿ� ĳ���ÿ� �����߽��ϴ�.");
					return;
				}

				// ��ư Ÿ���� ������ ��ȣ�ۿ� X
				if (EINTERACTION_BUTTONTYPE::None == Entity->GetInteractionButtonType())
				{
					return;
				}

				// ��ư�� ��� �����̸�
				if (EINTERACTION_BUTTONTYPE::Gear == Entity->GetInteractionButtonType())
				{	
					if (true == GameEngineInput::IsDown('Z', this))
					{
						// ��ȣ�ۿ��� �����̸� 
						if (EINTERACTION_TYPE::Near == Entity->GetInteractionType())
						{
							OtherEntity = Entity;
							ChangeState(EELLIE_STATE::Approach);
						}
						// �ָ������� ������ ���
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
				// ���ڸ�ä ��ȣ�ۿ��� �ƴҶ�
				else if (UI_Hub_Tool::m_CurrentTool != ETOOLTYPE::Dragonfly && EINTERACTION_TYPE::None != Entity->GetInteractionType())
				{
					// �ѹ� ������ �Ǵ� Ÿ��
					if (EINTERACTION_PRESSTYPE::Down == Entity->GetInteractionPressType())
					{
						// ��ҽ��ϴ�.
						if (true == GameEngineInput::IsDown('Z', this))
						{
							// ��ȣ�ۿ��� �����̸� 
							if (EINTERACTION_TYPE::Near == Entity->GetInteractionType())
							{
								OtherEntity = Entity;
								ChangeState(EELLIE_STATE::Approach);
							}

							// �ָ������� ������ ���
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

				// UI���� �̰� ����޶�� ��û�մϴ�.
				if (nullptr != UI_InterativeMark::UI_Mark)
				{
					UI_InterativeMark::UI_Mark->PointThis(Entity);
				}
			}
		});
}



void Ellie::NetCollision()
{
	m_NetCol->Collision(ECOLLISION::Entity, [&](std::vector<GameEngineCollision*>& _OtherGroup)
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