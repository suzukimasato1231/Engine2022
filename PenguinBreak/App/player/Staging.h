#pragma once
#include"Vec.h"
#include"ParticleManager.h"
#include<vector>
#include"Particle3D.h"
#include<memory>
/// <summary>
/// �v���C���[���o�N���X
/// </summary>
class Staging
{
private://�����o�ϐ�
	//������
	ObjectData  m_fallDown;
	std::unique_ptr<Particle3D>  paricle3D = nullptr;
	//�d�C���S
	std::unique_ptr<ParticleManager> particle = nullptr;
	//�v���C���[�o�ꎞ�̉��o
	ObjectData  m_startObject;
	TextureData  m_start_color[3]={};

	TextureData  m_graph = {};
public://�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Staging();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~Staging();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// 3D�`��
	/// </summary>
	void Draw3D();
	/// <summary>
	/// ���d���̐�������
	/// </summary>
	void CreateElect(const Vec3 pPos);
	/// <summary>
	/// �����p�[�e�B�N���̐�������
	/// </summary>
	void CreateWalk(const Vec3& pPos, const Vec3& vec);
	/// <summary>
	/// �������̃p�[�e�B�N����������
	/// </summary>
	void CreateFallDown(const Vec3& pPos);
	/// <summary>
	/// �o�ꎞ�̃p�[�e�B�N����������
	/// </summary>
	void CreateStart(const Vec3& pPos);
};

