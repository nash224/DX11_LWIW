#include "PreCompile.h"
#include "GameEngineStructuredBuffer.h"

std::map<int, std::shared_ptr<GameEngineStructuredBuffer>> GameEngineStructuredBuffer::StructuredBufferRes;

GameEngineStructuredBuffer::GameEngineStructuredBuffer()
{
}

GameEngineStructuredBuffer::~GameEngineStructuredBuffer()
{
	Release();
}


void GameEngineStructuredBuffer::VSSetting(UINT _Slot)
{
	// ��Ʈ��ó�� ���۸� ����� SRV
	// ���� ������ t������ �����ϰ� �־���.
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}
void GameEngineStructuredBuffer::PSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineStructuredBuffer::GSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->GSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineStructuredBuffer::CSSetting(UINT _Slot)
{

	// ��ǻƮ ���̴� �϶��� �ϴ�
	// ���� RWStructuredBuffer�μ� �����Ѵٰ� �����ϰ� ������ ����ڴ�.

	// ������ ���� ����� �ȳ� �׳� 
	// ����: const UINT*
	// �߰� �� ��� ���� �������� �迭�Դϴ�.�� - 1�� ���� �������� �������� ��Ÿ���ϴ�.
	// /�ٸ� ��� ���� ������ ī���͸� �����մϴ� �߰� �� �Ҹ� UAV�� ���.
	// pUAVInitialCounts�� D3D11_BUFFER_UAV_FLAG_APPEND �Ǵ� D3D11_BUFFER_UAV_FLAG_COUNTER 
	// ������ ���·� ������ UAV���� ������ �ֽ��ϴ� UAV�� ��������� ��; �׷��� ������ �μ��� ���õ˴ϴ�.

	UINT Offset = -1;
	GameEngineCore::GetContext()->CSSetUnorderedAccessViews(_Slot, 1, &UAV, &Offset);

	// �׷��� ���ҽ��� ���̴� ���ҽ����ù��
	// 	GameEngineCore::GetContext()->CSSetShaderResources(_Slot, 1, &SRV);
}


void GameEngineStructuredBuffer::VSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* NullSRV = nullptr;

	// ��Ʈ��ó�� ���۸� ����� SRV
	// ���� ������ t������ �����ϰ� �־���.
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &NullSRV);
}

void GameEngineStructuredBuffer::PSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* NullSRV = nullptr;
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &NullSRV);
}

void GameEngineStructuredBuffer::GSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* NullSRV = nullptr;
	GameEngineCore::GetContext()->GSSetShaderResources(_Slot, 1, &NullSRV);
}

void GameEngineStructuredBuffer::CSReset(UINT _Slot)
{
	//ID3D11ShaderResourceView* NullSRV = nullptr;
	//GameEngineCore::GetContext()->CSSetShaderResources(_Slot, 1, &NullSRV);

	UINT i = -1;
	ID3D11UnorderedAccessView* Nullptr = nullptr;
	GameEngineCore::GetContext()->CSSetUnorderedAccessViews(_Slot, 1, &Nullptr, &i);
}

void GameEngineStructuredBuffer::Release()
{
	if (nullptr != UAV)
	{
		UAV->Release();
		UAV = nullptr;
	}

	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

	if (nullptr != WriteBuffer)
	{
		WriteBuffer->Release();
		WriteBuffer = nullptr;
	}

	if (nullptr != ReadBuffer)
	{
		ReadBuffer->Release();
		ReadBuffer = nullptr;
	}
	BufferRelease();
}

void GameEngineStructuredBuffer::CreateResize(int _Byte, int _Count, StructuredBufferType _Type, const void* _StartData/* = nullptr*/)
{
	if (DataCount == _Count)
	{
		return;
	}

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
	Desc.StructureByteStride = DataSize;
	BufferInfo = Desc;

	Desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	// �޸� �������� ������ �߿��� �ɼ�
	Desc.Usage = D3D11_USAGE_DEFAULT;

	Type = _Type;

	switch (_Type)
	{
		// ������ ���� �뵵�� ����Ϸ��� ��
	case StructuredBufferType::SRV_ONLY:
		Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Desc.Usage = D3D11_USAGE_DYNAMIC;
		break;
		// ��ǻƮ���̴��� ������ ���� �뵵�� �����͸� �޾ƿ��� �뵵�� ���
	case StructuredBufferType::UAV_INC:
		// D3D11_BIND_UNORDERED_ACCESS ��ǻƮ ���̴� ����.
		Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		Desc.CPUAccessFlags = 0;
		Desc.Usage = D3D11_USAGE_DEFAULT;
		break;
	default:
		break;
	}

	D3D11_SUBRESOURCE_DATA* StartDataPtr = nullptr;
	D3D11_SUBRESOURCE_DATA StartData = { 0 };
	if (nullptr != _StartData)
	{
		StartData.SysMemPitch = 0;
		StartData.SysMemSlicePitch = 0;
		StartData.pSysMem = _StartData;
		StartDataPtr = &StartData;
	}

	BufferInfo = Desc;

	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, StartDataPtr, &Buffer))
	{
		MsgBoxAssert("��Ʈ��ó�� ���� ������ �����߽��ϴ�");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDecs = {};
	// ���̴� ���ҽ� �並 �ؽ�ó�� �ƴ� �Ϲ� ���ۿ��� �����ϰڴ�.
	SRVDecs.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	SRVDecs.Format = DXGI_FORMAT_UNKNOWN;
	// ������ �������� ��𼭺��� �����̳�?
	SRVDecs.BufferEx.FirstElement = 0;
	SRVDecs.BufferEx.Flags = 0;
	SRVDecs.BufferEx.NumElements = DataCount;

	if (S_OK != GameEngineCore::GetDevice()->CreateShaderResourceView(Buffer, &SRVDecs, &SRV))
	{
		MsgBoxAssert("��Ʈ��ó�� ���� �������� ���̴� ���ҽ� �� ������ �����߽��ϴ�");
	}

	if (_Type == StructuredBufferType::UAV_INC)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC UVADesc = {};
		UVADesc.Buffer.NumElements = DataCount;
		UVADesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

		if (S_OK != GameEngineCore::GetDevice()->CreateUnorderedAccessView(Buffer, &UVADesc, &UAV))
		{
			MsgBoxAssert("��Ʈ��ó�� ���� �������� �� ������ �׼��� �� ������ �����߽��ϴ�.");
		}
	}

	// ��� �޾ƿ���� �߰� ���۸� ���� �����ε�.
	// �ȸ���� �ȵ�.

	BufferInfo.ByteWidth = DataSize * DataCount;	// ���� ��ü ũ��
	BufferInfo.StructureByteStride = DataSize;		// ���� ��� ũ��			
	BufferInfo.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // ����ȭ ���� �߰� �÷��� ����
	BufferInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding	

	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	StartData.pSysMem = nullptr;

	const D3D11_SUBRESOURCE_DATA* pInitialData = nullptr;

	if (GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, pInitialData, &WriteBuffer))
	{
		MsgBoxAssert("if (GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &WriteBuffer))");
	}


	BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	if (GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, pInitialData, &ReadBuffer))
	{
		MsgBoxAssert("if (GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &ReadBuffer))");
	}
}

void GameEngineStructuredBuffer::ChangeData(const void* _Data, size_t _Size)
{

	// ���� ���� ����ϸ� ������.
	// �������� ������ �����̴�.
	// �׷���ī�忡�� �� �����͸� ���ų� �� �����Ϳ� ���õ� ����ó�� �Ǵ� �ȼ��̵� ���ؽ��� ��� ���̴��� �����ϴ°�
	GameEngineCore::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);
	// SettingResources �̰� �׷���ī���� �޸� ����ü�� �ƴϴ� �ű⿡ �����϶�� ���� ���̴�.

	if (nullptr == SettingResources.pData)
	{
		MsgBoxAssert("��Ʈ��ó�� ������ GPU �޸𸮸� ������ ���߽��ϴ�");
		GameEngineCore::GetContext()->Unmap(Buffer, 0);
		return;
	}
	memcpy_s(SettingResources.pData, BufferInfo.ByteWidth, _Data, _Size);
	GameEngineCore::GetContext()->Unmap(Buffer, 0);
}


void GameEngineStructuredBuffer::SetData(void* _pSrc, size_t _Count)
{
	// ������ ���ڶ�� �߰��Ҵ��ϸ鼭 �ʱ�ȭ�Ѵ�.
	if (DataCount < static_cast<int>(_Count))
	{
		CreateResize(DataSize, static_cast<int>(_Count), Type, _pSrc);
		return;
	}

	// ������ ����ϴٸ�, ������ ����
	else
	{
		D3D11_MAPPED_SUBRESOURCE tMapSub = {};

		GameEngineCore::GetContext()->Map(WriteBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);
		memcpy(tMapSub.pData, _pSrc, DataSize * DataCount);
		GameEngineCore::GetContext()->Unmap(WriteBuffer, 0);

		// ������� -> ���ι���
		GameEngineCore::GetContext()->CopyResource(Buffer, WriteBuffer);
	}
}