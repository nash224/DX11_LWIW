#pragma once

// 기하구조를 표현하고
// 부모자식관계를 처리한다.

// 왜 굳이. 
class TransformData 
{
public:
	float4 Scale;
	float4 Rotation;
	float4 Position;
	
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalPosition;

	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldPosition;

	float4 ScaleMatrix;
	float4 RotationMatrix;
	float4 PositionMatrix;
	float4 LocalWorldMatrix;
	float4 WorldMatrix;
	float4 View;
	float4 Projection;
	float4 ViewPort;
	float4 WorldViewPorjectionMatrix;
};

// 설명 :
class GameEngineTransform
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

protected:

private:
	TransformData TransData;
};

