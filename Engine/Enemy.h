#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
class Enemy
{
private://�\����

public:
	Enemy();//�R���X�g���N�^

	~Enemy();//�ł��R���X�g���N�^

	 void Init();//������

	void Update();//�X�V

	void Draw();//�`��

	Vec3 GetPos() { return pos; }

	Vec3 GetSize() { return eSize; }

	void  SetPos(Vec3 pos) { Enemy::pos = pos; }
private:
	Vec3 pos = {};
	int eNum = 2;
	const Vec3 eSize = { 10.0f,5.0f,10.0f };
public://�擾�n
	int GetENum() { return eNum; }
};