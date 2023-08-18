#pragma once
#include "GameEngineResources.h"
#include "GameEngineDirectBuffer.h"

// 설명 :
class GameEngineVertexBuffer :
	public GameEngineResources<GameEngineVertexBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer();

	// delete Function
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&& _Other) noexcept = delete;

	template<typename VertexType>
	static std::shared_ptr<GameEngineVertexBuffer> Create(const std::string_view& _Name, const std::vector<VertexType>& _Data)
	{
		std::shared_ptr<GameEngineVertexBuffer> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(&_Data[0], sizeof(VertexType), _Data.size());
		return nullptr;
	}

	void Setting();

protected:

private:
	//                                점1개의 크기가 얼마? 점 개수가 몇개냐.,
	void ResCreate(const void* _Data, size_t _VertexSize, size_t _VertexCount);

	UINT VertexSize = 0;
	UINT VertexCount = 0;
	UINT Offset = 0;

};

