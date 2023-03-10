#pragma once
#include <d3dx12.h>
#include"Singleton.h"
#include"Sprite.h"
/// <summary>
/// テクスチャクラス
/// </summary>
class Texture :public Singleton<Texture>
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	template <class T> using vector = std::vector<T>;
	friend Singleton<Texture>;
public:
	static ID3D12Device* dev;					//デバイス
	static const int textureMax = 1024;
	//テクスチャデータ
	struct TextureData
	{
		D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		ComPtr<ID3D12Resource> texbuff;
	};

	Texture();

	~Texture();
	//初期化
	void Init(ID3D12Device* dev);
	//画像読み込み
	int LoadTexture(const wchar_t* filename);
	//OBJ画像読み込み
	int OBJLoadTexture(const std::string& directoryPath, const std::string& filename);

	int FbxLoadTexture(const DirectX::Image* img, CD3DX12_RESOURCE_DESC texresDesc);

	//影用の深度値保存
	void LoadShadowTexture(ID3D12Resource* texbuff);
	//被写界深度用
	void LoadCameraTexture(ID3D12Resource* texbuff);
	//ポストエフェクト保存
	void LoadPostEfectTexture(ID3D12Resource* texbuff);
	//SRVを獲得
	const D3D12_GPU_DESCRIPTOR_HANDLE &GetGPUSRV(int i);

	ID3D12Resource* GetTexbuff(int i);
	//desc獲得
	ID3D12DescriptorHeap* GetDescHeap();

	int GetShadowTexture() { return m_shadowTexture; }

	int GetCameraDepth() { return m_cameraDepth; }

	int GetPostEfect() { return m_postEfect; }
private:
	//定数バッファ用のデスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap >m_descHeap = { nullptr };

	//テクスチャデータの作成
	std::vector <TextureData*>textureData;

	int m_texNum = 0;

	int m_shadowTexture = 0;

	int m_cameraDepth = 0;

	int m_postEfect = 0;
};

