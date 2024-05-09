#include "DXHook.h"
#include <kiero.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <imgui.h>
#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>
#include <atlbase.h>
#include "../../Event/Impl/RenderEvent.h"
#include "../../Event/EventHandler.h"
#include "../../../Utils/ImageUtil.h"
#include "../../../Utils/MiscUtil.h"
#include "../../System.h"

bool ImGui_Initialised = false;

struct FrameContext {
	CComPtr<ID3D12CommandAllocator> command_allocator = NULL;
	CComPtr<ID3D12Resource> main_render_target_resource = NULL;
	D3D12_CPU_DESCRIPTOR_HANDLE main_render_target_descriptor;
};

// Data
static std::vector<FrameContext> g_FrameContext;
static UINT						g_FrameBufferCount = 0;

static CComPtr<ID3D12DescriptorHeap> g_pD3DRtvDescHeap = NULL;
static CComPtr<ID3D12DescriptorHeap> g_pD3DSrvDescHeap = NULL;
static CComPtr<ID3D12CommandQueue> g_pD3DCommandQueue = NULL;
static CComPtr<ID3D12GraphicsCommandList> g_pD3DCommandList = NULL;

typedef HRESULT(__thiscall* present_o)(IDXGISwapChain3*, UINT, UINT);
present_o presentO;

HRESULT presentH(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags) {
	auto window = FindWindowA(nullptr, "Minecraft");
	if (g_pD3DCommandQueue == nullptr) {
		return presentO(pSwapChain, SyncInterval, Flags);
	}
	if (!ImGui_Initialised) {
		ID3D12Device* pD3DDevice;

		if (FAILED(pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pD3DDevice))) {
			return presentO(pSwapChain, SyncInterval, Flags);
		}

		{
			DXGI_SWAP_CHAIN_DESC desc;
			pSwapChain->GetDesc(&desc);
			g_FrameBufferCount = desc.BufferCount;
			g_FrameContext.clear();
			g_FrameContext.resize(g_FrameBufferCount);
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc = {};
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			desc.NumDescriptors = g_FrameBufferCount;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

			if (pD3DDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pD3DSrvDescHeap)) != S_OK) {
				return presentO(pSwapChain, SyncInterval, Flags);
			}
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			desc.NumDescriptors = g_FrameBufferCount;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			desc.NodeMask = 1;

			if (pD3DDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pD3DRtvDescHeap)) != S_OK) {
				return presentO(pSwapChain, SyncInterval, Flags);
			}

			const auto rtvDescriptorSize = pD3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_pD3DRtvDescHeap->GetCPUDescriptorHandleForHeapStart();

			for (UINT i = 0; i < g_FrameBufferCount; i++) {

				g_FrameContext[i].main_render_target_descriptor = rtvHandle;
				pSwapChain->GetBuffer(i, IID_PPV_ARGS(&g_FrameContext[i].main_render_target_resource));
				pD3DDevice->CreateRenderTargetView(g_FrameContext[i].main_render_target_resource, nullptr, rtvHandle);
				rtvHandle.ptr += rtvDescriptorSize;
			}

		}

		{
			ID3D12CommandAllocator* allocator;
			if (pD3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator)) != S_OK) {
				return presentO(pSwapChain, SyncInterval, Flags);
			}

			for (size_t i = 0; i < g_FrameBufferCount; i++) {
				if (pD3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_FrameContext[i].command_allocator)) != S_OK) {
					return presentO(pSwapChain, SyncInterval, Flags);
				}
			}

			if (pD3DDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_FrameContext[0].command_allocator, NULL, IID_PPV_ARGS(&g_pD3DCommandList)) != S_OK || g_pD3DCommandList->Close() != S_OK) {
				return presentO(pSwapChain, SyncInterval, Flags);
			}
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr;

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX12_Init(pD3DDevice, g_FrameBufferCount,
			DXGI_FORMAT_R8G8B8A8_UNORM, g_pD3DSrvDescHeap,
			g_pD3DSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
			g_pD3DSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

		ImageUtil::loadTextureFromPath(50, 50, System::getStoragePath() + "sponge.png", pD3DDevice, g_FrameBufferCount);
		ImGui_Initialised = true;

		pD3DDevice->Release();
	}

	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX12_NewFrame();
	ImGui::NewFrame();

	RenderEvent e(true);
	EventHandler<RenderEvent>::trigger(e);

	FrameContext& currentFrameContext = g_FrameContext[pSwapChain->GetCurrentBackBufferIndex()];
	currentFrameContext.command_allocator->Reset();

	D3D12_RESOURCE_BARRIER barrier;
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = currentFrameContext.main_render_target_resource;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	g_pD3DCommandList->Reset(currentFrameContext.command_allocator, nullptr);
	g_pD3DCommandList->ResourceBarrier(1, &barrier);
	g_pD3DCommandList->OMSetRenderTargets(1, &currentFrameContext.main_render_target_descriptor, FALSE, nullptr);
	g_pD3DCommandList->SetDescriptorHeaps(1, &g_pD3DSrvDescHeap);
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_pD3DCommandList);
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	g_pD3DCommandList->ResourceBarrier(1, &barrier);
	g_pD3DCommandList->Close();

	g_pD3DCommandQueue->ExecuteCommandLists(1, (ID3D12CommandList**)&g_pD3DCommandList);
	
	return presentO(pSwapChain, SyncInterval, Flags);
}

typedef HRESULT(__thiscall* resizebuffers_o)(IDXGISwapChain3* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
resizebuffers_o resizebuffersO;

HRESULT resizebuffersH(IDXGISwapChain3* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	if (ImGui_Initialised) {
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX12_Shutdown();
		ImGui_Initialised = false;
	}
	g_pD3DCommandQueue = nullptr;
	g_FrameContext.clear();
	g_pD3DCommandList = nullptr;
	g_pD3DRtvDescHeap = nullptr;
	g_pD3DSrvDescHeap = nullptr;
	return resizebuffersO(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

typedef void(__thiscall* ExecuteCommandListsD3D12)(ID3D12CommandQueue*, UINT, ID3D12CommandList*);
ExecuteCommandListsD3D12 oExecuteCommandListsD3D12;

void hookExecuteCommandListsD3D12(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists) {
	if (!g_pD3DCommandQueue)
		g_pD3DCommandQueue = queue;

	oExecuteCommandListsD3D12(queue, NumCommandLists, ppCommandLists);
};

void DirectXHook::patch() {
	if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
		kiero::bind(140, (void**)&presentO, presentH);
		kiero::bind(54, (void**)&oExecuteCommandListsD3D12, hookExecuteCommandListsD3D12);
		kiero::bind(145, (void**)&resizebuffersO, resizebuffersH);
	}
}

void DirectXHook::disablePatch() {
	kiero::unbind(140);
	kiero::unbind(54);
	kiero::unbind(145);
	kiero::shutdown();
}