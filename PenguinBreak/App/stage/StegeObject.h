#pragma once
#include"Object.h"
#include <CollisionPrimitive.h>

enum StageType
{
	NONEFLOOR,
	FLOORNORMAL,	//���ʂ̏�
	FLOOR169,		//�΂ߏ�
	FLOOR11,		//�΂ߏ�
	FLOORMOVE,		//�ړ���
	FLOORMOVE2,		//�ړ���
	FLOORPITFALL_A,	//���Ƃ���A
	FLOORPITFALL_B,	//���Ƃ���B
	WALL ,			//��
	GOAL ,			//�S�[��
	BARRIERWALL ,	//�o���A�u���b�N
	BOX ,			//���锠
	BOXHARD ,		//�ł���
	BOXJUMP ,		//�W�����v��
	BOXBOMB ,		//���e��
	ICICLE ,		//�X��
	ELECTRICITY ,	//�d�C
	FISHATTACK ,	//���A�^�b�N
	DEADTREE ,		//�͂��
	STLON ,			//��
	ICEARCH ,		//�X�̃A�[�`
	SIGNBOARD1 ,	//�ŔW�����v
	SIGNBOARD2 ,	//�ŔX�s��
};

struct StageData
{
	Vec3 position = {};
	Vec3 scale = {};
	Vec3 rotation = {};
	//�e�N���X
	PSR psr = {};
	std::string fileName;
	Box box;
	int type = 0;
	int actionTime = 0;
	int actionType = 0;
	Vec3 actionPos = {};
};