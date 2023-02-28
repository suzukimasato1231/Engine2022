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
	ObjectData fallDown;
	std::unique_ptr<Particle3D> fallParicle = nullptr;
	//�d�C���S
	std::unique_ptr<ParticleManager>electDie = nullptr;
	//����
	std::unique_ptr<ParticleManager> walk = nullptr;
	//�v���C���[�o�ꎞ�̉��o
	ObjectData startObject;
	std::unique_ptr<Particle3D> startParicle;
	int start_color[3];

	int graph = 0;
public://�����o�֐�
	//�R���X�g���N�^
	Staging();
	//�f�X�R���X�g���N�^
	~Staging();
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//3D�`��
	void Draw3D();
	//���d���̐�������
	void CreateElect(const Vec3 pPos);
	//�����̐�������
	void CreateWalk(const Vec3& pPos, const Vec3& vec);
	//������
	void CreateFallDown(const Vec3& pPos);
	//�o�ꎞ��3D�p�[�e�B�N��
	void CreateStart(const Vec3& pPos);
};

