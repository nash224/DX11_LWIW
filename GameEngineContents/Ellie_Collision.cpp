#include "PreCompile.h"
#include "Ellie.h"

#include "ContentsMath.h"

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
	isHolding = false;

	if (EELLIE_STATUS::Normal != g_Status)
	{
		return;
	}

	float4 DirectionVector = DirectionFunction::GetVectorToDirection(Dir);
	float DirAngle = ContentMathFunction::ReturnClampDegree(ContentMathFunction::GetDegreeToVector2D(DirectionVector));
	float LeftFOVAngle = ContentMathFunction::ReturnClampDegree(DirAngle + FOVAngle);
	float RightFOVAngle = ContentMathFunction::ReturnClampDegree(DirAngle - FOVAngle);

	ShowFOVDebugLine(LeftFOVAngle, RightFOVAngle);

	EllieCol->Collision(ECOLLISION::Entity, [=](std::vector<GameEngineCollision*>& _Collisions)
		{
			std::vector<float> vecDistance;

			int Amount = static_cast<int>(_Collisions.size());
			vecDistance.resize(Amount);

			for (int i = 0; i < Amount; i++)
			{
				GameEngineCollision* Collision = _Collisions[i];

				const float4 VectorToOther = Collision->Transform.GetWorldPosition() - Transform.GetWorldPosition();
				const float ObjectAngle = ContentMathFunction::ReturnClampDegree(ContentMathFunction::GetDegreeToVector2D(VectorToOther));

				bool isInSight = IsInSight(ObjectAngle, LeftFOVAngle, RightFOVAngle);
				if (isInSight)
				{
					const float4 Size = DirectX::XMVector2Length(VectorToOther.DirectXVector);
					vecDistance[i] = Size.X;
				}
				else
				{
					vecDistance[i] = 0.0f;
				}
			}

			int ShortestNumber = -1;
			float ShortestDistance = 1000.0f;

			for (int i = 0; i < Amount; i++)
			{
				float EntitySize = vecDistance[i];

				if (0.0f != vecDistance[i] && ShortestDistance > EntitySize)
				{
					ShortestNumber = i;
					ShortestDistance = EntitySize;
				}
			}

			if (-1 != ShortestNumber)
			{
				GameEngineCollision* Collision = _Collisions[ShortestNumber];
				if (true == Collision->IsDeath())
				{
					return;
				}

				GameEngineActor* Object = Collision->GetActor();
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
				else if (UI_Hub_Tool::CurRenderToolType != ETOOLTYPE::Dragonfly && EINTERACTION_TYPE::None != Entity->GetInteractionType())
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
							isHolding = true;
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


bool Ellie::IsInSight(float _AngleToObject, float _LeftFov, float _RightFov)
{
	if (_LeftFov - _RightFov > 0.0f)
	{
		if (_LeftFov >= _AngleToObject && _RightFov <= _AngleToObject)
		{
			return true;
		}
	}
	else
	{
		if (_LeftFov >= _AngleToObject && 0.0f <= _AngleToObject)
		{
			return true;
		}
		else if (_RightFov <= _AngleToObject && 360.0f >= _AngleToObject)
		{
			return true;
		}
	}

	return false;
}


void Ellie::CheckNetCollision()
{
	NetCollision->Collision(ECOLLISION::Entity, [&](std::vector<GameEngineCollision*>& _OtherGroup)
		{
			for (int i = 0; i < _OtherGroup.size(); i++)
			{
				GameEngineCollision* Collision = _OtherGroup[i];
				GameEngineActor* Actor = Collision->GetActor();
				InteractiveActor* Entity = dynamic_cast<InteractiveActor*>(Actor);
				if (nullptr == Entity)
				{
					MsgBoxAssert("형변환에 실패했습니다.");
					return;
				}

				if (ETOOLTYPE::Dragonfly == Entity->GetCollectionToolType())
				{
					Entity->ReachThis();
				}
			}
		});
}

void Ellie::ShowFOVDebugLine(float _LeftFOVAngle, float _RightFOVAngle) 
{
	if (true == GameEngineLevel::IsDebug)
	{
		const float FOVDistance = 100.0f;
		const float4 MyPos = Transform.GetLocalPosition() - GetLevel()->GetMainCamera()->Transform.GetLocalPosition();
		float4 LeftLine = MyPos + float4::GetUnitVectorFromDeg(_LeftFOVAngle) * FOVDistance;
		const float4 RightLine = MyPos + float4::GetUnitVectorFromDeg(_RightFOVAngle) * FOVDistance;
	
		GameEngineDebug::DrawLine(MyPos, LeftLine);
		GameEngineDebug::DrawLine(MyPos, RightLine);
	}
}