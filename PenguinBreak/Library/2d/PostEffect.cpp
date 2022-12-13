#include "PostEffect.h"
#include"ShaderManager.h"
using namespace DirectX;
extern const int window_width;
extern const int window_height;

const float PostEffect::clearColor[4] = { 0.2f,0.2f,0.4f,0.0f };//�΂��ۂ��F
ID3D12Device* PostEffect::dev = nullptr;
PostEffect::PostEffect()
{}

void PostEffect::Initialize(ID3D12Device* dev)
{
	HRESULT result;

	this->dev = dev;
	assert(dev);

	CreatePipeline(dev);

	//���_�f�[�^
	Sprite::VertexPosUv vertices[] = {
		{{-1.0f,-1.0f,0.0f},{0.0f,1.0f}},
		{{-1.0f,+1.0f,0.0f},{0.0f,0.0f}},
		{{+1.0f,-1.0f,0.0f},{1.0f,1.0f}},
		{{+1.0f,+1.0f,0.0f},{1.0f,0.0f}},
	};

	//���_�o�b�t�@����
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
	//���_�o�b�t�@�ւ̃f�[�^�]��
	Sprite::VertexPosUv* vertMap = nullptr;
	result = sprite.vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		memcpy(vertMap, vertices, sizeof(vertices));
		sprite.vertBuff->Unmap(0, nullptr);
	}

	//���_�o�b�t�@�r���[�̍쐬
	sprite.vbView.BufferLocation = sprite.vertBuff->GetGPUVirtualAddress();
	sprite.vbView.SizeInBytes = sizeof(Sprite::VertexPosUv) * 4;
	sprite.vbView.StrideInBytes = sizeof(Sprite::VertexPosUv);

	//�萔�o�b�t�@
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

	//�e�N�X�`�����\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		window_width,
		window_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	//�e�N�X�`���o�b�t�@�̐���
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

	{//�e�N�X�`����ԃN���A
		//��f��
		const UINT pixelCount = window_width * window_height;
		//�摜1�s���̃f�[�^�T�C�Y
		const UINT rowPitch = sizeof(UINT) * window_width;
		//�摜�S�̂̃f�[�^�T�C�Y
		const UINT depthPitch = rowPitch * window_height;
		//�摜�C���[�W
		UINT* img = new UINT[pixelCount];
		for (int i = 0; unsigned(i) < pixelCount; i++) { img[i] = 0xff0000ff; }

		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texbuff->WriteToSubresource(0, nullptr,
			img, rowPitch, depthPitch);
		assert(SUCCEEDED(result));
		delete[] img;
	}

	//SRV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 2;
	//SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = dev->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	assert(SUCCEEDED(result));
#ifdef _DEBUG
	descHeapSRV->SetName(L"SpriteSRV");
#endif

	//SRV�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
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
	//RTV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	//RTV�p�f�X�N���v�^�q�[�v�𐶐�
	result = dev->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));
#ifdef _DEBUG
	descHeapRTV->SetName(L"SpriteRTV");
#endif
	//�f�X�N���v�^�q�[�v��RTV�쐬
	dev->CreateRenderTargetView(texbuff.Get(),
		nullptr,
		descHeapRTV->GetCPUDescriptorHandleForHeapStart());

	//�[�x�o�b�t�@���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			window_width,
			window_height,
			1, 0,
			1, 0,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

	//�[�x�o�b�t�@�̐���
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
	//DSV�p�f�X�N���v�^�q�[�v
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;
	//DSV�p�f�X�N���v�^�q�[�v���쐬
	result = dev->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	assert(SUCCEEDED(result));

	//�f�X�N���v�^�q�[�v��DSV�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
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
	//���\�[�X�o���A��ύX
	cmdList->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(texbuff.Get(),
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET));

	//�����_�[�^�[�Q�b�g�r���[�p�f�B�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	//�[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	//�����_�[�^�[�Q�b�g���Z�b�g
	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	//�r���[�|�[�g�̐ݒ�
	cmdList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<FLOAT>(window_width), static_cast<FLOAT>(window_height)));
	//�V�U�����O�Z�`�̐ݒ�
	cmdList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, static_cast<LONG>(window_width), static_cast<LONG>(window_height)));

	//�S��ʃN���A
	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	//�[�x�o�b�t�@�̃N���A
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

}
void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	//���\�[�X�o���A��ύX
	cmdList->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(texbuff.Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
}

void PostEffect::UpdatePost(SpriteData& sprite, Vec2 position, float width, float height, Vec2 anchorpoint, Vec4 color, bool isFlipX, bool isFlipY)
{
	//�萔�o�b�t�@�̓]��
	Sprite::ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->mat = XMMatrixIdentity();
	constMap->color = color;
	constBuff->Unmap(0, nullptr);
}

void PostEffect::DrawPost(SpriteData& sprite, Vec2 position, float width, float height, Vec2 anchorpoint, Vec4 color, bool isFlipX, bool isFlipY)
{
	//�p�C�v���C���X�e�[�g�̐ݒ�
	Sprite::cmdList->SetPipelineState(pipelineSet.pipelinestate.Get());
	//���[�g�V�O�l�`���̐ݒ�
	Sprite::cmdList->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
	//�v���~�e�B�u�`���ݒ�
	Sprite::cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	UpdatePost(sprite, position, width, height, anchorpoint, color, isFlipX, isFlipY);
	//���_�o�b�t�@���Z�b�g
	Sprite::cmdList->IASetVertexBuffers(0, 1, &sprite.vbView);
	//�萔�o�b�t�@���Z�b�g
	Sprite::cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());


	//�e�N�X�`���p�f�X�N���v�^�q�[�v�̐ݒ�
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV.Get() };
	Sprite::cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	//�V�F�[�_�[���\�[�X�r���[���Z�b�g
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

	//�|���S���̕`��i�S���_�Ŏl�p�`�j
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


