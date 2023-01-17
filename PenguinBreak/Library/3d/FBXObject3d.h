#pragma once
#include "Model.h"
#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<DirectXMath.h>
#include<string>
#include"FbxLoader.h"
#include"LightGroup.h"
/// <summary>
/// FBX�I�u�W�F�N�g�N���X
/// </summary>
class FBXObject3d
{
protected://�G�C���A�X
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public://�ÓI�����o�֐�
	static void SetDevice(ID3D12Device *device) { FBXObject3d::device = device; }
	static void SetLight(LightGroup* lightGroup) { FBXObject3d::lightGroup = lightGroup; }
	static void SetCmdList(ID3D12GraphicsCommandList *cmdList) { FBXObject3d::cmdList = cmdList; }
private://�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device *device;
	//���C�g�N���X
	static LightGroup* lightGroup;

	static ID3D12GraphicsCommandList *cmdList;
public://�萔
	//�{�[���̍ő吔
	static const int MAX_BONES = 32;
public://�T�u�N���X

		//�萔�o�b�t�@�p�f�[�^�\����(���W�ϊ��s��p)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	//�r���[�v���W�F�N�V�����s��
		XMMATRIX world;		//���[���h�s��
		Vec3 cameraPos;	//�J�������W(���[���h���W)
	};



	//�萔�o�b�t�@�p�f�[�^�\����(�X�L�j���O)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public://�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C���̐���
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update(bool shadowFlag);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���f���̃Z�b�g
	/// </summary>
	/// <param name="model"></param>
	void SetModel(Model *model) { this->model = model; }

	/// <summary>
	/// �A�j���[�V�����J�n
	/// </summary>
	/// <param name="Loop">���[�v�Đ������邩�ǂ���</param>
	void PlayAnimation(bool Loop);
	/// <summary>
	/// �A�j���[�V�����̒�~
	/// </summary>
	void StopAnimation();

	void SetPosition(Vec3 pos) { FBXObject3d::position = pos; }
	void SetScale(Vec3 scale) { FBXObject3d::scale = scale; }
	void SetRotation(Vec3 rotation) { FBXObject3d::rotation = rotation; }
protected://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource>constBuffTransform;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource>constBufferSkin;

	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature>rootsignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState>pipelinestate;

	//���[�J���X�P�[��
	Vec3 scale = { 0.025f,0.025f,0.025f };//�y���M��
	//X,Y,Z�����̃��[�J����]�p
	Vec3 rotation = { 0.0f,180.0f,0.0f };
	//���[�J�����W
	Vec3 position = { 0,0,0 };
	//���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	//���f��
	Model *model = nullptr;

	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;
	//�A�j���[�V���������[�v�����邩�ǂ���
	bool isLoop = false;
};
