#pragma once
#include <d3dx12.h>
#include"Singleton.h"
#include"Sprite.h"
/// <summary>
/// �e�N�X�`���N���X
/// </summary>
class Texture :public Singleton<Texture>
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	template <class T> using vector = std::vector<T>;
	friend Singleton<Texture>;
public:
	static ID3D12Device* dev;					//�f�o�C�X
	static const int textureMax = 1024;
	//�e�N�X�`���f�[�^
	struct TextureData
	{
		D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		ComPtr<ID3D12Resource> texbuff;
	};

	Texture();

	~Texture();
	//������
	void Init(ID3D12Device* dev);
	//�摜�ǂݍ���
	int LoadTexture(const wchar_t* filename);
	//OBJ�摜�ǂݍ���
	int OBJLoadTexture(const std::string& directoryPath, const std::string& filename);

	int FbxLoadTexture(const DirectX::Image* img, CD3DX12_RESOURCE_DESC texresDesc);

	//�e�p�̐[�x�l�ۑ�
	void LoadShadowTexture(ID3D12Resource* texbuff);
	//��ʊE�[�x�p
	void LoadCameraTexture(ID3D12Resource* texbuff);
	//�|�X�g�G�t�F�N�g�ۑ�
	void LoadPostEfectTexture(ID3D12Resource* texbuff);
	//SRV���l��
	const D3D12_GPU_DESCRIPTOR_HANDLE &GetGPUSRV(int i);

	ID3D12Resource* GetTexbuff(int i);
	//desc�l��
	ID3D12DescriptorHeap* GetDescHeap();

	int GetShadowTexture() { return m_shadowTexture; }

	int GetCameraDepth() { return m_cameraDepth; }

	int GetPostEfect() { return m_postEfect; }
private:
	//�萔�o�b�t�@�p�̃f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap >m_descHeap = { nullptr };

	//�e�N�X�`���f�[�^�̍쐬
	std::vector <TextureData*>textureData;

	int m_texNum = 0;

	int m_shadowTexture = 0;

	int m_cameraDepth = 0;

	int m_postEfect = 0;
};

