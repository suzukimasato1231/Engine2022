#include "ShadowMap.h"
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <cassert>
#include"Object.h"
ShadowMap::ShadowMap()
{
}

ShadowMap::~ShadowMap()
{
}

void ShadowMap::Init()
{
	ID3D12Device* dev=_DirectX::Get()->GetDevice();
	HRESULT result;

	//頂点バッファ生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv) * 4),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

	//頂点データ転送
	VertexPosUv vertices[4];

	vertices[0].pos = { -1.0f, -1.0f , 0.0f };
	vertices[1].pos = { -1.0f, 1.0, 0.0f };
	vertices[2].pos = { 1.0, -1.0f , 0.0f };
	vertices[3].pos = { 1.0, 1.0, 0.0f };

	vertices[0].uv = { 0.0f, 1.0f };
	vertices[1].uv = { 0.0f, 0.0f };
	vertices[2].uv = { 1.0f, 1.0f };
	vertices[3].uv = { 1.0f, 0.0f };

	//頂点バッファへのデータ転送
	VertexPosUv* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuff->Unmap(0, nullptr);
	}

	//頂点バッファビューの作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(VertexPosUv) * 4;
	vbView.StrideInBytes = sizeof(VertexPosUv);

	//定数バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstantBuffer_b0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff)
	);
	assert(SUCCEEDED(result));

	//テクスチャリソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		window_width,
		window_height,
		1, 1, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	//テクスチャバッファの生成
	float color[] = { 1.0f,1.0f,1.0f,1.0f };
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, color),
		IID_PPV_ARGS(&texbuff)
	);
	assert(SUCCEEDED(result));

	//テクスチャを仮想生成
	const UINT pixelCount = window_width * window_height;
	//画像1行分のデータサイズ
	const UINT rowPitch = sizeof(UINT) * window_width;
	//画像全体のデータサイズ
	const UINT depthPitch = rowPitch * window_height;
	//画像イメージ
	UINT* img = new UINT[pixelCount];
	for (int i = 0; i < static_cast<int>(pixelCount); i++) { img[i] = 0xff0000ff; }

	//テクスチャバッファにデータ転送
	result = texbuff->WriteToSubresource(0, nullptr,
		img, rowPitch, depthPitch);
	assert(SUCCEEDED(result));
	delete[] img;

	//SRV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 1;
	//SRV用デスクリプタヒープを作成
	result = dev->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	assert(SUCCEEDED(result)
	);

	//SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};				//設定構造体
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	//デスクリプタヒープにSRVを作成
	dev->CreateShaderResourceView(
		texbuff,	//ビューと関連付けるバッファ
		&srvDesc,
		descHeapSRV->GetCPUDescriptorHandleForHeapStart()
	);

	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;

	//RTV用デスクリプタヒープを生成
	result = dev->CreateDescriptorHeap(
		&rtvDescHeapDesc,
		IID_PPV_ARGS(&descHeapRTV)
	);
	assert(SUCCEEDED(result));
	
	
	dev->CreateRenderTargetView(
		texbuff,
		nullptr,
		descHeapRTV->GetCPUDescriptorHandleForHeapStart()
	);

	//深度バッファリソース設定
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			window_width,
			window_height,
			1, 0,
			1, 0,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		);

	//深度バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0),
		IID_PPV_ARGS(&depthbuff)
	);
	assert(SUCCEEDED(result));

	//DSV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;
	//DSV用デスクリプタヒープを作成
	result = dev->CreateDescriptorHeap(
		&DescHeapDesc,
		IID_PPV_ARGS(&descHeapDSV)
	);
	assert(SUCCEEDED(result));

	//デスクリプタヒープにDSV作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	//深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dev->CreateDepthStencilView(
		depthbuff.Get(),
		&dsvDesc,
		descHeapDSV->GetCPUDescriptorHandleForHeapStart()
	);
}

void ShadowMap::Draw(ID3D12GraphicsCommandList* cmdList)
{
	HRESULT result = S_OK;

	//定数バッファにデータ転送
	ConstantBuffer_b0 data;
	data.mat = XMMatrixIdentity();

	//GPU上のバッファに対応した仮想メモリを取得
	ConstantBuffer_b0* constMap = nullptr;
	void* dst = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&dst);
	memcpy(dst, &data, sizeof(ConstantBuffer_b0));
	constBuff->Unmap(0, nullptr);

	//パイプラインステートの設定
	cmdList->SetPipelineState(pipelineState.Get());
	//ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(rootSignature.Get());
	//プリミティブ形状を設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &this->vbView);

	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV.Get() };
	//デスクリプタヒープをセット
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(0, this->constBuff->GetGPUVirtualAddress());

	//SRV
	cmdList->SetGraphicsRootDescriptorTable(
		1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());
	//描画コマンド
	cmdList->DrawInstanced(4, 1, 0, 0);
}

void ShadowMap::PreDraw(ID3D12GraphicsCommandList* cmdList)
{
	//リソースバリアを変更
	cmdList->ResourceBarrier(
		1,
		&CD3DX12_RESOURCE_BARRIER::Transition(texbuff,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET)
	);

	//レンダーターゲットビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	//レンダーターゲットをセット
	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	//ビューポートの設定
	cmdList->RSSetViewports(
		1,
		&CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<FLOAT>(window_width), static_cast<FLOAT>(window_height))
	);
	//シザリング矩形の設定
	cmdList->RSSetScissorRects(
		1,
		&CD3DX12_RECT(0, 0, static_cast<LONG>(window_width), static_cast<LONG>(window_height))
	);

	//全画面クリア
	float color[] = { 1.0f,1.0f,1.0f,1.0f };
	cmdList->ClearRenderTargetView(rtvH, color, 0, nullptr);

	//深度バッファのクリア
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void ShadowMap::PostDraw(ID3D12GraphicsCommandList* cmdList)
{
	cmdList->ResourceBarrier(
		1,
		&CD3DX12_RESOURCE_BARRIER::Transition(texbuff,
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
	);

}