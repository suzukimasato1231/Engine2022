#include "Texture.h"
#include <DirectXTex.h>
using namespace DirectX;
ID3D12Device *Texture::dev = nullptr;

Texture::Texture()
{
}

Texture::~Texture()
{
	for (int i = (int)textureData.size() - 1; i >= 0; i--)
	{
		delete textureData[i];
		textureData.erase(textureData.begin() + i);
	}
}

void Texture::Init(ID3D12Device *dev)
{
	this->dev = dev;

	LoadTexture(L"Resources/white1x1.png");
}

int Texture::LoadTexture(const wchar_t *filename)
{
	HRESULT result = S_FALSE;

	textureData.push_back(new Texture::TextureData);

	if (texNum == 0)
	{
		//設定構造体
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダーから見える
		descHeapDesc.NumDescriptors = textureMax;//定数バッファの数
		//デスクリプタヒープの生成
		result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));
	}


	TexMetadata metadata{};
	ScratchImage scratchImg{};
	//WICテクスチャのロード
	result = LoadFromWICFile(
		filename,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);

	const Image *img = scratchImg.GetImage(0, 0, 0);//生データ抽出

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	//テクスチャ用バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,//テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&textureData[texNum]->texbuff));

	//テクスチャバッファにデータ転送
	result = textureData[texNum]->texbuff->WriteToSubresource(
		0,
		nullptr,//全領域へコピー
		img->pixels,//元データアドレス
		(UINT)img->rowPitch,//1ラインサイズ
		(UINT)img->slicePitch//全サイズ
	);

	//デスクリプタヒープの先頭ハンドルを取得
	textureData[texNum]->cpuDescHandleSRV = descHeap->GetCPUDescriptorHandleForHeapStart();
	//ハンドルのアドレスを進める
	textureData[texNum]->cpuDescHandleSRV.ptr += texNum * dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleStart = descHeap->GetGPUDescriptorHandleForHeapStart();
	UINT descHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//1番SRV
	textureData[texNum]->gpuDescHandleSRV = gpuDescHandleStart;
	textureData[texNum]->gpuDescHandleSRV.ptr += descHandleIncrementSize * texNum;

	//シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//２Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	//ヒープの２番目にシェーダーリソースビューを作成
	dev->CreateShaderResourceView(textureData[texNum]->texbuff.Get(),//ビューと関連付けるバッファ
		&srvDesc,//テクスチャ設定構造
		textureData[texNum]->cpuDescHandleSRV
	);
	texNum++;
	return (int)texNum - 1;
}

int Texture::OBJLoadTexture(const std::string &directoryPath, const std::string &filename)
{
	HRESULT result = S_FALSE;
	textureData.push_back(new Texture::TextureData);
	if (texNum == 0)
	{
		//設定構造体
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダーから見える
		descHeapDesc.NumDescriptors = textureMax;//定数バッファの数
		//デスクリプタヒープの生成
		result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));
	}
	// WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	//ファイルパスを結合
	std::string filepath = directoryPath + filename;

	//ユニコード文字列に変換する
	wchar_t wfilepath[128];
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, filepath.c_str(), -1, wfilepath, _countof(wfilepath));

	result = LoadFromWICFile(
		wfilepath, WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	if (FAILED(result)) {
		return result;
	}
	const Image *img = scratchImg.GetImage(0, 0, 0); // 生データ抽出

	// リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);
	// テクスチャ用バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&textureData[texNum]->texbuff));
	if (FAILED(result)) {
		return result;
	}
	// テクスチャバッファにデータ転送
	result = textureData[texNum]->texbuff->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		img->pixels,    // 元データアドレス
		(UINT)img->rowPitch,  // 1ラインサイズ
		(UINT)img->slicePitch // 1枚サイズ
	);
	if (FAILED(result)) {
		return result;
	}
	UINT descHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	// シェーダリソースビュー作成
	textureData[texNum]->cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descHandleIncrementSize);
	//ハンドルのアドレスを進める
	textureData[texNum]->cpuDescHandleSRV.ptr += texNum * descHandleIncrementSize;
	textureData[texNum]->gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descHandleIncrementSize);
	textureData[texNum]->gpuDescHandleSRV.ptr += descHandleIncrementSize * texNum;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	D3D12_RESOURCE_DESC resDesc = textureData[texNum]->texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	dev->CreateShaderResourceView(textureData[texNum]->texbuff.Get(), //ビューと関連付けるバッファ
		&srvDesc, //テクスチャ設定情報
		textureData[texNum]->cpuDescHandleSRV
	);
	texNum++;
	return (int)texNum - 1;
}

D3D12_GPU_DESCRIPTOR_HANDLE Texture::GetGPUSRV(int i)
{
	return 	textureData[i]->gpuDescHandleSRV;
}

ID3D12Resource *Texture::GetTexbuff(int i)
{
	return textureData[i]->texbuff.Get();
}

ID3D12DescriptorHeap *Texture::GetDescHeap()
{
	return descHeap.Get();
}
