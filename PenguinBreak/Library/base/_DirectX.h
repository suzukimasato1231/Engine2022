#pragma once
#include<Windows.h>
#include<wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include "_Window.h."
#include"Singleton.h"
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>
#include <chrono>
extern const int window_width;
extern const int window_height;
/// <summary>
/// DirectX12クラス
/// </summary>
class _DirectX :public Singleton<_DirectX>
{
public:
	friend Singleton<_DirectX>;
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	
private://メンバ変数
	//ウィンドウ関連

	//DirectX3D関連
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12GraphicsCommandList >cmdList;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12CommandQueue >cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap>rtvHeaps;
	//深度設定
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//フェンスの生成
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	ComPtr<ID3D12DescriptorHeap> imguiHeap;
	float deltaTime = 0.0f;
	float frameRate = 0.0f;
	float commandWaitTime = 0.0f;
	std::chrono::steady_clock::time_point lastUpdate;
private:
	//アダプタの列挙
	void Adapter();

	//コマンドリスト
	void CommandListInitilize();

	//スワップチェーン
	void Swapchain();
	//深度設定
	void DepthBuffer();
	//imgui初期化
	bool InitImgui();
	
public://メンバ関数
	_DirectX();

	~_DirectX()
	{

	}
	//初期化
	void Initilize();

	//描画前処理
	void PreDraw();

	//描画後処理
	void ResourceBarrier();

	ID3D12Device* GetDevice();

	ID3D12GraphicsCommandList* GetCmandList();

	ID3D12Resource* GetDeth() { return depthBuffer.Get(); };

	void ClearDepthBuffer();
	
};
