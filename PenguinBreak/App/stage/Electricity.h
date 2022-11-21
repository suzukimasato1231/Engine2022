#pragma once
#include"StegeObject.h"
#include"ParticleManager.h"
class Electricity
{
public:
	Electricity();

	~Electricity();
	//������
	void Init();
	//�S�̓I�ȍX�V
	void AllUpdate();
	//�X�V
	void Update(StageOBJ* stageObj, const int Z);
	//�`��
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	void DrawParicle();

	static StageOBJ SetElect(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type);
private:
	//�d�C�p�[�e�B�N��
	void AddElect(Vec3 pos);
private:
	//�d�C���I�u�W�F�N�g
	ObjectData m_electOBJ;
	//�d�C�I�u�W�F�N�g
	ObjectData m_electShockOBJ;

	//�d�CON/OFF
	bool m_electFlag = false;
	//�d�C�؂�ւ��ő厞�Ԏ���
	const int c_electTimeMax = 150;
	//�؂�ւ��܂ł̎���
	int m_electTime = 0;
	//�d�C�т�т�
	ParticleManager* m_electParicle = nullptr;
	int m_electParicleGraph = 0;
};

