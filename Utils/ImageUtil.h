#pragma once
#include <string>

#include <iostream>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_dx12.h>
#include <limits>
#include <d3d12.h>
#include <dxgi1_4.h>

struct ResourceData {
    ID3D12Resource* pTextureResource;
    D3D12_CPU_DESCRIPTOR_HANDLE hSrvCpuDescHandle;
    D3D12_GPU_DESCRIPTOR_HANDLE hSrvGpuDescHandle;
};

#undef max

namespace ImageUtil {
	static void getTextureDataFromPath(
		std::string& path,
		char** out_pixels
		) 
	{
		std::ifstream file(path, std::ios::binary);

		file.ignore(std::numeric_limits<std::streamsize>::max());
		std::streamsize length = file.gcount();
		file.clear();
		file.seekg(0, std::ios_base::beg);

		*out_pixels = new char[length];
		file.read(*out_pixels, length);
		file.close();
	}

	static ResourceData* loadTextureFromPath(int width, int height, std::string path, ID3D12Device* device, int bufferCount) {
		char* pixels;
		getTextureDataFromPath(path, &pixels);
        ResourceData* bd = new ResourceData();
        // Upload texture to graphics system
        {
            D3D12_DESCRIPTOR_HEAP_DESC dHeapDesc = {};
            dHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
            dHeapDesc.NumDescriptors = bufferCount;
            dHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

            ID3D12DescriptorHeap* dHeap = 0;
            device->CreateDescriptorHeap(&dHeapDesc, IID_PPV_ARGS(&dHeap));

            bd->hSrvCpuDescHandle = dHeap->GetCPUDescriptorHandleForHeapStart();
            bd->hSrvGpuDescHandle = dHeap->GetGPUDescriptorHandleForHeapStart();
            D3D12_HEAP_PROPERTIES props;
            memset(&props, 0, sizeof(D3D12_HEAP_PROPERTIES));
            props.Type = D3D12_HEAP_TYPE_DEFAULT;
            props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

            D3D12_RESOURCE_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
            desc.Alignment = 0;
            desc.Width = width;
            desc.Height = height;
            desc.DepthOrArraySize = 1;
            desc.MipLevels = 1;
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.SampleDesc.Count = 1;
            desc.SampleDesc.Quality = 0;
            desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
            desc.Flags = D3D12_RESOURCE_FLAG_NONE;

            ID3D12Resource* pTexture = nullptr;
            device->CreateCommittedResource(&props, D3D12_HEAP_FLAG_NONE, &desc,
                D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&pTexture));

            UINT uploadPitch = (width * 4 + D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1u) & ~(D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1u);
            UINT uploadSize = height * uploadPitch;
            desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
            desc.Alignment = 0;
            desc.Width = uploadSize;
            desc.Height = 1;
            desc.DepthOrArraySize = 1;
            desc.MipLevels = 1;
            desc.Format = DXGI_FORMAT_UNKNOWN;
            desc.SampleDesc.Count = 1;
            desc.SampleDesc.Quality = 0;
            desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
            desc.Flags = D3D12_RESOURCE_FLAG_NONE;

            props.Type = D3D12_HEAP_TYPE_UPLOAD;
            props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

            ID3D12Resource* uploadBuffer = nullptr;
            HRESULT hr = device->CreateCommittedResource(&props, D3D12_HEAP_FLAG_NONE, &desc,
                D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&uploadBuffer));
            IM_ASSERT(SUCCEEDED(hr));

            void* mapped = nullptr;
            D3D12_RANGE range = { 0, uploadSize };
            hr = uploadBuffer->Map(0, &range, &mapped);
            IM_ASSERT(SUCCEEDED(hr));
            for (int y = 0; y < height; y++)
                memcpy((void*)((uintptr_t)mapped + y * uploadPitch), pixels + y * width * 4, width * 4);
            uploadBuffer->Unmap(0, &range);

            D3D12_TEXTURE_COPY_LOCATION srcLocation = {};
            srcLocation.pResource = uploadBuffer;
            srcLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
            srcLocation.PlacedFootprint.Footprint.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            srcLocation.PlacedFootprint.Footprint.Width = width;
            srcLocation.PlacedFootprint.Footprint.Height = height;
            srcLocation.PlacedFootprint.Footprint.Depth = 1;
            srcLocation.PlacedFootprint.Footprint.RowPitch = uploadPitch;

            D3D12_TEXTURE_COPY_LOCATION dstLocation = {};
            dstLocation.pResource = pTexture;
            dstLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            dstLocation.SubresourceIndex = 0;

            D3D12_RESOURCE_BARRIER barrier = {};
            barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier.Transition.pResource = pTexture;
            barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
            barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
            barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

            ID3D12Fence* fence = nullptr;
            hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
            IM_ASSERT(SUCCEEDED(hr));

            HANDLE event = CreateEvent(0, 0, 0, 0);
            IM_ASSERT(event != nullptr);

            D3D12_COMMAND_QUEUE_DESC queueDesc = {};
            queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
            queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
            queueDesc.NodeMask = 1;

            ID3D12CommandQueue* cmdQueue = nullptr;
            hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&cmdQueue));
            IM_ASSERT(SUCCEEDED(hr));

            ID3D12CommandAllocator* cmdAlloc = nullptr;
            hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAlloc));
            IM_ASSERT(SUCCEEDED(hr));

            ID3D12GraphicsCommandList* cmdList = nullptr;
            hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAlloc, nullptr, IID_PPV_ARGS(&cmdList));
            IM_ASSERT(SUCCEEDED(hr));

            cmdList->CopyTextureRegion(&dstLocation, 0, 0, 0, &srcLocation, nullptr);
            cmdList->ResourceBarrier(1, &barrier);

            hr = cmdList->Close();
            IM_ASSERT(SUCCEEDED(hr));

            cmdQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&cmdList);
            hr = cmdQueue->Signal(fence, 1);
            IM_ASSERT(SUCCEEDED(hr));

            fence->SetEventOnCompletion(1, event);
            WaitForSingleObject(event, INFINITE);

            cmdList->Release();
            cmdAlloc->Release();
            cmdQueue->Release();
            CloseHandle(event);
            fence->Release();
            uploadBuffer->Release();

            // Create texture view
            D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
            ZeroMemory(&srvDesc, sizeof(srvDesc));
            srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
            srvDesc.Texture2D.MipLevels = desc.MipLevels;
            srvDesc.Texture2D.MostDetailedMip = 0;
            srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            device->CreateShaderResourceView(pTexture, &srvDesc, bd->hSrvCpuDescHandle);
            bd->pTextureResource;
            bd->pTextureResource = pTexture;

            dHeap->Release();
        }

		delete[] pixels;
		return bd;
	}

}