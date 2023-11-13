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
	// ��Ʈ��ó�� ���۸� ����� SRV
	// ���� ������ t������ �����ϰ� �־���.
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
		MsgBoxAssert("ũ�Ⱑ 0�� ��Ʈ��ó�� ���۸� ���� ���� �����ϴ�.");
	}

	if (DataSize != _Byte)
	{
		MsgBoxAssert("if (DataSize != _Byte) ��Ʈ��ó�� ���� ���� ũ�Ⱑ �ٸ��ϴ�.");
	}

	DataCount = _Count;

	D3D11_BUFFER_DESC Desc;

	Desc.ByteWidth = DataSize * DataCount;
	// 1�� ũ��
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