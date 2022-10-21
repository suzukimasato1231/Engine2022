#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include"Vec.h"
#include"Singleton.h"
#include"_DirectX.h"
extern const int window_width;
extern const int window_height;

class ShadowMap :public Singleton<ShadowMap>
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	struct VertexPosUv
	{
		DirectX::XMFLOAT3 pos;			//xyz���W
		DirectX::XMFLOAT2 uv;			//uv���W
	};

	struct ConstantBuffer_b0
	{
		DirectX::XMMATRIX mat;			//�ϊ��s��
	};
private:
	friend Singleton<ShadowMap>;
	//�e�N�X�`���o�b�t�@
	ID3D12Resource* texbuff;
	//SRv�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource> depthbuff;

	//SRv�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> depthHeapSRV;
	//RTV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//�O���t�B�b�N�X�p�C�v���C��
	ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;

	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�萔�o�b�t�@
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
};