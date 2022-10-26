#pragma once
#include"Vec.h"
#include"ParticleManager.h"
#include<vector>
#include"Particle3D.h"
class Staging
{
private://�����o�ϐ�
	//������
	ObjectData fallDown;
	Particle3D *fallParicle;
	//�d�C���S
	ParticleManager* electDie = nullptr;
	//����
	ParticleManager* walk = nullptr;
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
	void CreateElect(Vec3 pPos);
	//�����̐�������
	void CreateWalk(Vec3 pPos, Vec3 vec);
	//������
	void CreateFallDown(Vec3 pPos);
};

