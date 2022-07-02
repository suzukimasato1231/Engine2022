#pragma once
#include<d3dcompiler.h>
#include<DirectXTex.h>
#include<d3dx12.h>
#include<wrl.h>
#include"ShaderManager.h"
using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class Pipeline :public ShaderManager
{
public:
	//�\����
	struct PipelineSet
	{
		//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState>pipelinestate;
		//���[�g�V�O�l�`��
		ComPtr <ID3D12RootSignature>rootsignature;
	};
	//�X�v���C�g
	static PipelineSet  SpriteCreateGraphicsPipeline(ID3D12Device* dev,Shader shader);
	//OBJ�ǂݍ���
	static PipelineSet  OBJCreateGraphicsPipeline(ID3D12Device* dev, Shader shader);

	//�p�[�e�B�N��
	//�l�p�`
	static PipelineSet ParticleCreateGraphicsPipeline(ID3D12Device* dev, Shader shader);

	//�|�X�g�G�t�F�N�g
	//�ʏ�
	static PipelineSet PostNormalCreateGraphicsPipeline(ID3D12Device* dev, Shader shader);
};