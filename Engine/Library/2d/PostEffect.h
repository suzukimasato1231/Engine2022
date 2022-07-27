#pragma once
#include "Sprite.h"
#include"Singleton.h"
#include"Sprite.h"
#include"Texture.h"
class PostEffect : public Singleton<PostEffect>
{
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	friend Singleton<PostEffect>;
public:

	//��ʃN���A�J���[
	static const float clearColor[4];
	static ID3D12Device* dev;
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PostEffect();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(ID3D12Device* dev);

	//�p�C�v���C������
	void CreatePipeline(ID3D12Device* dev);

	/// <summary>
	/// �`��R�}���h�̔��s
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// �V�[���`��O����
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// �V�[���`��㏈��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	void UpdatePost(SpriteData& sprite, Vec2 position, float width, float height, Vec2 anchorpoint, Vec4 color, bool isFlipX, bool isFlipY);

	void DrawPost(SpriteData& sprite, Vec2 position, float width, float height, Vec2 anchorpoint, Vec4 color, bool isFlipX, bool isFlipY);
	//�p�C�v���C���؂�ւ�
	void SetPipeline(int num);

private:
	
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource>texbuff;
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap>descHeapSRV;
	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource>depthBuff;
	//RTV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap>descHeapRTV;
	//DSV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap>descHeapDSV;

	//GPU���\�[�X�̐���1
	ComPtr<ID3D12Resource> constBuff;

	SpriteData sprite;

	//�p�C�v���C���Z�b�g
	Pipeline::PipelineSet pipelineSet;
};

