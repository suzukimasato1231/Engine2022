#pragma once
#include"Vec.h"
#include"ParticleManager.h"
class PlayerFallDie
{
public://�萔
private://�����o�ϐ�
	ParticleManager* particle = nullptr;

	int graph = 0;
public://�����o�֐�
	PlayerFallDie();

	~PlayerFallDie();
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//��������
	void Create(Vec3 pPos);
};

