#pragma once
#include "GameEngineTransform.h"

// 우리엔진의 가장 기본적인
// Start 이녀석이 시작될때
// Update 이녀석이 업데이트될때
// Release 이녀석이 지워질때

// 설명 :
class GameEngineObject 
{
	friend class GameEngineLevel;
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Release() {}


	virtual void On()
	{
		IsUpdateValue = true;
	}

	virtual void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		this->IsDeathValue = true;
	}

	virtual bool IsUpdate()
	{
		return Parent == nullptr ? true == IsUpdateValue && false == IsDeathValue : Parent->IsUpdate() && true == IsUpdateValue && false == IsDeathValue;
	}

	virtual bool IsDeath()
	{
		return Parent == nullptr ? IsDeathValue : Parent->IsDeathValue && IsDeathValue;
	}

	int GetOrder()
	{
		return Order;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	void SetName(const std::string& _Name)
	{
		Name = _Name;
	}

	std::string GetName()
	{
		return Name;
	}

	template<typename ObjectType>
	std::shared_ptr<ObjectType> CreateChild(int _Order = 0)
	{
		std::shared_ptr<class GameEngineObject> NewChild = std::make_shared<ObjectType>();

		NewChild->Start();
		NewChild->Parent = this;
		Childs[_Order].push_back(NewChild);

		// GameEngineObject형으로 사용하고 있다면
		// 내가 잘못형변환하면 Monster 였는데? Player <= 미친듯한 메모리 크러시를 일으킵니다.
		// 이녀석은 문제가 이유를 알수 없게 터진다??????
		// 이포인터가 상속관계이 있고 가상함수 테이블을 가지고 있다면
		// dynamic_cast를 통해서 안전하게 형변환이 가능하다.
		// std::shared_ptr 진짜 포인터는 아니기 때문에 dynamic_cast 해야할 상황에서
		// 아래와 같은 함수를 사용하면 된다.
		return std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	virtual void AllUpdate(float _Delta);

protected:
	GameEngineObject* Parent;

	// 오더링을 위해서
	std::map<int, std::list<std::shared_ptr<class GameEngineObject>>> Childs;


private:
	GameEngineTransform Transform;

	std::string Name;
	float LiveTime = 0.0f;
	int Order = 0;
	bool IsUpdateValue = true; // 이걸 false로 만들면 됩니다.
	bool IsDeathValue = false; // 아예 메모리에서 날려버리고 싶어.

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}

};

