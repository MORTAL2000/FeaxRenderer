#include "stdafx.h"
#include "Graphics.h"
#include "DescriptorHeap.h"
#include "Buffer.h"
#include "..\DXSample.h"
#include <string>

Buffer::Buffer(uint noofElements, uint elementSize, DXGI_FORMAT format, unsigned char *data, LPCWSTR name)
: m_noofElements(noofElements)
, m_elementSize(elementSize)
, m_format(format)
, m_data(data)
{
	m_bufferSize = noofElements * elementSize;
	m_resourceFlags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

	CreateResources();

	m_buffer->SetName(name);
}


void Buffer::CreateResources()
{
	ID3D12Device* device = Graphics::Context.m_device;
	ID3D12GraphicsCommandList* commandList = Graphics::Context.m_commandList;

	D3D12_RESOURCE_DESC desc = {};
	desc.Alignment = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags = m_resourceFlags;
	desc.Format = DXGI_FORMAT_UNKNOWN;
	desc.Height = 1;
	desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Width = (UINT64)m_bufferSize;

	D3D12_HEAP_PROPERTIES heapProperties;
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperties.CreationNodeMask = 1;
	heapProperties.VisibleNodeMask = 1;

	ThrowIfFailed(
		device->CreateCommittedResource(
										&heapProperties,
										D3D12_HEAP_FLAG_NONE,
										&desc,
										D3D12_RESOURCE_STATE_GENERIC_READ,
										nullptr,
										IID_PPV_ARGS(&m_buffer)
										)
	);

	if (m_data)
	{
		// Create the GPU upload buffer.
		ThrowIfFailed(device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(m_bufferSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_bufferUpload)));

		D3D12_SUBRESOURCE_DATA data = {};
		data.pData = m_data;
		data.RowPitch = m_bufferSize;
		data.SlicePitch = 0;

		UpdateSubresources(commandList, m_buffer, m_bufferUpload, 0, 0, 1, &data);
		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_buffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
	}

	// Describe and create a shader resource view (SRV) heap for the texture.
	DescriptorHeapManager* descriptorManager = Graphics::Context.m_descriptorManager;
	m_srvHandle = descriptorManager->CreateCPUHandle(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// Describe and create a SRV for the texture.
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = m_format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.NumElements = m_noofElements;
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

	device->CreateShaderResourceView(m_buffer, &srvDesc, m_srvHandle.GetCPUHandle());
}

Buffer::~Buffer()
{
	m_buffer->Release();
	m_bufferUpload->Release();
}