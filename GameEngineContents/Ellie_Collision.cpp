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
			// ���� ����� ��ü�� �����ϰڽ��ϴ�.
			std::vector<float> vecDistance;

			size_t Amount = _Collisions.size();
			vecDistance.resize(Amount);

			for (size_t i = 0; i < Amount; i++)
			{
				// 1. ���� ĳ���� ���� �� �� 45��
				// 2. �Ÿ� ����� ���� ����

				std::shared_ptr<GameEngineCollision>& Collision = _Collisions[i];
				if (nullptr == Collision)
				{
					MsgBoxAssert("�浹 ������ �ҷ����� ���߽��ϴ�.");
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
				std::shared_ptr<GameEngineCollision>& Collision = _Collisions[ShortestNumber];

				GameEngineActor* Object = Collision->GetActor();
				if (nullptr == Object)
				{
					MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
					return;
				}

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

				if (UI_Hub_Tool::m_CurrentTool != ETOOLTYPE::Dragonfly)
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
								// ����Ÿ���� ���ø��϶�
								if (ECOLLECTION_METHOD::MongSiri == Entity->GetCollectionMethod())
								{
									// ���߰� ��
									Entity->GetCaught();
								}

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
				if (nullptr == UI_InterativeMark::UI_Mark)
				{
					MsgBoxAssert("UI Mark�� �������� �ʾҽ��ϴ�.");
					return;
				}

				UI_InterativeMark::UI_Mark->PointThis(Entity);
			}
		});
}

