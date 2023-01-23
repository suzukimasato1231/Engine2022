#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include"Vec.h"
#include"_DirectX.h"
/// <summary>
/// シャドウマップ
/// </summary>
class ShadowMap
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	struct VertexPosUv
	{
		DirectX::XMFLOAT3 pos;			//xyz座標
		DirectX::XMFLOAT2 uv;			//uv座標
	};

	struct ConstantBuffer_b0
	{
		DirectX::XMMATRIX mat;			//変換行列
	};
private:
	static ID3D12Device* dev;
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	//SRv用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//深度バッファ
	ComPtr<ID3D12Resource> depthbuff;

	//SRv用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> depthHeapSRV;
	//RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//グラフィックスパイプライン
	ComPtr<ID3D12PipelineState> pipelineState;
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;

	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
public:
public:
	ShadowMap();
	~ShadowMap();
	void Init();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	void PreDraw(ID3D12GraphicsCommandList* cmdList);
	void PostDraw(ID3D12GraphicsCommandList* cmdList);

	ID3D12Resource* GetTexbuff() { return depthbuff.Get(); }
private:
	void CreateGraphicsPipelineState(ID3D12Device* dev);

	int texture_width = 2600;
	int texture_height = 2600;
};