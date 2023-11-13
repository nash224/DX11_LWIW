#include "PreCompile.h"
#include "GameEngineStructuredBuffer.h"

std::map<int, std::shared_ptr<GameEngineStructuredBuffer>> GameEngineStructuredBuffer::StructuredBufferRes;

GameEngineStructuredBuffer::GameEngineStructuredBuffer() 
{
}

GameEngineStructuredBuffer::~GameEngineStructuredBuffer() 
{
}


void GameEngineStructuredBuffer::VSSetting(UINT _Slot)
{
	// 스트럭처드 버퍼를 만들면 SRV
	// 무슨 슬롯을 t슬롯을 차지하고 있었다.
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}
void GameEngineStructuredBuffer::PSSetting(UINT _Slot)
{
}


void GameEngineStructuredBuffer::Release()
{
	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}
	BufferRelease();
}

void GameEngineStructuredBuffer::CreateResize(int _Byte, int _Count, StructuredBufferType _Type)
{
	if (DataCount < _Count)
	{
		Release();
	}

	if (0 >= _Byte)
	{
		MsgBoxAssert("크기가 0인 스트럭처드 버퍼를 만들 수는 없습니다.");
	}

	if (DataSize != _Byte)
	{
		MsgBoxAssert("if (DataSize != _Byte) 스트럭처드 버퍼 세팅 크기가 다릅니다.");
	}

	DataCount = _Count;

	D3D11_BUFFER_DESC Desc;

	Desc.ByteWidth = DataSize * DataCount;
	// 1개 크기
	Desc.StructureByteStride = DataSize;
	BufferInfo = Desc;

	Desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	Type = _Type;

	switch (_Type)
	{
	case StructuredBufferType::SRV_ONLY:
		break;
	case StructuredBufferType::UAV_INC:
		break;
	default:
		break;
	}
	

}