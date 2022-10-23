#pragma once
#include"Vec.h"
#include"ParticleManager.h"
class Staging
{
public://�萔
private://�����o�ϐ�
	ParticleManager* particle = nullptr;
	ParticleManager* electDie = nullptr;
	int graph = 0;
public://�����o�֐�
	Staging();

	~Staging();
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�������̐�������
	void CreateFallDown(Vec3 pPos);
	//���d���̐�������
	void CreateElect(Vec3 pPos);
};

