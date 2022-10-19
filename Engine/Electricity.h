#pragma once
#include"../Engine/App/stage/StegeObject.h"
class Electricity
{
public:
	Electricity();

	~Electricity();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	static StageOBJ SetElect(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type);
public:
	bool GetElectFlag() { return electFlag; }
private:
	//�d�C���I�u�W�F�N�g
	ObjectData electOBJ;
	//�d�C�I�u�W�F�N�g
	ObjectData electShockOBJ;

	//�d�CON/OFF
	bool electFlag = false;
	//�d�C�؂�ւ��ő厞�Ԏ���
	const int electTimeMax = 150;
	//�؂�ւ��܂ł̎���
	int electTime = 0;
};

