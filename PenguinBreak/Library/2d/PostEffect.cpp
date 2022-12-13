#include "PostEffect.h"
#include"ShaderManager.h"
using namespace DirectX;
extern const int window_width;
extern const int window_height;

const float PostEffect::clearColor[4] = { 0.2f,0.2f,0.4f,0.0f };//緑っぽい色
ID3D12Device* PostEffect::dev = nullptr;
PostEffect::PostEffect()
{}

void PostEffect::Initialize(ID3D12Device* dev)
{
	HRESULT result;

	this->dev = dev;
	assert(dev);

	CreatePipeline(dev);

	//頂点データ
	Sprite::VertexPosUv vertices[] = {
		{{-1.0f,-1.0f,0.0f},{0.0f,1.0f}},
		{{-1.0f,+1.0f,0.0f},{0.0f,0.0f}},
		{{+1.0f,-1.0f,0.0f},{1.0f,1.0f}},
		{{+1.0f,+1.0f,0.0f},{1.0f,0.0f}},
	};

	//頂点バッファ生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&sprite.vertBuff));
	assert(SUCCEEDED(result));
#ifdef _DEBUG
	sprite.vertBuff->SetName(L"SpriteVert");
#endif
	//頂点バッファへのデータ転送
	Sprite::VertexPosUv* vertMap = nullptr;
	result = sprite.vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		memcpy(vertMap, vertices, sizeof(vertices));
		sprite.vertBuff->Unmap(0, nullptr);
	}

	//頂点バッファビューの作成
	sprite.vbView.BufferLocation = sprite.vertBuff->GetGPUVirtualAddress();
	sprite.vbView.SizeInBytes = sizeof(Sprite::VertexPosUv) * 4;
	sprite.vbView.StrideInBytes = sizeof(Sprite::VertexPosUv);

	//定数バッファ
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(Sprite::ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff)
	);
	assert(SUCCEEDED(result));

#ifdef _DEBUG
	constBuff->SetName(L"SpriteConst");
#endif

	//テクスチャリソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		window_width,
		window_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	//テクスチャバッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
			D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, clearColor),
		IID_PPV_ARGS(&texbuff));
	assert(SUCCEEDED(result));

#ifdef _DEBUG
	texbuff->SetName(L"SpriteBuff");
#endif

	{//テクスチャを赤クリア
		//画素数
		const UINT pixelCount = window_width * window_height;
		//画像1行分のデータサイズ
		const UINT rowPitch = sizeof(UINT) * window_width;
		//画像全体のデータサイズ
		const UINT depthPitch = rowPitch * window_height;
		//画像イメージ
		UINT* img = new UINT[pixelCount];
		for (int i = 0; unsigned(i) < pixelCount; i++) { img[i] = 0xff0000ff; }

		//テクスチャバッファにデータ転送
		result = texbuff->WriteToSubresource(0, nullptr,
			img, rowPitch, depthPitch);
		assert(SUCCEEDED(result));
		delete[] img;
	}

	//SRV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 2;
	//SRV用デスクリプタヒープを生成
	result = dev->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	assert(SUCCEEDED(result));
#ifdef _DEBUG
	descHeapSRV->SetName(L"SpriteSRV");
#endif

	//SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	dev->CreateShaderResourceView(texbuff.Get(),
		&srvDesc,
		CD3DX12_CPU_DESCRIPTOR_HANDLE(
			descHeapSRV->GetCPUDescriptorHandleForHeapStart(), 0,
			dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
		));
	
#ifdef _DEBUG
	texbuff->SetName(L"SpriteBuff");
#endif
	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	//RTV用デスクリプタヒープを生成
	result = dev->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));
#ifdef _DEBUG
	descHeapRTV->SetName(L"SpriteRTV");
#endif
	//デスクリプタヒープにRTV作成
	dev->CreateRenderTargetView(texbuff.Get(),
		nullptr,
		descHeapRTV->GetCPUDescriptorHandleForHeapStart());

	//深度バッファリソース設定
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			window_width,
			window_height,
			1, 0,
			1, 0,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

	//深度バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0),
		IID_PPV_ARGS(&depthBuff));

	assert(SUCCEEDED(result));
#ifdef _DEBUG
	depthBuff->SetName(L"SpriteDepth");
#endif
	//DSV用デスクリプタヒープ
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;
	//DSV用デスクリプタヒープを作成
	result = dev->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	assert(SUCCEEDED(result));

	//デスクリプタヒープにDSV作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dev->CreateDepthStencilView(depthBuff.Get(),
		&dsvDesc,
		descHeapDSV->GetCPUDescriptorHandleForHeapStart());
}

void PostEffect::CreatePipeline(ID3D12Device* dev)
{
	pipelineSet = Pipeline::PostNormalCreateGraphicsPipeline(dev, ShaderManager::postNormalShader);
	SetPipeline(2);
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList, Vec4 color)
{

	DrawPost(sprite, { 0, 0 }, 500.0f, 500.0f, { 0.0f,0.0f }, color, false, false);

}

void PostEffect::PreDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	//リソースバリアを変更
	cmdList->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(texbuff.Get(),
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET));

	//レンダーターゲットビュー用ディスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	//レンダーターゲットをセット
	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	//ビューポートの設定
	cmdList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<FLOAT>(window_width), static_cast<FLOAT>(window_height)));
	//シザリング短形の設定
	cmdList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, static_cast<LONG>(window_width), static_cast<LONG>(window_height)));

	//全画面クリア
	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	//深度バッファのクリア
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

}
void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	//リソースバリアを変更
	cmdList->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(texbuff.Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
}

void PostEffect::UpdatePost(SpriteData& sprite, Vec2 position, float width, float height, Vec2 anchorpoint, Vec4 color, bool isFlipX, bool isFlipY)
{
	//定数バッファの転送
	Sprite::ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->mat = XMMatrixIdentity();
	constMap->color = color;
	constBuff->Unmap(0, nullptr);
}

void PostEffect::DrawPost(SpriteData& sprite, Vec2 position, float width, float height, Vec2 anchorpoint, Vec4 color, bool isFlipX, bool isFlipY)
{
	//パイプラインステートの設定
	Sprite::cmdList->SetPipelineState(pipelineSet.pipelinestate.Get());
	//ルートシグネチャの設定
	Sprite::cmdList->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
	//プリミティブ形状を設定
	Sprite::cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	UpdatePost(sprite, position, width, height, anchorpoint, color, isFlipX, isFlipY);
	//頂点バッファをセット
	Sprite::cmdList->IASetVertexBuffers(0, 1, &sprite.vbView);
	//定数バッファをセット
	Sprite::cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());


	//テクスチャ用デスクリプタヒープの設定
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV.Get() };
	Sprite::cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	//シェーダーリソースビューをセット
	Sprite::cmdList->SetGraphicsRootDescriptorTable(1,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(
			descHeapSRV->GetGPUDescriptorHandleForHeapStart(),
			0,
			dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	/*Sprite::cmdList->SetGraphicsRootDescriptorTable(2,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(
			descHeapSRV->GetGPUDescriptorHandleForHeapStart(),
			1,
			dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));*/

	//ポリゴンの描画（４頂点で四角形）
	Sprite::cmdList->DrawInstanced(4, 1, 0, 0);
}

void PostEffect::SetPipeline(int num)
{
	switch (num)
	{
	case 0:
		pipelineSet = Pipeline::PostNormalCreateGraphicsPipeline(dev, ShaderManager::postNormalShader);
		break;
	case 1:
		pipelineSet = Pipeline::PostNormalCreateGraphicsPipeline(dev, ShaderManager::postTestShader);
		break;
	case 2:
		pipelineSet = Pipeline::DepthOfFieldPipelineCreateGraphicesPipeline(dev, ShaderManager::DepthOfFieldShader);
		break;
	}
}


